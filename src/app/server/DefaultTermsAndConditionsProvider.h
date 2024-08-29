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
#include <lib/core/CHIPPersistentStorageDelegate.h>
#include <lib/core/Optional.h>

namespace chip {
namespace app {
class DefaultTermsAndConditionsProvider : public TermsAndConditionsProvider
{
public:
    /**
     * @brief Initializes the TermsAndConditionsProvider.
     *
     * @param[in] inPersistentStorageDelegate Persistent storage delegate dependency.
     */
    CHIP_ERROR Init(PersistentStorageDelegate * const inPersistentStorageDelegate,
                    const chip::Optional<chip::app::TermsAndConditions> & inRequiredTermsAndConditions);

    CHIP_ERROR CheckAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions,
                               TermsAndConditionsState & outState) const override;

    CHIP_ERROR CommitAcceptance() override;

    CHIP_ERROR GetAcceptance(Optional<TermsAndConditions> & outTermsAndConditions) const override;

    CHIP_ERROR GetRequirements(Optional<TermsAndConditions> & outTermsAndConditions) const override;

    CHIP_ERROR ResetAcceptance() override;

    CHIP_ERROR RevertAcceptance() override;

    CHIP_ERROR SetAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions) override;

private:
    CHIP_ERROR LoadAcceptance(Optional<TermsAndConditions> & outTermsAndConditions);

    CHIP_ERROR StoreAcceptance(const Optional<TermsAndConditions> & inTermsAndConditions);

    PersistentStorageDelegate * mPersistentStorageDelegate;

    Optional<TermsAndConditions> mLatchedAcceptance;
    Optional<TermsAndConditions> mTemporalAcceptance;
    Optional<TermsAndConditions> mRequiredAcknowledgements;
};

} // namespace app
} // namespace chip
