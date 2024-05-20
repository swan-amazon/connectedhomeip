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

#include "EnhancedSetupFlowProvider.h"

#include <stdint.h>

#include <lib/core/CHIPError.h>

#include "TermsAndConditionsProvider.h"

namespace chip {
namespace app {
class DefaultEnhancedSetupFlowProvider : public EnhancedSetupFlowProvider
{
public:
    /**
     * @brief Initializes the EnhancedSetupFlowProvider.
     *
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR Init(TermsAndConditionsProvider * aTermsAndConditionsProvider);

    /**
     * @brief Checks if the required terms and conditions acknowledgements have been accepted.
     *
     * @return true if the required acknowledgements have been accepted, false otherwise.
     */
    virtual bool HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted();

    /**
     * @brief Checks if the required terms and conditions acknowledgements version has been accepted.
     *
     * @return true if the required acknowledgements version has been accepted, false otherwise.
     */
    virtual bool HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted();

    /**
     * @brief Retrieves the required terms and conditions acknowledgements.
     *
     * @param[out] value The value of the required acknowledgements.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR GetTermsAndConditionsRequiredAcknowledgements(uint16_t & value);

    /**
     * @brief Retrieves the required terms and conditions acknowledgements version.
     *
     * @param[out] value The value of the required acknowledgements version.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR GetTermsAndConditionsRequiredAcknowledgementsVersion(uint16_t & value);

    /**
     * @brief Retrieves the accepted terms and conditions acknowledgements.
     *
     * @param[out] value The value of the accepted acknowledgements.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR GetTermsAndConditionsAcceptedAcknowledgements(uint16_t & value);

    /**
     * @brief Retrieves the accepted terms and conditions acknowledgements version.
     *
     * @param[out] value The value of the accepted acknowledgements version.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR GetTermsAndConditionsAcceptedAcknowledgementsVersion(uint16_t & value);

    /**
     * @brief Sets the acceptance status of the terms and conditions.
     *
     * @param[in] aTCAcknowledgements The acknowledgements to accept.
     * @param[in] aTCAcknowledgementsVersion The version of the acknowledgements to accept.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR SetTermsAndConditionsAcceptance(uint16_t aTCAcknowledgements, uint16_t aTCAcknowledgementsVersion);

private:
    TermsAndConditionsProvider * mTermsAndConditionsProvider; /**< TermsAndConditionsProvider instance. */
};

}; // namespace app
}; // namespace chip
