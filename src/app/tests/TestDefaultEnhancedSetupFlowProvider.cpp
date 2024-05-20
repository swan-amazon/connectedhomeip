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

#include <nlunit-test.h>

#include <lib/support/UnitTestRegistration.h>

static int Setup(void * inContext)
{
    return SUCCESS;
}

static int TearDown(void * inContext)
{
    return SUCCESS;
}

static int Initialize(void * inContext)
{
    return SUCCESS;
}

static int Terminate(void * inContext)
{
    return SUCCESS;
}

static void TestDefaultEnhancedSetupFlowProvider(struct _nlTestSuite * inSuite, void * inContext)
{
    NL_TEST_ASSERT(inSuite, true);
}

static nlTestSuite sEnhancedSetupFlowProviderTestSuite = {
    .name = (const char *) "Enhanced Setup Flow Provider Test Suite",
    .tests =
        (const nlTest[]){
            NL_TEST_DEF("Enhanced Setup Flow Provider Test", TestDefaultEnhancedSetupFlowProvider),
            NL_TEST_SENTINEL(),
        },
    .setup      = (int (*)(void *)) Setup,
    .tear_down  = (int (*)(void *)) TearDown,
    .initialize = (int (*)(void *)) Initialize,
    .terminate  = (int (*)(void *)) Terminate,
};

int TestDefaultEnhancedSetupFlowProvider()
{
    nlTestRunner(&sEnhancedSetupFlowProviderTestSuite, nullptr);
    return nlTestRunnerStats(&sEnhancedSetupFlowProviderTestSuite);
}

CHIP_REGISTER_TEST_SUITE(TestDefaultEnhancedSetupFlowProvider)
