/*
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

#include "app/server/DefaultEnhancedSetupFlowProvider.h"

#include <lib/core/CHIPError.h>
#include <lib/support/UnitTestRegistration.h>
#include <nlunit-test.h>

class FakeTermsAndConditionsProvider : public chip::app::TermsAndConditionsProvider
{
public:
    FakeTermsAndConditionsProvider(uint16_t inAcceptedAcknowledgements, uint16_t inAcceptedAcknowledgementsVersion,
                                   uint16_t inRequiredAcknowledgements, uint16_t inRequiredAcknowledgementsVersion) :
        mAcceptedAcknowledgements(inAcceptedAcknowledgements),
        mAcceptedAcknowledgementsVersion(inAcceptedAcknowledgementsVersion), mRequiredAcknowledgements(inRequiredAcknowledgements),
        mRequiredAcknowledgementsVersion(inRequiredAcknowledgementsVersion)
    {}

    CHIP_ERROR GetAcceptance(uint16_t & outAcknowledgements, uint16_t & outAcknowledgementsVersion) const override
    {
        outAcknowledgements        = mAcceptedAcknowledgements;
        outAcknowledgementsVersion = mAcceptedAcknowledgementsVersion;
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR GetRequirements(uint16_t & outAcknowledgements, uint16_t & outAcknowledgementsVersion) const override
    {
        outAcknowledgements        = mRequiredAcknowledgements;
        outAcknowledgementsVersion = mRequiredAcknowledgementsVersion;
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR SetAcceptance(uint16_t inAcknowledgements, uint16_t inAcknowledgementsVersion) override
    {
        mAcceptedAcknowledgements        = inAcknowledgements;
        mAcceptedAcknowledgementsVersion = inAcknowledgementsVersion;
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR ClearAcceptance() override
    {
        mAcceptedAcknowledgements        = 0;
        mAcceptedAcknowledgementsVersion = 0;
        return CHIP_NO_ERROR;
    }

private:
    uint16_t mAcceptedAcknowledgements;
    uint16_t mAcceptedAcknowledgementsVersion;
    uint16_t mRequiredAcknowledgements;
    uint16_t mRequiredAcknowledgementsVersion;
};

static void Test_NoAcceptanceRequired_CheckAcknowledgementsAccepted_Success(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;

    FakeTermsAndConditionsProvider tncProvider(0, 0, 0, 0);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsBeenAccepted);
}

static void Test_NoAcceptanceRequired_CheckAcknowledgementsVersionAccepted_Success(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsVersionBeenAccepted;

    FakeTermsAndConditionsProvider tncProvider(0, 0, 0, 0);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasTermsVersionBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsVersionBeenAccepted);
}

static void Test_AcceptanceRequired_NoTermsAccepted_CheckAcknowledgementsAccepted_Failure(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;

    FakeTermsAndConditionsProvider tncProvider(0, 0, 1, 1);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, !hasTermsBeenAccepted);
}

static void
Test_AcceptanceRequired_TermsAccepted_TermsVersionOutdated_CheckAcknowledgementsVersionAccepted_Failure(nlTestSuite * inSuite,
                                                                                                        void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;
    bool hasTermsVersionBeenAccepted;

    FakeTermsAndConditionsProvider tncProvider(0, 0, 1, 1);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.SetTermsAndConditionsAcceptance(1, 0);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsBeenAccepted);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasTermsVersionBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, !hasTermsVersionBeenAccepted);
}

static void Test_AcceptanceRequired_TermsAccepted_FutureVersion_CheckAcknowledgementsAccepted_Success(nlTestSuite * inSuite,
                                                                                                      void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;
    bool hasTermsVersionBeenAccepted;

    uint16_t acceptedTerms        = 1;
    uint16_t requiredTerms        = 1;
    uint16_t acceptedTermsVersion = 2;
    uint16_t requiredTermsVersion = 1;

    FakeTermsAndConditionsProvider tncProvider(acceptedTerms, acceptedTermsVersion, requiredTerms, requiredTermsVersion);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsBeenAccepted);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasTermsVersionBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsVersionBeenAccepted);
}

static void Test_AcceptanceRequired_TermsAccepted_Success(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;
    bool hasTermsVersionBeenAccepted;

    FakeTermsAndConditionsProvider tncProvider(0, 0, 1, 1);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.SetTermsAndConditionsAcceptance(1, 1);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsBeenAccepted);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasTermsVersionBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsVersionBeenAccepted);
}

static void Test_AcceptanceRequired_TermsMissing_Failure(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;
    bool hasTermsVersionBeenAccepted;

    uint16_t acceptedTerms        = 0b0111'1111'1111'1111;
    uint16_t requiredTerms        = 0b1111'1111'1111'1111;
    uint16_t acceptedTermsVersion = 1;
    uint16_t requiredTermsVersion = 1;

    FakeTermsAndConditionsProvider tncProvider(acceptedTerms, acceptedTermsVersion, requiredTerms, requiredTermsVersion);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, !hasTermsBeenAccepted);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasTermsVersionBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsVersionBeenAccepted);
}

static void Test_AcceptanceRequired_AllTermsAccepted_CheckAcknowledgementsAccepted_Success(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    bool hasTermsBeenAccepted;
    bool hasTermsVersionBeenAccepted;

    uint16_t acceptedTerms        = 0b1111'1111'1111'1111;
    uint16_t requiredTerms        = 0b1111'1111'1111'1111;
    uint16_t acceptedTermsVersion = 1;
    uint16_t requiredTermsVersion = 1;

    FakeTermsAndConditionsProvider tncProvider(acceptedTerms, acceptedTermsVersion, requiredTerms, requiredTermsVersion);
    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasTermsBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsBeenAccepted);

    err = esfProvider.HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasTermsVersionBeenAccepted);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, hasTermsVersionBeenAccepted);
}

static void Test_ClearAcceptance_RetainsRequirements(nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    uint16_t initialAcceptedTermsAndConditions        = 0;
    uint16_t initialRequiredTermsAndConditions        = 0b1111'1111'1111'1111;
    uint16_t initialAcceptedTermsAndConditionsVersion = 0;
    uint16_t initialRequiredTermsAndConditionsVersion = 1;

    uint16_t outAcceptedTermsAndConditions;
    uint16_t outRequiredTermsAndConditions;
    uint16_t outAcceptedTermsAndConditionsVersion;
    uint16_t outRequiredTermsAndConditionsVersion;

    uint16_t updatedAcceptedTermsAndConditions        = 0b1111'1111'1111'1111;
    uint16_t updatedAcceptedTermsAndConditionsVersion = 1;

    FakeTermsAndConditionsProvider tncProvider(initialAcceptedTermsAndConditions, initialAcceptedTermsAndConditionsVersion,
                                               initialRequiredTermsAndConditions, initialRequiredTermsAndConditionsVersion);

    chip::app::DefaultEnhancedSetupFlowProvider esfProvider;

    err = esfProvider.Init(&tncProvider);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.SetTermsAndConditionsAcceptance(updatedAcceptedTermsAndConditions, updatedAcceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.GetTermsAndConditionsRequiredAcknowledgements(outRequiredTermsAndConditions);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outRequiredTermsAndConditions == initialRequiredTermsAndConditions);

    err = esfProvider.GetTermsAndConditionsRequiredAcknowledgementsVersion(outRequiredTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outRequiredTermsAndConditionsVersion == initialRequiredTermsAndConditionsVersion);

    err = esfProvider.GetTermsAndConditionsAcceptedAcknowledgements(outAcceptedTermsAndConditions);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outAcceptedTermsAndConditions == updatedAcceptedTermsAndConditions);

    err = esfProvider.GetTermsAndConditionsAcceptedAcknowledgementsVersion(outAcceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outAcceptedTermsAndConditionsVersion == updatedAcceptedTermsAndConditionsVersion);

    err = esfProvider.ClearTermsAndConditionsAcceptance();
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = esfProvider.GetTermsAndConditionsRequiredAcknowledgements(outRequiredTermsAndConditions);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outRequiredTermsAndConditions == initialRequiredTermsAndConditions);

    err = esfProvider.GetTermsAndConditionsRequiredAcknowledgementsVersion(outRequiredTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outRequiredTermsAndConditionsVersion == initialRequiredTermsAndConditionsVersion);

    err = esfProvider.GetTermsAndConditionsAcceptedAcknowledgements(outAcceptedTermsAndConditions);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outAcceptedTermsAndConditions == 0);

    err = esfProvider.GetTermsAndConditionsAcceptedAcknowledgementsVersion(outAcceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, outAcceptedTermsAndConditionsVersion == 0);
}

#define STR_HELPER(x) #x
#define XSTR(x) STR_HELPER(x)
#define NAMED_NL_TEST_DEF(x) NL_TEST_DEF(XSTR(x), x)

static nlTest sTests[] = {
    NAMED_NL_TEST_DEF(Test_NoAcceptanceRequired_CheckAcknowledgementsAccepted_Success),
    NAMED_NL_TEST_DEF(Test_NoAcceptanceRequired_CheckAcknowledgementsVersionAccepted_Success),
    NAMED_NL_TEST_DEF(Test_AcceptanceRequired_NoTermsAccepted_CheckAcknowledgementsAccepted_Failure),
    NAMED_NL_TEST_DEF(Test_AcceptanceRequired_TermsAccepted_TermsVersionOutdated_CheckAcknowledgementsVersionAccepted_Failure),
    NAMED_NL_TEST_DEF(Test_AcceptanceRequired_TermsAccepted_FutureVersion_CheckAcknowledgementsAccepted_Success),
    NAMED_NL_TEST_DEF(Test_AcceptanceRequired_TermsAccepted_Success),
    NAMED_NL_TEST_DEF(Test_AcceptanceRequired_TermsMissing_Failure),
    NAMED_NL_TEST_DEF(Test_AcceptanceRequired_AllTermsAccepted_CheckAcknowledgementsAccepted_Success),
    NAMED_NL_TEST_DEF(Test_ClearAcceptance_RetainsRequirements),
    NL_TEST_SENTINEL(),
};

static nlTestSuite sEnhancedSetupFlowProviderTestSuite = {
    .name  = "Enhanced Setup Flow Provider Test Suite",
    .tests = sTests,
};

int TestDefaultEnhancedSetupFlowProvider()
{
    nlTestRunner(&sEnhancedSetupFlowProviderTestSuite, nullptr);
    return nlTestRunnerStats(&sEnhancedSetupFlowProviderTestSuite);
}

CHIP_REGISTER_TEST_SUITE(TestDefaultEnhancedSetupFlowProvider)
