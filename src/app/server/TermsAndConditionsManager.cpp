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

#include "TermsAndConditionsManager.h"

#include <platform/ConfigurationManager.h>

CHIP_ERROR chip::app::TermsAndConditionsManager::GetTCAcceptedVersion(uint16_t & value)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = DeviceLayer::ConfigurationMgr().GetTCAcceptedVersion(value);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "GetTCAcceptedVersion failed with error: %s", ErrorStr(err));
    }
    return err;
}

CHIP_ERROR chip::app::TermsAndConditionsManager::GetTCMinRequiredVersion(uint16_t & value)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = DeviceLayer::ConfigurationMgr().GetTCMinRequiredVersion(value);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "GetTCMinRequiredVersion failed with error: %s", ErrorStr(err));
    }
    return err;
}

CHIP_ERROR chip::app::TermsAndConditionsManager::GetTCAcknowledgements(uint16_t & value)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = DeviceLayer::ConfigurationMgr().GetTCAcknowledgements(value);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "GetTCAcknowledgements failed with error: %s", ErrorStr(err));
    }
    return err;
}

CHIP_ERROR chip::app::TermsAndConditionsManager::GetTCAcknowledgementsRequired(uint16_t & value)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = DeviceLayer::ConfigurationMgr().GetTCAcknowledgementsRequired(value);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "GetTCAcknowledgementsRequired failed with error: %s", ErrorStr(err));
    }
    return err;
}

CHIP_ERROR chip::app::TermsAndConditionsManager::SetTCAcknowledgements(uint16_t tcVersion, uint16_t tcUserResponse)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = DeviceLayer::ConfigurationMgr().StoreTCAcknowledgements(tcVersion, tcUserResponse);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "SetTCAcknowledgements failed with error: %s", ErrorStr(err));
    }
    return err;
}
