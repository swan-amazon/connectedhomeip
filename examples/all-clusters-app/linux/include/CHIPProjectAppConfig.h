/*
 *
 *    Copyright (c) 2022-2024 Project CHIP Authors
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

/**
 *    @file
 *          Example project configuration file for CHIP.
 *
 *          This is a place to put application or project-specific overrides
 *          to the default configuration values for general CHIP features.
 *
 */

#pragma once

// include the CHIPProjectConfig from config/standalone
#include <CHIPProjectConfig.h>

// All clusters app has 3 group endpoints. This needs to defined here so that
// CHIP_CONFIG_MAX_GROUPS_PER_FABRIC is properly configured.
#define CHIP_CONFIG_MAX_GROUP_ENDPOINTS_PER_FABRIC 3

// Allows app options (ports) to be configured on launch of app
#define CHIP_DEVICE_ENABLE_PORT_PARAMS 1

// Expose the device type in the advertisement for CI testing.
#define CHIP_DEVICE_CONFIG_ENABLE_COMMISSIONABLE_DEVICE_TYPE 1

// Marks that a ModeBase Derived cluster is being used.
#define MATTER_DM_PLUGIN_MODE_BASE

// Enable batching of up to 5 commands.
#define CHIP_CONFIG_MAX_PATHS_PER_INVOKE 5

#define CHIP_CONFIG_ENABLE_BDX_LOG_TRANSFER 1

// Claim a device type while advertising that matches the device type on our
// endpoint 1.  0x0101 is the "Dimmable Light" device type.
#define CHIP_DEVICE_CONFIG_DEVICE_TYPE 0x0101

/**
 * @brief Configures the required terms and conditions acknowledgements.
 *
 * This macro defines the required terms and conditions acknowledgements bitmask. The bit-field is 16 bits long, so the possible
 * value range is [0, 65535). This setting can be used to require that terms and conditions are presented to the user during
 * commissioning.
 */
#define CHIP_CONFIG_TC_REQUIRED_ACKNOWLEDGEMENTS 1 // Require that terms and conditions ordinal 1 must be accepted.

/**
 * @brief Configures the latest known version of the terms and conditions.
 *
 * This macro defines the version number of the latest terms and conditions. It allows the application to iterate on revisions of
 * the terms and conditions. A value of 0 indicates that no specific version is required. This setting can be used to enforce
 * version-specific terms and conditions acknowledgements in the application. When the set of terms and conditions needs to be
 * changes, the version number should be monotomically increased. If the lateast terms and conditions version is updated (most
 * likely during an OTA) then this may signal to the Administrator that updated terms and conditions should be presented to the
 * user.
 */
#define CHIP_CONFIG_TC_REQUIRED_ACKNOWLEDGEMENTS_VERSION 1 // The current terms and conditions revision is 1.
