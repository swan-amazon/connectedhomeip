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
#include <lib/core/Optional.h>

namespace chip {
namespace app {

typedef struct sTermsAndConditions
{
    uint16_t value;
    uint16_t version;
} TermsAndConditions;

typedef enum eTermsAndConditionsState
{
    OK                               = 0,
    TC_ACKNOWLEDGEMENTS_NOT_RECEIVED = 1,
    TC_MIN_VERSION_NOT_MET           = 2,
    REQUIRED_TC_NOT_ACCEPTED         = 3,
} TermsAndConditionsState;

/**
 * @brief Data access layer for the required terms and conditions and the store for the user acceptance.
 */
class TermsAndConditionsProvider
{
public:
    virtual ~TermsAndConditionsProvider() = default;

    /**
     * @brief Checks the acceptance status without latching the value, nor temporal storage.
     */
    virtual CHIP_ERROR CheckAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions,
                                       TermsAndConditionsState & outState) const = 0;

    /**
     * @brief Commit the persistent acceptance status of the required terms and conditions.
     */
    virtual CHIP_ERROR CommitAcceptance() = 0;

    /**
     * @brief Retrieves the latest acceptance status of the required terms and conditions.
     */
    virtual CHIP_ERROR GetAcceptance(Optional<TermsAndConditions> & outTermsAndConditions) const = 0;

    /**
     * @brief Retrieves the requirements of the terms and conditions.
     */
    virtual CHIP_ERROR GetRequirements(Optional<TermsAndConditions> & outTermsAndConditions) const = 0;

    /**
     * @brief Reset the persisted acceptance status of the required terms and conditions.
     */
    virtual CHIP_ERROR ResetAcceptance() = 0;

    /**
     * @brief Clear the temporary acceptance status of the required terms and conditions.
     */
    virtual CHIP_ERROR RevertAcceptance() = 0;

    /**
     * @brief Sets the acceptance status of the required terms and conditions.
     */
    virtual CHIP_ERROR SetAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions) = 0;
};

} // namespace app
} // namespace chip
