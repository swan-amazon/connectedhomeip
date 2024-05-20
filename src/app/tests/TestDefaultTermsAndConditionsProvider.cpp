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

#include <lib/core/CHIPError.h>
#include <lib/support/TestPersistentStorageDelegate.h>
#include <lib/support/UnitTestRegistration.h>
#include <nlunit-test.h>

static void Test_Init_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t requiredAcknowledgements        = 1;
    uint16_t requiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
}

static void Test_NoRequirements_GetRequirements_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t requiredAcknowledgements        = 0;
    uint16_t requiredAcknowledgementsVersion = 0;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance;
    uint16_t outAcknowledgementsVersion;
    err = tncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 0 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 0 == outAcknowledgementsVersion);
}

static void Test_NeverAcceptance_GetAcceptance_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t requiredAcknowledgements        = 0b1111'1111'1111'1111;
    uint16_t requiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance;
    uint16_t outAcknowledgementsVersion;
    err = tncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 0 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 0 == outAcknowledgementsVersion);
}

static void Test_TermsAccepted_Persists_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;
    chip::app::DefaultTermsAndConditionsProvider anotherTncProvider;

    uint16_t requiredAcknowledgements        = 1;
    uint16_t requiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t acceptedTermsAndConditions        = 1;
    uint16_t acceptedTermsAndConditionsVersion = 1;
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions, acceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance;
    uint16_t outAcknowledgementsVersion;
    err = tncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 1 == outAcknowledgementsVersion);

    err = anotherTncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    err = anotherTncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 1 == outAcknowledgementsVersion);
}

static void Test_TermsRequired_GetRequirements_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t initialRequiredAcknowledgements        = 1;
    uint16_t initialRequiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, initialRequiredAcknowledgements, initialRequiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outRequiredAcknowledgements;
    uint16_t outRequiredAcknowledgementsVersion;
    err = tncProvider.GetRequirements(outRequiredAcknowledgements, outRequiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outRequiredAcknowledgements);
    NL_TEST_ASSERT(inSuite, 1 == outRequiredAcknowledgementsVersion);
}

static void Test_SetAcceptance_GetAcceptance_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t requiredAcknowledgements        = 1;
    uint16_t requiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t acceptedTermsAndConditions        = 1;
    uint16_t acceptedTermsAndConditionsVersion = 1;
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions, acceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance;
    uint16_t outAcknowledgementsVersion;
    err = tncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 1 == outAcknowledgementsVersion);
}

static void Test_ClearAcceptance_GetAcceptance_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t requiredAcknowledgements        = 1;
    uint16_t requiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t acceptedTermsAndConditions        = 1;
    uint16_t acceptedTermsAndConditionsVersion = 1;
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions, acceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance;
    uint16_t outAcknowledgementsVersion;
    err = tncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 1 == outAcknowledgementsVersion);

    err = tncProvider.ClearAcceptance();
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance2;
    uint16_t outAcknowledgementsVersion2;
    err = tncProvider.GetAcceptance(outAcceptance2, outAcknowledgementsVersion2);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 0 == outAcceptance2);
    NL_TEST_ASSERT(inSuite, 0 == outAcknowledgementsVersion2);
}

static void Test_ClearAcceptance_GetRequirements_Success(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;

    chip::TestPersistentStorageDelegate storageDelegate;
    chip::app::DefaultTermsAndConditionsProvider tncProvider;

    uint16_t requiredAcknowledgements        = 1;
    uint16_t requiredAcknowledgementsVersion = 1;
    err = tncProvider.Init(&storageDelegate, requiredAcknowledgements, requiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t acceptedTermsAndConditions        = 1;
    uint16_t acceptedTermsAndConditionsVersion = 1;
    err = tncProvider.SetAcceptance(acceptedTermsAndConditions, acceptedTermsAndConditionsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outAcceptance;
    uint16_t outAcknowledgementsVersion;
    err = tncProvider.GetAcceptance(outAcceptance, outAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outAcceptance);
    NL_TEST_ASSERT(inSuite, 1 == outAcknowledgementsVersion);

    err = tncProvider.ClearAcceptance();
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    uint16_t outRequiredAcknowledgements;
    uint16_t outRequiredAcknowledgementsVersion;
    err = tncProvider.GetRequirements(outRequiredAcknowledgements, outRequiredAcknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
    NL_TEST_ASSERT(inSuite, 1 == outRequiredAcknowledgements);
    NL_TEST_ASSERT(inSuite, 1 == outRequiredAcknowledgementsVersion);
}

#define STR_HELPER(x) #x
#define XSTR(x) STR_HELPER(x)
#define NAMED_NL_TEST_DEF(x) NL_TEST_DEF(XSTR(x), x)

static nlTest sTests[] = {
    NAMED_NL_TEST_DEF(Test_Init_Success),
    NAMED_NL_TEST_DEF(Test_NoRequirements_GetRequirements_Success),
    NAMED_NL_TEST_DEF(Test_NeverAcceptance_GetAcceptance_Success),
    NAMED_NL_TEST_DEF(Test_TermsAccepted_Persists_Success),
    NAMED_NL_TEST_DEF(Test_TermsRequired_GetRequirements_Success),
    NAMED_NL_TEST_DEF(Test_SetAcceptance_GetAcceptance_Success),
    NAMED_NL_TEST_DEF(Test_ClearAcceptance_GetAcceptance_Success),
    NAMED_NL_TEST_DEF(Test_ClearAcceptance_GetRequirements_Success),
    NL_TEST_SENTINEL(),
};

static nlTestSuite sDefaultTermsAndConditionsProviderTestSuite = {
    .name  = (const char *) "Terms and Conditions Provider Test Suite",
    .tests = sTests,
};

int TestDefaultTermsAndConditionsProvider()
{
    nlTestRunner(&sDefaultTermsAndConditionsProviderTestSuite, nullptr);
    return nlTestRunnerStats(&sDefaultTermsAndConditionsProviderTestSuite);
}

CHIP_REGISTER_TEST_SUITE(TestDefaultTermsAndConditionsProvider)
