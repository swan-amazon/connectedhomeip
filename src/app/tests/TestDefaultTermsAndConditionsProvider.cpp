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

#include "app/server/DefaultTermsAndConditionsProvider.h"
#include "app/server/TermsAndConditionsProvider.h"

#include <lib/core/CHIPError.h>
#include <lib/core/StringBuilderAdapters.h>
#include <lib/support/TestPersistentStorageDelegate.h>
#include <pw_unit_test/framework.h>

TEST(DefaultTermsAndConditionsProvider, TestInitSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
}

TEST(DefaultTermsAndConditionsProvider, TestNoRequirementsGetRequirementsSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>();

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outTermsAndConditions;
    err = tncProvider.GetAcceptance(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_FALSE(outTermsAndConditions.HasValue());
}

TEST(DefaultTermsAndConditionsProvider, TestNeverAcceptanceGetAcceptanceSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 0b1111'1111'1111'1111,
        .version = 1,
    });

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outTermsAndConditions;
    err = tncProvider.GetAcceptance(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_FALSE(outTermsAndConditions.HasValue());
}

TEST(DefaultTermsAndConditionsProvider, TestTermsAcceptedPersistsSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;
    chip::app::DefaultTermsAndConditionsProvider anotherTncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> newTermsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });

    err = tncProvider.SetAcceptance(newTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outTermsAndConditions;
    err = tncProvider.GetAcceptance(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outTermsAndConditions.Value().value);
    EXPECT_EQ(1, outTermsAndConditions.Value().version);

    err = tncProvider.CommitAcceptance();
    err = tncProvider.GetAcceptance(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outTermsAndConditions.Value().value);
    EXPECT_EQ(1, outTermsAndConditions.Value().version);

    err = anotherTncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    err = anotherTncProvider.GetAcceptance(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outTermsAndConditions.Value().value);
    EXPECT_EQ(1, outTermsAndConditions.Value().version);
}

TEST(DefaultTermsAndConditionsProvider, TestTermsRequiredGetRequirementsSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outTermsAndConditions;
    err = tncProvider.GetRequirements(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outTermsAndConditions.Value().value);
    EXPECT_EQ(1, outTermsAndConditions.Value().version);
}

TEST(DefaultTermsAndConditionsProvider, TestSetAcceptanceGetAcceptanceSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> acceptedTermsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outTermsAndConditions;
    err = tncProvider.GetRequirements(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outTermsAndConditions.Value().value);
    EXPECT_EQ(1, outTermsAndConditions.Value().version);
}

TEST(DefaultTermsAndConditionsProvider, TestRevertAcceptanceGetAcceptanceSuccess)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> termsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });

    err = tncProvider.Init(&storageDelegate, termsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> acceptedTermsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outTermsAndConditions;
    err = tncProvider.GetRequirements(outTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outTermsAndConditions.Value().value);
    EXPECT_EQ(1, outTermsAndConditions.Value().version);

    err = tncProvider.RevertAcceptance();
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outAcceptance2;
    err = tncProvider.GetAcceptance(outAcceptance2);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_FALSE(outAcceptance2.HasValue());
}

TEST(DefaultTermsAndConditionsProvider, TestAcceptanceRequiredTermsMissingFailure)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    chip::Optional<chip::app::TermsAndConditions> requiredTermsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });
    err = tncProvider.Init(&storageDelegate, requiredTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> acceptedTermsAndConditions = chip::Optional<chip::app::TermsAndConditions>({
        .value   = 1,
        .version = 1,
    });
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outAcknowledgementTermsAndConditions;
    err = tncProvider.GetAcceptance(outAcknowledgementTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outAcknowledgementTermsAndConditions.Value().value);
    EXPECT_EQ(1, outAcknowledgementTermsAndConditions.Value().version);

    err = tncProvider.RevertAcceptance();
    EXPECT_EQ(CHIP_NO_ERROR, err);

    chip::Optional<chip::app::TermsAndConditions> outRequiredTermsAndConditions;
    err = tncProvider.GetRequirements(outRequiredTermsAndConditions);
    EXPECT_EQ(CHIP_NO_ERROR, err);
    EXPECT_EQ(1, outRequiredTermsAndConditions.Value().value);
    EXPECT_EQ(1, outRequiredTermsAndConditions.Value().version);
}
