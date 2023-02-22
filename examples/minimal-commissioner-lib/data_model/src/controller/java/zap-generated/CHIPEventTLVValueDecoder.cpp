/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#include <controller/java/CHIPAttributeTLVValueDecoder.h>

#include <app-common/zap-generated/cluster-objects.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/ids/Events.h>
#include <app/data-model/DecodableList.h>
#include <app/data-model/Decode.h>
#include <jni.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>
#include <lib/support/TypeTraits.h>

namespace chip {

jobject DecodeEventValue(const app::ConcreteEventPath & aPath, TLV::TLVReader & aReader, CHIP_ERROR * aError)
{
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();
    CHIP_ERROR err = CHIP_NO_ERROR;

    switch (aPath.mClusterId)
    {
    case app::Clusters::Identify::Id: {
        using namespace app::Clusters::Identify;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::Descriptor::Id: {
        using namespace app::Clusters::Descriptor;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::AccessControl::Id: {
        using namespace app::Clusters::AccessControl;
        switch (aPath.mEventId)
        {
        case Events::AccessControlEntryChanged::Id: {
            Events::AccessControlEntryChanged::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value_adminNodeID;
            if (cppValue.adminNodeID.IsNull())
            {
                value_adminNodeID = nullptr;
            }
            else
            {
                std::string value_adminNodeIDClassName     = "java/lang/Long";
                std::string value_adminNodeIDCtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(value_adminNodeIDClassName.c_str(),
                                                                               value_adminNodeIDCtorSignature.c_str(),
                                                                               cppValue.adminNodeID.Value(), value_adminNodeID);
            }

            jobject value_adminPasscodeID;
            if (cppValue.adminPasscodeID.IsNull())
            {
                value_adminPasscodeID = nullptr;
            }
            else
            {
                std::string value_adminPasscodeIDClassName     = "java/lang/Integer";
                std::string value_adminPasscodeIDCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                    value_adminPasscodeIDClassName.c_str(), value_adminPasscodeIDCtorSignature.c_str(),
                    cppValue.adminPasscodeID.Value(), value_adminPasscodeID);
            }

            jobject value_changeType;
            std::string value_changeTypeClassName     = "java/lang/Integer";
            std::string value_changeTypeCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                value_changeTypeClassName.c_str(), value_changeTypeCtorSignature.c_str(), static_cast<uint8_t>(cppValue.changeType),
                value_changeType);

            jobject value_latestValue;
            if (cppValue.latestValue.IsNull())
            {
                value_latestValue = nullptr;
            }
            else
            {
                jobject value_latestValue_privilege;
                std::string value_latestValue_privilegeClassName     = "java/lang/Integer";
                std::string value_latestValue_privilegeCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                    value_latestValue_privilegeClassName.c_str(), value_latestValue_privilegeCtorSignature.c_str(),
                    static_cast<uint8_t>(cppValue.latestValue.Value().privilege), value_latestValue_privilege);
                jobject value_latestValue_authMode;
                std::string value_latestValue_authModeClassName     = "java/lang/Integer";
                std::string value_latestValue_authModeCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                    value_latestValue_authModeClassName.c_str(), value_latestValue_authModeCtorSignature.c_str(),
                    static_cast<uint8_t>(cppValue.latestValue.Value().authMode), value_latestValue_authMode);
                jobject value_latestValue_subjects;
                if (cppValue.latestValue.Value().subjects.IsNull())
                {
                    value_latestValue_subjects = nullptr;
                }
                else
                {
                    chip::JniReferences::GetInstance().CreateArrayList(value_latestValue_subjects);

                    auto iter_value_latestValue_subjects_3 = cppValue.latestValue.Value().subjects.Value().begin();
                    while (iter_value_latestValue_subjects_3.Next())
                    {
                        auto & entry_3 = iter_value_latestValue_subjects_3.GetValue();
                        jobject newElement_3;
                        std::string newElement_3ClassName     = "java/lang/Long";
                        std::string newElement_3CtorSignature = "(J)V";
                        chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(
                            newElement_3ClassName.c_str(), newElement_3CtorSignature.c_str(), entry_3, newElement_3);
                        chip::JniReferences::GetInstance().AddToList(value_latestValue_subjects, newElement_3);
                    }
                }
                jobject value_latestValue_targets;
                if (cppValue.latestValue.Value().targets.IsNull())
                {
                    value_latestValue_targets = nullptr;
                }
                else
                {
                    chip::JniReferences::GetInstance().CreateArrayList(value_latestValue_targets);

                    auto iter_value_latestValue_targets_3 = cppValue.latestValue.Value().targets.Value().begin();
                    while (iter_value_latestValue_targets_3.Next())
                    {
                        auto & entry_3 = iter_value_latestValue_targets_3.GetValue();
                        jobject newElement_3;
                        jobject newElement_3_cluster;
                        if (entry_3.cluster.IsNull())
                        {
                            newElement_3_cluster = nullptr;
                        }
                        else
                        {
                            std::string newElement_3_clusterClassName     = "java/lang/Long";
                            std::string newElement_3_clusterCtorSignature = "(J)V";
                            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                                newElement_3_clusterClassName.c_str(), newElement_3_clusterCtorSignature.c_str(),
                                entry_3.cluster.Value(), newElement_3_cluster);
                        }
                        jobject newElement_3_endpoint;
                        if (entry_3.endpoint.IsNull())
                        {
                            newElement_3_endpoint = nullptr;
                        }
                        else
                        {
                            std::string newElement_3_endpointClassName     = "java/lang/Integer";
                            std::string newElement_3_endpointCtorSignature = "(I)V";
                            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                                newElement_3_endpointClassName.c_str(), newElement_3_endpointCtorSignature.c_str(),
                                entry_3.endpoint.Value(), newElement_3_endpoint);
                        }
                        jobject newElement_3_deviceType;
                        if (entry_3.deviceType.IsNull())
                        {
                            newElement_3_deviceType = nullptr;
                        }
                        else
                        {
                            std::string newElement_3_deviceTypeClassName     = "java/lang/Long";
                            std::string newElement_3_deviceTypeCtorSignature = "(J)V";
                            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                                newElement_3_deviceTypeClassName.c_str(), newElement_3_deviceTypeCtorSignature.c_str(),
                                entry_3.deviceType.Value(), newElement_3_deviceType);
                        }

                        jclass targetStructClass_4;
                        err = chip::JniReferences::GetInstance().GetClassRef(
                            env, "chip/devicecontroller/ChipStructs$AccessControlClusterTarget", targetStructClass_4);
                        if (err != CHIP_NO_ERROR)
                        {
                            ChipLogError(Zcl, "Could not find class ChipStructs$AccessControlClusterTarget");
                            return nullptr;
                        }
                        jmethodID targetStructCtor_4 = env->GetMethodID(targetStructClass_4, "<init>",
                                                                        "(Ljava/lang/Long;Ljava/lang/Integer;Ljava/lang/Long;)V");
                        if (targetStructCtor_4 == nullptr)
                        {
                            ChipLogError(Zcl, "Could not find ChipStructs$AccessControlClusterTarget constructor");
                            return nullptr;
                        }

                        newElement_3 = env->NewObject(targetStructClass_4, targetStructCtor_4, newElement_3_cluster,
                                                      newElement_3_endpoint, newElement_3_deviceType);
                        chip::JniReferences::GetInstance().AddToList(value_latestValue_targets, newElement_3);
                    }
                }
                jobject value_latestValue_fabricIndex;
                std::string value_latestValue_fabricIndexClassName     = "java/lang/Integer";
                std::string value_latestValue_fabricIndexCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                    value_latestValue_fabricIndexClassName.c_str(), value_latestValue_fabricIndexCtorSignature.c_str(),
                    cppValue.latestValue.Value().fabricIndex, value_latestValue_fabricIndex);

                jclass accessControlEntryStructStructClass_1;
                err = chip::JniReferences::GetInstance().GetClassRef(
                    env, "chip/devicecontroller/ChipStructs$AccessControlClusterAccessControlEntryStruct",
                    accessControlEntryStructStructClass_1);
                if (err != CHIP_NO_ERROR)
                {
                    ChipLogError(Zcl, "Could not find class ChipStructs$AccessControlClusterAccessControlEntryStruct");
                    return nullptr;
                }
                jmethodID accessControlEntryStructStructCtor_1 = env->GetMethodID(
                    accessControlEntryStructStructClass_1, "<init>",
                    "(Ljava/lang/Integer;Ljava/lang/Integer;Ljava/util/ArrayList;Ljava/util/ArrayList;Ljava/lang/Integer;)V");
                if (accessControlEntryStructStructCtor_1 == nullptr)
                {
                    ChipLogError(Zcl, "Could not find ChipStructs$AccessControlClusterAccessControlEntryStruct constructor");
                    return nullptr;
                }

                value_latestValue =
                    env->NewObject(accessControlEntryStructStructClass_1, accessControlEntryStructStructCtor_1,
                                   value_latestValue_privilege, value_latestValue_authMode, value_latestValue_subjects,
                                   value_latestValue_targets, value_latestValue_fabricIndex);
            }

            jobject value_fabricIndex;
            std::string value_fabricIndexClassName     = "java/lang/Integer";
            std::string value_fabricIndexCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(value_fabricIndexClassName.c_str(),
                                                                          value_fabricIndexCtorSignature.c_str(),
                                                                          cppValue.fabricIndex, value_fabricIndex);

            jclass accessControlEntryChangedStructClass;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipEventStructs$AccessControlClusterAccessControlEntryChangedEvent",
                accessControlEntryChangedStructClass);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipEventStructs$AccessControlClusterAccessControlEntryChangedEvent");
                return nullptr;
            }
            jmethodID accessControlEntryChangedStructCtor =
                env->GetMethodID(accessControlEntryChangedStructClass, "<init>",
                                 "(Ljava/lang/Long;Ljava/lang/Integer;Ljava/lang/Integer;Lchip/devicecontroller/"
                                 "ChipStructs$AccessControlClusterAccessControlEntryStruct;Ljava/lang/Integer;)V");
            if (accessControlEntryChangedStructCtor == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipEventStructs$AccessControlClusterAccessControlEntryChangedEvent constructor");
                return nullptr;
            }

            jobject value =
                env->NewObject(accessControlEntryChangedStructClass, accessControlEntryChangedStructCtor, value_adminNodeID,
                               value_adminPasscodeID, value_changeType, value_latestValue, value_fabricIndex);

            return value;
        }
        case Events::AccessControlExtensionChanged::Id: {
            Events::AccessControlExtensionChanged::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value_adminNodeID;
            if (cppValue.adminNodeID.IsNull())
            {
                value_adminNodeID = nullptr;
            }
            else
            {
                std::string value_adminNodeIDClassName     = "java/lang/Long";
                std::string value_adminNodeIDCtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(value_adminNodeIDClassName.c_str(),
                                                                               value_adminNodeIDCtorSignature.c_str(),
                                                                               cppValue.adminNodeID.Value(), value_adminNodeID);
            }

            jobject value_adminPasscodeID;
            if (cppValue.adminPasscodeID.IsNull())
            {
                value_adminPasscodeID = nullptr;
            }
            else
            {
                std::string value_adminPasscodeIDClassName     = "java/lang/Integer";
                std::string value_adminPasscodeIDCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                    value_adminPasscodeIDClassName.c_str(), value_adminPasscodeIDCtorSignature.c_str(),
                    cppValue.adminPasscodeID.Value(), value_adminPasscodeID);
            }

            jobject value_changeType;
            std::string value_changeTypeClassName     = "java/lang/Integer";
            std::string value_changeTypeCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                value_changeTypeClassName.c_str(), value_changeTypeCtorSignature.c_str(), static_cast<uint8_t>(cppValue.changeType),
                value_changeType);

            jobject value_latestValue;
            if (cppValue.latestValue.IsNull())
            {
                value_latestValue = nullptr;
            }
            else
            {
                jobject value_latestValue_data;
                jbyteArray value_latestValue_dataByteArray =
                    env->NewByteArray(static_cast<jsize>(cppValue.latestValue.Value().data.size()));
                env->SetByteArrayRegion(value_latestValue_dataByteArray, 0,
                                        static_cast<jsize>(cppValue.latestValue.Value().data.size()),
                                        reinterpret_cast<const jbyte *>(cppValue.latestValue.Value().data.data()));
                value_latestValue_data = value_latestValue_dataByteArray;
                jobject value_latestValue_fabricIndex;
                std::string value_latestValue_fabricIndexClassName     = "java/lang/Integer";
                std::string value_latestValue_fabricIndexCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                    value_latestValue_fabricIndexClassName.c_str(), value_latestValue_fabricIndexCtorSignature.c_str(),
                    cppValue.latestValue.Value().fabricIndex, value_latestValue_fabricIndex);

                jclass accessControlExtensionStructStructClass_1;
                err = chip::JniReferences::GetInstance().GetClassRef(
                    env, "chip/devicecontroller/ChipStructs$AccessControlClusterAccessControlExtensionStruct",
                    accessControlExtensionStructStructClass_1);
                if (err != CHIP_NO_ERROR)
                {
                    ChipLogError(Zcl, "Could not find class ChipStructs$AccessControlClusterAccessControlExtensionStruct");
                    return nullptr;
                }
                jmethodID accessControlExtensionStructStructCtor_1 =
                    env->GetMethodID(accessControlExtensionStructStructClass_1, "<init>", "([BLjava/lang/Integer;)V");
                if (accessControlExtensionStructStructCtor_1 == nullptr)
                {
                    ChipLogError(Zcl, "Could not find ChipStructs$AccessControlClusterAccessControlExtensionStruct constructor");
                    return nullptr;
                }

                value_latestValue =
                    env->NewObject(accessControlExtensionStructStructClass_1, accessControlExtensionStructStructCtor_1,
                                   value_latestValue_data, value_latestValue_fabricIndex);
            }

            jobject value_fabricIndex;
            std::string value_fabricIndexClassName     = "java/lang/Integer";
            std::string value_fabricIndexCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(value_fabricIndexClassName.c_str(),
                                                                          value_fabricIndexCtorSignature.c_str(),
                                                                          cppValue.fabricIndex, value_fabricIndex);

            jclass accessControlExtensionChangedStructClass;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipEventStructs$AccessControlClusterAccessControlExtensionChangedEvent",
                accessControlExtensionChangedStructClass);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipEventStructs$AccessControlClusterAccessControlExtensionChangedEvent");
                return nullptr;
            }
            jmethodID accessControlExtensionChangedStructCtor =
                env->GetMethodID(accessControlExtensionChangedStructClass, "<init>",
                                 "(Ljava/lang/Long;Ljava/lang/Integer;Ljava/lang/Integer;Lchip/devicecontroller/"
                                 "ChipStructs$AccessControlClusterAccessControlExtensionStruct;Ljava/lang/Integer;)V");
            if (accessControlExtensionChangedStructCtor == nullptr)
            {
                ChipLogError(Zcl,
                             "Could not find ChipEventStructs$AccessControlClusterAccessControlExtensionChangedEvent constructor");
                return nullptr;
            }

            jobject value =
                env->NewObject(accessControlExtensionChangedStructClass, accessControlExtensionChangedStructCtor, value_adminNodeID,
                               value_adminPasscodeID, value_changeType, value_latestValue, value_fabricIndex);

            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::BasicInformation::Id: {
        using namespace app::Clusters::BasicInformation;
        switch (aPath.mEventId)
        {
        case Events::StartUp::Id: {
            Events::StartUp::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value_softwareVersion;
            std::string value_softwareVersionClassName     = "java/lang/Long";
            std::string value_softwareVersionCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(value_softwareVersionClassName.c_str(),
                                                                           value_softwareVersionCtorSignature.c_str(),
                                                                           cppValue.softwareVersion, value_softwareVersion);

            jclass startUpStructClass;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipEventStructs$BasicInformationClusterStartUpEvent", startUpStructClass);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipEventStructs$BasicInformationClusterStartUpEvent");
                return nullptr;
            }
            jmethodID startUpStructCtor = env->GetMethodID(startUpStructClass, "<init>", "(Ljava/lang/Long;)V");
            if (startUpStructCtor == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipEventStructs$BasicInformationClusterStartUpEvent constructor");
                return nullptr;
            }

            jobject value = env->NewObject(startUpStructClass, startUpStructCtor, value_softwareVersion);

            return value;
        }
        case Events::ShutDown::Id: {
            Events::ShutDown::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jclass shutDownStructClass;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipEventStructs$BasicInformationClusterShutDownEvent", shutDownStructClass);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipEventStructs$BasicInformationClusterShutDownEvent");
                return nullptr;
            }
            jmethodID shutDownStructCtor = env->GetMethodID(shutDownStructClass, "<init>", "()V");
            if (shutDownStructCtor == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipEventStructs$BasicInformationClusterShutDownEvent constructor");
                return nullptr;
            }

            jobject value = env->NewObject(shutDownStructClass, shutDownStructCtor);

            return value;
        }
        case Events::Leave::Id: {
            Events::Leave::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value_fabricIndex;
            std::string value_fabricIndexClassName     = "java/lang/Integer";
            std::string value_fabricIndexCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(value_fabricIndexClassName.c_str(),
                                                                          value_fabricIndexCtorSignature.c_str(),
                                                                          cppValue.fabricIndex, value_fabricIndex);

            jclass leaveStructClass;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipEventStructs$BasicInformationClusterLeaveEvent", leaveStructClass);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipEventStructs$BasicInformationClusterLeaveEvent");
                return nullptr;
            }
            jmethodID leaveStructCtor = env->GetMethodID(leaveStructClass, "<init>", "(Ljava/lang/Integer;)V");
            if (leaveStructCtor == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipEventStructs$BasicInformationClusterLeaveEvent constructor");
                return nullptr;
            }

            jobject value = env->NewObject(leaveStructClass, leaveStructCtor, value_fabricIndex);

            return value;
        }
        case Events::ReachableChanged::Id: {
            Events::ReachableChanged::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value_reachableNewValue;
            std::string value_reachableNewValueClassName     = "java/lang/Boolean";
            std::string value_reachableNewValueCtorSignature = "(Z)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<bool>(value_reachableNewValueClassName.c_str(),
                                                                       value_reachableNewValueCtorSignature.c_str(),
                                                                       cppValue.reachableNewValue, value_reachableNewValue);

            jclass reachableChangedStructClass;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipEventStructs$BasicInformationClusterReachableChangedEvent",
                reachableChangedStructClass);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipEventStructs$BasicInformationClusterReachableChangedEvent");
                return nullptr;
            }
            jmethodID reachableChangedStructCtor =
                env->GetMethodID(reachableChangedStructClass, "<init>", "(Ljava/lang/Boolean;)V");
            if (reachableChangedStructCtor == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipEventStructs$BasicInformationClusterReachableChangedEvent constructor");
                return nullptr;
            }

            jobject value = env->NewObject(reachableChangedStructClass, reachableChangedStructCtor, value_reachableNewValue);

            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::LocalizationConfiguration::Id: {
        using namespace app::Clusters::LocalizationConfiguration;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::GeneralCommissioning::Id: {
        using namespace app::Clusters::GeneralCommissioning;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::NetworkCommissioning::Id: {
        using namespace app::Clusters::NetworkCommissioning;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::AdministratorCommissioning::Id: {
        using namespace app::Clusters::AdministratorCommissioning;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::OperationalCredentials::Id: {
        using namespace app::Clusters::OperationalCredentials;
        switch (aPath.mEventId)
        {
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
            break;
        }
        break;
    }
    default:
        *aError = CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB;
        break;
    }
    return nullptr;
}

} // namespace chip
