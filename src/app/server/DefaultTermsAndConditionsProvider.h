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

#include "TermsAndConditionsProvider.h"

#include <stdint.h>

#include <lib/core/CHIPError.h>
#include <platform/KeyValueStoreManager.h>

namespace chip {
namespace app {
class DefaultTermsAndConditionsProvider : public TermsAndConditionsProvider
{
public:
    static constexpr char kAcceptedAcknowledgementsKeyName[]        = "tc-acceptedacknowledgements";
    static constexpr char kAcceptedAcknowledgementsVersionKeyName[] = "tc-acceptedacknowledgementsversion";

    /**
     * @brief Initializes the TermsAndConditionsProvider.
     *
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR Init(chip::DeviceLayer::PersistedStorage::KeyValueStoreManager * kvsManager);

    /**
     * @brief Retrieves the acceptance status of the required terms and conditions.
     *
     * @param[out] aAcknowledgements The number of acknowledgements accepted.
     * @param[out] aAcknowledgementsVersion The version of the accepted acknowledgements.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR GetAcceptance(uint16_t & aAcknowledgements, uint16_t & aAcknowledgementsVersion);

    /**
     * @brief Retrieves the requirements of the terms and conditions.
     *
     * @param[out] aAcknowledgements The number of required acknowledgements.
     * @param[out] aAcknowledgementsVersion The version of the required acknowledgements.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR GetRequirements(uint16_t & aAcknowledgements, uint16_t & aAcknowledgementsVersion);

    /**
     * @brief Sets the acceptance status of the required terms and conditions.
     *
     * @param[in] aAcknowledgements The number of acknowledgements to accept.
     * @param[in] aAcknowledgementsVersion The version of the acknowledgements to accept.
     * @return CHIP_ERROR On success returns CHIP_NO_ERROR, otherwise returns an error code.
     */
    virtual CHIP_ERROR SetAcceptance(uint16_t aAcknowledgements, uint16_t aAcknowledgementsVersion);

private:
    chip::DeviceLayer::PersistedStorage::KeyValueStoreManager * mKeyValueStoreManager;
};

}; // namespace app
}; // namespace chip
