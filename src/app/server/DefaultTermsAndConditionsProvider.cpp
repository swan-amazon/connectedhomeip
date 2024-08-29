/*
 *
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "DefaultTermsAndConditionsProvider.h"
#include "TermsAndConditionsProvider.h"

#include <lib/core/CHIPError.h>
#include <lib/core/TLV.h>
#include <lib/core/TLVTypes.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/DefaultStorageKeyAllocator.h>
#include <lib/support/SafeInt.h>

namespace {
constexpr chip::TLV::Tag kSerializationVersionTag            = chip::TLV::ContextTag(1);
constexpr chip::TLV::Tag kAcceptedAcknowledgementsTag        = chip::TLV::ContextTag(2);
constexpr chip::TLV::Tag kAcceptedAcknowledgementsVersionTag = chip::TLV::ContextTag(3);
constexpr uint8_t kSerializationVersion                      = 1;

constexpr size_t kEstimatedTlvBufferSize = chip::TLV::EstimateStructOverhead(sizeof(uint8_t),  // SerializationVersion
                                                                             sizeof(uint16_t), // AcceptedAcknowledgements
                                                                             sizeof(uint16_t)  // AcceptedAcknowledgementsVersion
                                                                             ) *
    2; // Extra space for rollback compatibility
} // namespace

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::Init(
    chip::PersistentStorageDelegate * const inPersistentStorageDelegate,
    const chip::Optional<chip::app::TermsAndConditions> & inmRequiredAcknowledgements)
{
    VerifyOrReturnError(nullptr != inPersistentStorageDelegate, CHIP_ERROR_INVALID_ARGUMENT);

    mPersistentStorageDelegate = inPersistentStorageDelegate;
    mRequiredAcknowledgements  = inmRequiredAcknowledgements;

    if (CHIP_NO_ERROR == LoadAcceptance(mLatchedAcceptance))
    {
        mTemporalAcceptance.SetValue(mLatchedAcceptance.Value());
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::CheckAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions,
                                                                         TermsAndConditionsState & outState) const
{
    // No validation checks required if no required terms and conditions
    if (!mRequiredAcknowledgements.HasValue())
    {
        outState = TermsAndConditionsState::OK;
        return CHIP_NO_ERROR;
    }

    // Validate if we have received any terms and conditions acceptance
    if (!inTermsAndConditions.HasValue())
    {
        ChipLogError(AppServer, "No terms and conditions have been accepted");
        outState = TermsAndConditionsState::TC_ACKNOWLEDGEMENTS_NOT_RECEIVED;
        return CHIP_NO_ERROR;
    }

    // Validate the accepted version first...
    if (mRequiredAcknowledgements.Value().version > inTermsAndConditions.Value().version)
    {
        ChipLogProgress(AppServer, "Minimum terms and conditions version, 0x%04x, has not been accepted",
                        mRequiredAcknowledgements.Value().version);
        outState = TermsAndConditionsState::TC_MIN_VERSION_NOT_MET;
        return CHIP_NO_ERROR;
    }

    // Validate the accepted bits second...
    if (mRequiredAcknowledgements.Value().value != (mRequiredAcknowledgements.Value().value & inTermsAndConditions.Value().value))
    {
        ChipLogProgress(AppServer, "Required terms and conditions, 0x%04x,have not been accepted",
                        mRequiredAcknowledgements.Value().value);
        outState = TermsAndConditionsState::REQUIRED_TC_NOT_ACCEPTED;
        return CHIP_NO_ERROR;
    }

    // All validation check succeeded...
    outState = TermsAndConditionsState::OK;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::CommitAcceptance()
{
    if (!mTemporalAcceptance.HasValue())
    {
        return CHIP_NO_ERROR;
    }

    mLatchedAcceptance.SetValue(mTemporalAcceptance.Value());
    return StoreAcceptance(mLatchedAcceptance);
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::GetAcceptance(Optional<TermsAndConditions> & outTermsAndConditions) const
{
    outTermsAndConditions = mTemporalAcceptance;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::GetRequirements(Optional<TermsAndConditions> & outTermsAndConditions) const
{
    outTermsAndConditions = mRequiredAcknowledgements;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::ResetAcceptance()
{
    VerifyOrReturnError(nullptr != mPersistentStorageDelegate, CHIP_ERROR_UNINITIALIZED);

    const chip::StorageKeyName storageKey = DefaultStorageKeyAllocator::TermsAndConditionsAcceptance();

    ReturnErrorOnFailure(mPersistentStorageDelegate->SyncDeleteKeyValue(storageKey.KeyName()));
    mLatchedAcceptance.ClearValue();
    mTemporalAcceptance.ClearValue();

    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::RevertAcceptance()
{
    mTemporalAcceptance = mLatchedAcceptance;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::SetAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions)
{
    mTemporalAcceptance.SetValue(inTermsAndConditions.Value());
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::LoadAcceptance(Optional<TermsAndConditions> & outTermsAndConditions)
{
    uint8_t serializationVersion     = 0;
    uint16_t acknowledgements        = 0;
    uint16_t acknowledgementsVersion = 0;

    chip::TLV::TLVReader tlvReader;
    chip::TLV::TLVType tlvContainer;

    uint8_t buffer[kEstimatedTlvBufferSize] = { 0 };
    uint16_t bufferSize                     = sizeof(buffer);

    VerifyOrReturnError(nullptr != mPersistentStorageDelegate, CHIP_ERROR_UNINITIALIZED);

    const chip::StorageKeyName storageKey = DefaultStorageKeyAllocator::TermsAndConditionsAcceptance();
    CHIP_ERROR err                        = mPersistentStorageDelegate->SyncGetKeyValue(storageKey.KeyName(), &buffer, bufferSize);
    if (CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND == err)
    {
        return CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND;
    }

    VerifyOrReturnError(CHIP_NO_ERROR == err, err);

    tlvReader.Init(buffer, bufferSize);
    ReturnErrorOnFailure(tlvReader.Next(chip::TLV::kTLVType_Structure, chip::TLV::AnonymousTag()));
    ReturnErrorOnFailure(tlvReader.EnterContainer(tlvContainer));
    ReturnErrorOnFailure(tlvReader.Next(kSerializationVersionTag));
    ReturnErrorOnFailure(tlvReader.Get(serializationVersion));
    ReturnErrorOnFailure(tlvReader.Next(kAcceptedAcknowledgementsTag));
    ReturnErrorOnFailure(tlvReader.Get(acknowledgements));
    ReturnErrorOnFailure(tlvReader.Next(kAcceptedAcknowledgementsVersionTag));
    ReturnErrorOnFailure(tlvReader.Get(acknowledgementsVersion));
    ReturnErrorOnFailure(tlvReader.ExitContainer(tlvContainer));

    if (kSerializationVersion != serializationVersion)
    {
        return CHIP_ERROR_VERSION_MISMATCH;
    }

    outTermsAndConditions.SetValue({
        .value   = acknowledgements,
        .version = acknowledgementsVersion,
    });

    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::StoreAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions)
{
    uint8_t buffer[kEstimatedTlvBufferSize] = { 0 };
    chip::TLV::TLVWriter tlvWriter;
    chip::TLV::TLVType tlvContainer;

    VerifyOrReturnError(nullptr != mPersistentStorageDelegate, CHIP_ERROR_UNINITIALIZED);
    VerifyOrReturnError(inTermsAndConditions.HasValue(), CHIP_ERROR_INCORRECT_STATE);

    tlvWriter.Init(buffer, sizeof(buffer));
    ReturnErrorOnFailure(tlvWriter.StartContainer(chip::TLV::AnonymousTag(), chip::TLV::kTLVType_Structure, tlvContainer));
    ReturnErrorOnFailure(tlvWriter.Put(kSerializationVersionTag, kSerializationVersion));
    ReturnErrorOnFailure(tlvWriter.Put(kAcceptedAcknowledgementsTag, inTermsAndConditions.Value().value));
    ReturnErrorOnFailure(tlvWriter.Put(kAcceptedAcknowledgementsVersionTag, inTermsAndConditions.Value().version));
    ReturnErrorOnFailure(tlvWriter.EndContainer(tlvContainer));
    ReturnErrorOnFailure(tlvWriter.Finalize());
    uint32_t lengthWritten = tlvWriter.GetLengthWritten();
    VerifyOrReturnError(CanCastTo<uint16_t>(lengthWritten), CHIP_ERROR_BUFFER_TOO_SMALL);

    const chip::StorageKeyName storageKey = DefaultStorageKeyAllocator::TermsAndConditionsAcceptance();
    ReturnErrorOnFailure(
        mPersistentStorageDelegate->SyncSetKeyValue(storageKey.KeyName(), buffer, static_cast<uint16_t>(lengthWritten)));

    return CHIP_NO_ERROR;
}
