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

#include "DefaultEnhancedSetupFlowProvider.h"

#include <lib/core/CHIPConfig.h>
#include <platform/KeyValueStoreManager.h>

CHIP_ERROR chip::app::DefaultEnhancedSetupFlowProvider::Init(TermsAndConditionsProvider * aTermsAndConditionsProvider)
{
    mTermsAndConditionsProvider = aTermsAndConditionsProvider;
    return CHIP_NO_ERROR;
}

bool chip::app::DefaultEnhancedSetupFlowProvider::HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted()
{
    uint16_t requiredAcknowledgements;
    uint16_t requiredAcknowledgementsVersion;
    uint16_t acceptedAcknowledgements;
    uint16_t acceptedAcknowledgementsVersion;

    mTermsAndConditionsProvider->GetRequirements(requiredAcknowledgements, requiredAcknowledgementsVersion);
    mTermsAndConditionsProvider->GetAcceptance(acceptedAcknowledgements, acceptedAcknowledgementsVersion);

    return (requiredAcknowledgements & acceptedAcknowledgements) == requiredAcknowledgements;
}

bool chip::app::DefaultEnhancedSetupFlowProvider::HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted()
{
    uint16_t requiredAcknowledgements;
    uint16_t requiredAcknowledgementsVersion;
    uint16_t acceptedAcknowledgements;
    uint16_t acceptedAcknowledgementsVersion;

    mTermsAndConditionsProvider->GetRequirements(requiredAcknowledgements, requiredAcknowledgementsVersion);
    mTermsAndConditionsProvider->GetAcceptance(acceptedAcknowledgements, acceptedAcknowledgementsVersion);

    return acceptedAcknowledgementsVersion >= requiredAcknowledgementsVersion;
}

CHIP_ERROR chip::app::DefaultEnhancedSetupFlowProvider::GetTermsAndConditionsRequiredAcknowledgements(uint16_t & value)
{
    uint16_t requiredAcknowledgements;
    uint16_t requiredAcknowledgementsVersion;

    mTermsAndConditionsProvider->GetRequirements(requiredAcknowledgements, requiredAcknowledgementsVersion);

    value = requiredAcknowledgements;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultEnhancedSetupFlowProvider::GetTermsAndConditionsRequiredAcknowledgementsVersion(uint16_t & value)
{
    uint16_t requiredAcknowledgements;
    uint16_t requiredAcknowledgementsVersion;

    mTermsAndConditionsProvider->GetRequirements(requiredAcknowledgements, requiredAcknowledgementsVersion);

    value = requiredAcknowledgementsVersion;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultEnhancedSetupFlowProvider::GetTermsAndConditionsAcceptedAcknowledgements(uint16_t & value)
{
    uint16_t acceptedAcknowledgements;
    uint16_t acceptedAcknowledgementsVersion;

    mTermsAndConditionsProvider->GetAcceptance(acceptedAcknowledgements, acceptedAcknowledgementsVersion);

    value = acceptedAcknowledgements;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultEnhancedSetupFlowProvider::GetTermsAndConditionsAcceptedAcknowledgementsVersion(uint16_t & value)
{
    uint16_t acceptedAcknowledgements;
    uint16_t acceptedAcknowledgementsVersion;

    mTermsAndConditionsProvider->GetAcceptance(acceptedAcknowledgements, acceptedAcknowledgementsVersion);

    value = acceptedAcknowledgementsVersion;
    return CHIP_NO_ERROR;
}

CHIP_ERROR chip::app::DefaultEnhancedSetupFlowProvider::SetTermsAndConditionsAcceptance(uint16_t aTCAcknowledgements,
                                                                                        uint16_t aTCAcknowledgementsVersion)
{
    return mTermsAndConditionsProvider->SetAcceptance(aTCAcknowledgements, aTCAcknowledgementsVersion);
}
