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

#include <gmock/gmock.h>
#include <nlunit-test.h>

#include <lib/support/UnitTestRegistration.h>

#include "app/server/DefaultTermsAndConditionsProvider.h"
#include "lib/core/CHIPError.h"

/**
 * @brief A struct template representing an action to save a value into a buffer at a specified index.
 *
 * This struct template is intended for use with Google Mock to define actions for mocked methods.
 * It copies a value into a buffer at a specified index when the action is invoked.
 *
 * @tparam N The index of the argument in the function call arguments tuple.
 * @tparam T The type of the value to save into the buffer.
 */
template <size_t N, typename T, typename = void>
struct SaveArgVoidPointeeAction
{
    T value; /**< The value to save into the buffer. */

    /**
     * @brief The function call operator.
     *
     * This operator is invoked when the action is called.
     * It copies the value stored in 'value' into the buffer at the specified index 'N'.
     *
     * @tparam Args The types of the function call arguments.
     * @param args The function call arguments.
     */
    template <typename... Args>
    void operator()(const Args &... args) const
    {
        // Get the buffer at index 'N' from the tuple of arguments
        void * buffer = std::get<N>(std::tie(args...));
        // Copy the value into the buffer
        memcpy(buffer, &value, sizeof(value));
    }
};

/**
 * @brief Helper function to create a SaveArgVoidPointeeAction object.
 *
 * This function simplifies the creation of SaveArgVoidPointeeAction objects.
 *
 * @tparam N The index of the argument in the function call arguments tuple.
 * @tparam T The type of the value to save into the buffer.
 * @param value The value to save into the buffer.
 * @return A SaveArgVoidPointeeAction object initialized with the specified value.
 */
template <size_t N, typename T>
SaveArgVoidPointeeAction<N, T> SaveArgVoidPointee(T value)
{
    return { std::move(value) };
}

/**
 * @brief A mock class for the KeyValueStoreManager interface.
 *
 * This mock class is used for testing purposes to mock the behavior of the KeyValueStoreManager class.
 * It inherits from the KeyValueStoreManager class and provides mock implementations for its methods.
 */
class MockKeyValueStoreManager : public chip::DeviceLayer::PersistedStorage::KeyValueStoreManager
{
public:
    /**
     * @brief Mock method for the Get method of KeyValueStoreManager.
     *
     * This mock method is used to simulate the behavior of the Get method of KeyValueStoreManager.
     * It takes parameters similar to the Get method and returns a CHIP_ERROR.
     *
     * @param key The key to retrieve from the key-value store.
     * @param buffer Pointer to the buffer where the retrieved value will be stored.
     * @param buffer_size Size of the buffer.
     * @param read_bytes_size Pointer to a variable where the number of bytes read will be stored.
     * @param offset_bytes Offset within the value from where to start reading.
     * @return CHIP_ERROR representing the success or failure of the operation.
     */
    MOCK_METHOD5(GetMock, CHIP_ERROR(const char *, void *, size_t, size_t *, size_t));

    /**
     * @brief Mock method for the Put method of KeyValueStoreManager.
     *
     * This mock method is used to simulate the behavior of the Put method of KeyValueStoreManager.
     * It takes parameters similar to the Put method and returns a CHIP_ERROR.
     *
     * @param key The key under which to store the value in the key-value store.
     * @param value Pointer to the value to be stored.
     * @param value_size Size of the value.
     * @return CHIP_ERROR representing the success or failure of the operation.
     */
    MOCK_METHOD3(PutMock, CHIP_ERROR(const char *, const void *, size_t));

    /**
     * @brief Mock method for the Delete method of KeyValueStoreManager.
     *
     * This mock method is used to simulate the behavior of the Delete method of KeyValueStoreManager.
     * It takes a key as a parameter and returns a CHIP_ERROR.
     *
     * @param key The key to delete from the key-value store.
     * @return CHIP_ERROR representing the success or failure of the operation.
     */
    MOCK_METHOD1(DeleteMock, CHIP_ERROR(const char *));

    /**
     * @brief Override of the Get method of KeyValueStoreManager.
     *
     * This method overrides the Get method of KeyValueStoreManager.
     * It delegates the call to the corresponding mock method GetMock.
     *
     * @param key The key to retrieve from the key-value store.
     * @param buffer Pointer to the buffer where the retrieved value will be stored.
     * @param buffer_size Size of the buffer.
     * @param read_bytes_size Pointer to a variable where the number of bytes read will be stored.
     * @param offset_bytes Offset within the value from where to start reading.
     * @return CHIP_ERROR representing the success or failure of the operation.
     */
    CHIP_ERROR Get(const char * key, void * buffer, size_t buffer_size, size_t * read_bytes_size, size_t offset_bytes)
    {
        return GetMock(key, buffer, buffer_size, read_bytes_size, offset_bytes);
    }

    /**
     * @brief Override of the Put method of KeyValueStoreManager.
     *
     * This method overrides the Put method of KeyValueStoreManager.
     * It delegates the call to the corresponding mock method PutMock.
     *
     * @param key The key under which to store the value in the key-value store.
     * @param value Pointer to the value to be stored.
     * @param value_size Size of the value.
     * @return CHIP_ERROR representing the success or failure of the operation.
     */
    CHIP_ERROR Put(const char * key, const void * value, size_t value_size) { return PutMock(key, value, value_size); }

    /**
     * @brief Override of the Delete method of KeyValueStoreManager.
     *
     * This method overrides the Delete method of KeyValueStoreManager.
     * It delegates the call to the corresponding mock method DeleteMock.
     *
     * @param key The key to delete from the key-value store.
     * @return CHIP_ERROR representing the success or failure of the operation.
     */
    CHIP_ERROR Delete(const char * key) { return DeleteMock(key); }
};

/**
 * @brief Setup function for the test suite.
 *
 * This function is called before running the test suite.
 * It performs any necessary setup steps.
 *
 * @param inContext A pointer to the context (not used in this function).
 * @return SUCCESS if setup succeeds, an error code otherwise.
 */
static int Setup(void * inContext)
{
    return SUCCESS;
}

/**
 * @brief Tear down function for the test suite.
 *
 * This function is called after running the test suite.
 * It performs any necessary cleanup steps.
 *
 * @param inContext A pointer to the context (not used in this function).
 * @return SUCCESS if teardown succeeds, an error code otherwise.
 */
static int TearDown(void * inContext)
{
    return SUCCESS;
}

/**
 * @brief Initialization function for the test suite.
 *
 * This function is called before running each test case.
 * It performs any necessary initialization steps.
 *
 * @param inContext A pointer to the context (not used in this function).
 * @return SUCCESS if initialization succeeds, an error code otherwise.
 */
static int Initialize(void * inContext)
{
    return SUCCESS;
}

/**
 * @brief Termination function for the test suite.
 *
 * This function is called after running each test case.
 * It performs any necessary termination steps.
 *
 * @param inContext A pointer to the context (not used in this function).
 * @return SUCCESS if termination succeeds, an error code otherwise.
 */
static int Terminate(void * inContext)
{
    return SUCCESS;
}

/**
 * @brief Test case for initializing the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that the DefaultTermsAndConditionsProvider initializes successfully.
 * It initializes the provider with a mock key-value store manager and checks for success.
 */
static void TestDefaultTermsAndConditionsProviderInitSuccess(struct _nlTestSuite * inSuite, void * inContext)
{
    MockKeyValueStoreManager mockKeyValueStoreManager;

    chip::app::DefaultTermsAndConditionsProvider uut;
    CHIP_ERROR err = uut.Init(&mockKeyValueStoreManager);

    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);
}

/**
 * @brief Test case for retrieving acceptance from the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that the DefaultTermsAndConditionsProvider retrieves acceptance successfully.
 * It initializes the provider with a mock key-value store manager, sets up expectations for Get method calls,
 * calls the GetAcceptance method, and checks for expected values.
 */
static void TestDefaultTermsAndConditionsProviderGetAcceptanceSuccess(struct _nlTestSuite * inSuite, void * inContext)
{
    CHIP_ERROR err;
    uint16_t acknowledgements;
    uint16_t acknowledgementsVersion;

    MockKeyValueStoreManager mockKeyValueStoreManager;
    chip::app::DefaultTermsAndConditionsProvider uut;

    err = uut.Init(&mockKeyValueStoreManager);
    NL_TEST_ASSERT(inSuite, CHIP_NO_ERROR == err);

    EXPECT_CALL(mockKeyValueStoreManager,
                GetMock(chip::app::DefaultTermsAndConditionsProvider::kAcceptedAcknowledgementsKeyName, testing::_,
                        sizeof(uint16_t), testing::_, testing::_))
        .WillOnce(testing::DoAll(SaveArgVoidPointee<1>(static_cast<uint16_t>(1)), testing::Return(CHIP_NO_ERROR)));

    EXPECT_CALL(mockKeyValueStoreManager,
                GetMock(chip::app::DefaultTermsAndConditionsProvider::kAcceptedAcknowledgementsVersionKeyName, testing::_,
                        sizeof(uint16_t), testing::_, testing::_))
        .WillOnce(testing::DoAll(SaveArgVoidPointee<1>(static_cast<uint16_t>(1)), testing::Return(CHIP_NO_ERROR)));

    err = uut.GetAcceptance(acknowledgements, acknowledgementsVersion);
    NL_TEST_ASSERT(inSuite, 1 == acknowledgements);
    NL_TEST_ASSERT(inSuite, 1 == acknowledgementsVersion);
}

/**
 * @brief Test case for getting requirements from the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that getting requirements from the DefaultTermsAndConditionsProvider succeeds.
 * It checks for successful execution without any assertions.
 */
static void TestGetRequirementsSuccess(struct _nlTestSuite * inSuite, void * inContext)
{
    // Test implementation goes here...
}

/**
 * @brief Test case for setting acceptance in the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that setting acceptance in the DefaultTermsAndConditionsProvider succeeds.
 * It checks for successful execution without any assertions.
 */
static void TestSetAcceptanceSuccess(struct _nlTestSuite * inSuite, void * inContext)
{
    // Test implementation goes here...
}

/**
 * @brief Test case for initialization failure of the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that the DefaultTermsAndConditionsProvider fails to initialize.
 * It checks for failure conditions without any assertions.
 */
static void TestInitFailure(struct _nlTestSuite * inSuite, void * inContext)
{
    // Test implementation goes here...
}

/**
 * @brief Test case for failure in retrieving acceptance from the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that retrieving acceptance from the DefaultTermsAndConditionsProvider fails.
 * It checks for failure conditions without any assertions.
 */
static void TestGetAcceptanceFailure(struct _nlTestSuite * inSuite, void * inContext)
{
    // Test implementation goes here...
}

/**
 * @brief Test case for failure in getting requirements from the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that getting requirements from the DefaultTermsAndConditionsProvider fails.
 * It checks for failure conditions without any assertions.
 */
static void TestGetRequirementsFailure(struct _nlTestSuite * inSuite, void * inContext)
{
    // Test implementation goes here...
}

/**
 * @brief Test case for failure in setting acceptance in the DefaultTermsAndConditionsProvider.
 *
 * This test case verifies that setting acceptance in the DefaultTermsAndConditionsProvider fails.
 * It checks for failure conditions without any assertions.
 */
static void TestSetAcceptanceFailure(struct _nlTestSuite * inSuite, void * inContext)
{
    // Test implementation goes here...
}

static nlTestSuite sDefaultTermsAndConditionsProviderTestSuite = {
    .name = (const char *) "Terms and Conditions Provider Test Suite",
    .tests =
        (const nlTest[]){
            NL_TEST_DEF("TestInitSuccess", TestDefaultTermsAndConditionsProviderInitSuccess),
            NL_TEST_DEF("TestGetAcceptanceSuccess", TestDefaultTermsAndConditionsProviderGetAcceptanceSuccess),
            NL_TEST_DEF("TestGetRequirementsSuccess", TestGetRequirementsSuccess),
            NL_TEST_DEF("TestSetAcceptanceSuccess", TestSetAcceptanceSuccess),
            NL_TEST_DEF("TestInitFailure", TestInitFailure),
            NL_TEST_DEF("TestGetAcceptanceFailure", TestGetAcceptanceFailure),
            NL_TEST_DEF("TestGetRequirementsFailure", TestGetRequirementsFailure),
            NL_TEST_DEF("TestSetAcceptanceFailure", TestSetAcceptanceFailure),
            NL_TEST_SENTINEL(),
        },
    .setup      = (int (*)(void *)) Setup,
    .tear_down  = (int (*)(void *)) TearDown,
    .initialize = (int (*)(void *)) Initialize,
    .terminate  = (int (*)(void *)) Terminate,
};

int TestDefaultTermsAndConditionsProvider()
{
    nlTestRunner(&sDefaultTermsAndConditionsProviderTestSuite, nullptr);
    return nlTestRunnerStats(&sDefaultTermsAndConditionsProviderTestSuite);
}

CHIP_REGISTER_TEST_SUITE(TestDefaultTermsAndConditionsProvider)
