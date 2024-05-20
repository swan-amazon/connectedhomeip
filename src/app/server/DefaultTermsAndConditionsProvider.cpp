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

#include <lib/core/CHIPConfig.h>
#include <platform/KeyValueStoreManager.h>

CHIP_ERROR
chip::app::DefaultTermsAndConditionsProvider::Init(chip::DeviceLayer::PersistedStorage::KeyValueStoreManager * kvsManager)
{
    mKeyValueStoreManager = kvsManager;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::GetAcceptance(uint16_t & aAcknowledgements,
                                                                       uint16_t & aAcknowledgementsVersion)
{
    uint16_t acknowledgements        = 0;
    uint16_t acknowledgementsVersion = 0;

    mKeyValueStoreManager->Get(kAcceptedAcknowledgementsKeyName, &acknowledgements, sizeof(acknowledgements));
    mKeyValueStoreManager->Get(kAcceptedAcknowledgementsVersionKeyName, &acknowledgementsVersion, sizeof(acknowledgementsVersion));

    aAcknowledgements        = acknowledgements;
    aAcknowledgementsVersion = acknowledgementsVersion;

    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::GetRequirements(uint16_t & aAcknowledgements,
                                                                         uint16_t & aAcknowledgementsVersion)
{
    aAcknowledgements        = CHIP_CONFIG_TC_REQUIRED_ACKNOWLEDGEMENTS;
    aAcknowledgementsVersion = CHIP_CONFIG_TC_REQUIRED_ACKNOWLEDGEMENTS_VERSION;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultTermsAndConditionsProvider::SetAcceptance(uint16_t aAcceptedAcknowledgements,
                                                                       uint16_t aAcceptedAcknowledgementsVersion)
{
    mKeyValueStoreManager->Put(kAcceptedAcknowledgementsKeyName, &aAcceptedAcknowledgements, sizeof(aAcceptedAcknowledgements));
    mKeyValueStoreManager->Put(kAcceptedAcknowledgementsVersionKeyName, &aAcceptedAcknowledgementsVersion,
                               sizeof(aAcceptedAcknowledgementsVersion));
    return CHIP_NO_ERROR;
}
