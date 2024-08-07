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

#pragma once

#include <stdint.h>

#include <lib/core/CHIPError.h>

namespace chip {
namespace app {

/**
 * This class provides access to the state of the Enhanced Setup Flow feature.
 */
class EnhancedSetupFlowProvider
{
public:
    virtual ~EnhancedSetupFlowProvider() = default;

    /**
     * @param[out] outAccepted true if the required acknowledgements have been accepted, false otherwise.
     */
    virtual CHIP_ERROR HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(bool & outAccepted) const = 0;

    /**
     * @param[out] outAccepted true if the required acknowledgements version has been accepted, false otherwise.
     */
    virtual CHIP_ERROR HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(bool & outAccepted) const = 0;

    /**
     * @param[out] outValue The version of the required acknowledgements.
     */
    virtual CHIP_ERROR GetTermsAndConditionsRequiredAcknowledgements(uint16_t & outValue) const = 0;

    /**
     * @param[out] outValue The outValue of the required acknowledgements version.
     */
    virtual CHIP_ERROR GetTermsAndConditionsRequiredAcknowledgementsVersion(uint16_t & outValue) const = 0;

    /**
     * @param[out] outValue The outValue of the accepted acknowledgements.
     */
    virtual CHIP_ERROR GetTermsAndConditionsAcceptedAcknowledgements(uint16_t & outValue) const = 0;

    /**
     * @param[out] outValue The outValue of the accepted acknowledgements version.
     */
    virtual CHIP_ERROR GetTermsAndConditionsAcceptedAcknowledgementsVersion(uint16_t & outValue) const = 0;

    /**
     * @param[in] inTCAcknowledgements The acknowledgements to accept.
     * @param[in] inTCAcknowledgementsVersionValue The version of the acknowledgements to accept.
     */
    virtual CHIP_ERROR SetTermsAndConditionsAcceptance(uint16_t inTCAcknowledgementsValue,
                                                       uint16_t inTCAcknowledgementsVersionValue) = 0;

    /**
     * Reset the terms and conditions acceptance. The terms and conditions should be cleared on factory reset or if failure occurs
     * during a failsafe context.
     */
    virtual CHIP_ERROR ClearTermsAndConditionsAcceptance() = 0;
};

} // namespace app
} // namespace chip
