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
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/data-model/DecodableList.h>
#include <app/data-model/Decode.h>
#include <jni.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>
#include <lib/support/TypeTraits.h>

namespace chip {

jobject DecodeAttributeValue(const app::ConcreteAttributePath & aPath, TLV::TLVReader & aReader, CHIP_ERROR * aError)
{
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();
    CHIP_ERROR err = CHIP_NO_ERROR;

    switch (aPath.mClusterId)
    {
    case app::Clusters::Identify::Id: {
        using namespace app::Clusters::Identify;
        switch (aPath.mAttributeId)
        {
        case Attributes::IdentifyTime::Id: {
            using TypeInfo = Attributes::IdentifyTime::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::IdentifyType::Id: {
            using TypeInfo = Attributes::IdentifyType::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::Descriptor::Id: {
        using namespace app::Clusters::Descriptor;
        switch (aPath.mAttributeId)
        {
        case Attributes::DeviceTypeList::Id: {
            using TypeInfo = Attributes::DeviceTypeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jobject newElement_0_deviceType;
                std::string newElement_0_deviceTypeClassName     = "java/lang/Long";
                std::string newElement_0_deviceTypeCtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(newElement_0_deviceTypeClassName.c_str(),
                                                                               newElement_0_deviceTypeCtorSignature.c_str(),
                                                                               entry_0.deviceType, newElement_0_deviceType);
                jobject newElement_0_revision;
                std::string newElement_0_revisionClassName     = "java/lang/Integer";
                std::string newElement_0_revisionCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(newElement_0_revisionClassName.c_str(),
                                                                               newElement_0_revisionCtorSignature.c_str(),
                                                                               entry_0.revision, newElement_0_revision);

                jclass deviceTypeStructStructClass_1;
                err = chip::JniReferences::GetInstance().GetClassRef(
                    env, "chip/devicecontroller/ChipStructs$DescriptorClusterDeviceTypeStruct", deviceTypeStructStructClass_1);
                if (err != CHIP_NO_ERROR)
                {
                    ChipLogError(Zcl, "Could not find class ChipStructs$DescriptorClusterDeviceTypeStruct");
                    return nullptr;
                }
                jmethodID deviceTypeStructStructCtor_1 =
                    env->GetMethodID(deviceTypeStructStructClass_1, "<init>", "(Ljava/lang/Long;Ljava/lang/Integer;)V");
                if (deviceTypeStructStructCtor_1 == nullptr)
                {
                    ChipLogError(Zcl, "Could not find ChipStructs$DescriptorClusterDeviceTypeStruct constructor");
                    return nullptr;
                }

                newElement_0 = env->NewObject(deviceTypeStructStructClass_1, deviceTypeStructStructCtor_1, newElement_0_deviceType,
                                              newElement_0_revision);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::ServerList::Id: {
            using TypeInfo = Attributes::ServerList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::ClientList::Id: {
            using TypeInfo = Attributes::ClientList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::PartsList::Id: {
            using TypeInfo = Attributes::PartsList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Integer";
                std::string newElement_0CtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::AccessControl::Id: {
        using namespace app::Clusters::AccessControl;
        switch (aPath.mAttributeId)
        {
        case Attributes::Acl::Id: {
            using TypeInfo = Attributes::Acl::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jobject newElement_0_privilege;
                std::string newElement_0_privilegeClassName     = "java/lang/Integer";
                std::string newElement_0_privilegeCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                    newElement_0_privilegeClassName.c_str(), newElement_0_privilegeCtorSignature.c_str(),
                    static_cast<uint8_t>(entry_0.privilege), newElement_0_privilege);
                jobject newElement_0_authMode;
                std::string newElement_0_authModeClassName     = "java/lang/Integer";
                std::string newElement_0_authModeCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(
                    newElement_0_authModeClassName.c_str(), newElement_0_authModeCtorSignature.c_str(),
                    static_cast<uint8_t>(entry_0.authMode), newElement_0_authMode);
                jobject newElement_0_subjects;
                if (entry_0.subjects.IsNull())
                {
                    newElement_0_subjects = nullptr;
                }
                else
                {
                    chip::JniReferences::GetInstance().CreateArrayList(newElement_0_subjects);

                    auto iter_newElement_0_subjects_3 = entry_0.subjects.Value().begin();
                    while (iter_newElement_0_subjects_3.Next())
                    {
                        auto & entry_3 = iter_newElement_0_subjects_3.GetValue();
                        jobject newElement_3;
                        std::string newElement_3ClassName     = "java/lang/Long";
                        std::string newElement_3CtorSignature = "(J)V";
                        chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(
                            newElement_3ClassName.c_str(), newElement_3CtorSignature.c_str(), entry_3, newElement_3);
                        chip::JniReferences::GetInstance().AddToList(newElement_0_subjects, newElement_3);
                    }
                }
                jobject newElement_0_targets;
                if (entry_0.targets.IsNull())
                {
                    newElement_0_targets = nullptr;
                }
                else
                {
                    chip::JniReferences::GetInstance().CreateArrayList(newElement_0_targets);

                    auto iter_newElement_0_targets_3 = entry_0.targets.Value().begin();
                    while (iter_newElement_0_targets_3.Next())
                    {
                        auto & entry_3 = iter_newElement_0_targets_3.GetValue();
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
                        chip::JniReferences::GetInstance().AddToList(newElement_0_targets, newElement_3);
                    }
                }
                jobject newElement_0_fabricIndex;
                std::string newElement_0_fabricIndexClassName     = "java/lang/Integer";
                std::string newElement_0_fabricIndexCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(newElement_0_fabricIndexClassName.c_str(),
                                                                              newElement_0_fabricIndexCtorSignature.c_str(),
                                                                              entry_0.fabricIndex, newElement_0_fabricIndex);

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

                newElement_0 = env->NewObject(accessControlEntryStructStructClass_1, accessControlEntryStructStructCtor_1,
                                              newElement_0_privilege, newElement_0_authMode, newElement_0_subjects,
                                              newElement_0_targets, newElement_0_fabricIndex);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::Extension::Id: {
            using TypeInfo = Attributes::Extension::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jobject newElement_0_data;
                jbyteArray newElement_0_dataByteArray = env->NewByteArray(static_cast<jsize>(entry_0.data.size()));
                env->SetByteArrayRegion(newElement_0_dataByteArray, 0, static_cast<jsize>(entry_0.data.size()),
                                        reinterpret_cast<const jbyte *>(entry_0.data.data()));
                newElement_0_data = newElement_0_dataByteArray;
                jobject newElement_0_fabricIndex;
                std::string newElement_0_fabricIndexClassName     = "java/lang/Integer";
                std::string newElement_0_fabricIndexCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(newElement_0_fabricIndexClassName.c_str(),
                                                                              newElement_0_fabricIndexCtorSignature.c_str(),
                                                                              entry_0.fabricIndex, newElement_0_fabricIndex);

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

                newElement_0 = env->NewObject(accessControlExtensionStructStructClass_1, accessControlExtensionStructStructCtor_1,
                                              newElement_0_data, newElement_0_fabricIndex);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::SubjectsPerAccessControlEntry::Id: {
            using TypeInfo = Attributes::SubjectsPerAccessControlEntry::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::TargetsPerAccessControlEntry::Id: {
            using TypeInfo = Attributes::TargetsPerAccessControlEntry::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::AccessControlEntriesPerFabric::Id: {
            using TypeInfo = Attributes::AccessControlEntriesPerFabric::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::BasicInformation::Id: {
        using namespace app::Clusters::BasicInformation;
        switch (aPath.mAttributeId)
        {
        case Attributes::DataModelRevision::Id: {
            using TypeInfo = Attributes::DataModelRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::VendorName::Id: {
            using TypeInfo = Attributes::VendorName::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::VendorID::Id: {
            using TypeInfo = Attributes::VendorID::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           static_cast<uint16_t>(cppValue), value);
            return value;
        }
        case Attributes::ProductName::Id: {
            using TypeInfo = Attributes::ProductName::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::ProductID::Id: {
            using TypeInfo = Attributes::ProductID::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::NodeLabel::Id: {
            using TypeInfo = Attributes::NodeLabel::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::Location::Id: {
            using TypeInfo = Attributes::Location::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::HardwareVersion::Id: {
            using TypeInfo = Attributes::HardwareVersion::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::HardwareVersionString::Id: {
            using TypeInfo = Attributes::HardwareVersionString::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::SoftwareVersion::Id: {
            using TypeInfo = Attributes::SoftwareVersion::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::SoftwareVersionString::Id: {
            using TypeInfo = Attributes::SoftwareVersionString::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::ManufacturingDate::Id: {
            using TypeInfo = Attributes::ManufacturingDate::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::PartNumber::Id: {
            using TypeInfo = Attributes::PartNumber::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::ProductURL::Id: {
            using TypeInfo = Attributes::ProductURL::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::ProductLabel::Id: {
            using TypeInfo = Attributes::ProductLabel::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::SerialNumber::Id: {
            using TypeInfo = Attributes::SerialNumber::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::LocalConfigDisabled::Id: {
            using TypeInfo = Attributes::LocalConfigDisabled::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Boolean";
            std::string valueCtorSignature = "(Z)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<bool>(valueClassName.c_str(), valueCtorSignature.c_str(), cppValue,
                                                                       value);
            return value;
        }
        case Attributes::Reachable::Id: {
            using TypeInfo = Attributes::Reachable::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Boolean";
            std::string valueCtorSignature = "(Z)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<bool>(valueClassName.c_str(), valueCtorSignature.c_str(), cppValue,
                                                                       value);
            return value;
        }
        case Attributes::UniqueID::Id: {
            using TypeInfo = Attributes::UniqueID::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::CapabilityMinima::Id: {
            using TypeInfo = Attributes::CapabilityMinima::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            jobject value_caseSessionsPerFabric;
            std::string value_caseSessionsPerFabricClassName     = "java/lang/Integer";
            std::string value_caseSessionsPerFabricCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                value_caseSessionsPerFabricClassName.c_str(), value_caseSessionsPerFabricCtorSignature.c_str(),
                cppValue.caseSessionsPerFabric, value_caseSessionsPerFabric);
            jobject value_subscriptionsPerFabric;
            std::string value_subscriptionsPerFabricClassName     = "java/lang/Integer";
            std::string value_subscriptionsPerFabricCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                value_subscriptionsPerFabricClassName.c_str(), value_subscriptionsPerFabricCtorSignature.c_str(),
                cppValue.subscriptionsPerFabric, value_subscriptionsPerFabric);

            jclass capabilityMinimaStructStructClass_0;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipStructs$BasicInformationClusterCapabilityMinimaStruct",
                capabilityMinimaStructStructClass_0);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipStructs$BasicInformationClusterCapabilityMinimaStruct");
                return nullptr;
            }
            jmethodID capabilityMinimaStructStructCtor_0 =
                env->GetMethodID(capabilityMinimaStructStructClass_0, "<init>", "(Ljava/lang/Integer;Ljava/lang/Integer;)V");
            if (capabilityMinimaStructStructCtor_0 == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipStructs$BasicInformationClusterCapabilityMinimaStruct constructor");
                return nullptr;
            }

            value = env->NewObject(capabilityMinimaStructStructClass_0, capabilityMinimaStructStructCtor_0,
                                   value_caseSessionsPerFabric, value_subscriptionsPerFabric);
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::LocalizationConfiguration::Id: {
        using namespace app::Clusters::LocalizationConfiguration;
        switch (aPath.mAttributeId)
        {
        case Attributes::ActiveLocale::Id: {
            using TypeInfo = Attributes::ActiveLocale::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            value = env->NewStringUTF(std::string(cppValue.data(), cppValue.size()).c_str());
            return value;
        }
        case Attributes::SupportedLocales::Id: {
            using TypeInfo = Attributes::SupportedLocales::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                newElement_0 = env->NewStringUTF(std::string(entry_0.data(), entry_0.size()).c_str());
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::GeneralCommissioning::Id: {
        using namespace app::Clusters::GeneralCommissioning;
        switch (aPath.mAttributeId)
        {
        case Attributes::Breadcrumb::Id: {
            using TypeInfo = Attributes::Breadcrumb::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::BasicCommissioningInfo::Id: {
            using TypeInfo = Attributes::BasicCommissioningInfo::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            jobject value_failSafeExpiryLengthSeconds;
            std::string value_failSafeExpiryLengthSecondsClassName     = "java/lang/Integer";
            std::string value_failSafeExpiryLengthSecondsCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                value_failSafeExpiryLengthSecondsClassName.c_str(), value_failSafeExpiryLengthSecondsCtorSignature.c_str(),
                cppValue.failSafeExpiryLengthSeconds, value_failSafeExpiryLengthSeconds);
            jobject value_maxCumulativeFailsafeSeconds;
            std::string value_maxCumulativeFailsafeSecondsClassName     = "java/lang/Integer";
            std::string value_maxCumulativeFailsafeSecondsCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                value_maxCumulativeFailsafeSecondsClassName.c_str(), value_maxCumulativeFailsafeSecondsCtorSignature.c_str(),
                cppValue.maxCumulativeFailsafeSeconds, value_maxCumulativeFailsafeSeconds);

            jclass basicCommissioningInfoStructClass_0;
            err = chip::JniReferences::GetInstance().GetClassRef(
                env, "chip/devicecontroller/ChipStructs$GeneralCommissioningClusterBasicCommissioningInfo",
                basicCommissioningInfoStructClass_0);
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(Zcl, "Could not find class ChipStructs$GeneralCommissioningClusterBasicCommissioningInfo");
                return nullptr;
            }
            jmethodID basicCommissioningInfoStructCtor_0 =
                env->GetMethodID(basicCommissioningInfoStructClass_0, "<init>", "(Ljava/lang/Integer;Ljava/lang/Integer;)V");
            if (basicCommissioningInfoStructCtor_0 == nullptr)
            {
                ChipLogError(Zcl, "Could not find ChipStructs$GeneralCommissioningClusterBasicCommissioningInfo constructor");
                return nullptr;
            }

            value = env->NewObject(basicCommissioningInfoStructClass_0, basicCommissioningInfoStructCtor_0,
                                   value_failSafeExpiryLengthSeconds, value_maxCumulativeFailsafeSeconds);
            return value;
        }
        case Attributes::RegulatoryConfig::Id: {
            using TypeInfo = Attributes::RegulatoryConfig::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          static_cast<uint8_t>(cppValue), value);
            return value;
        }
        case Attributes::LocationCapability::Id: {
            using TypeInfo = Attributes::LocationCapability::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          static_cast<uint8_t>(cppValue), value);
            return value;
        }
        case Attributes::SupportsConcurrentConnection::Id: {
            using TypeInfo = Attributes::SupportsConcurrentConnection::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Boolean";
            std::string valueCtorSignature = "(Z)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<bool>(valueClassName.c_str(), valueCtorSignature.c_str(), cppValue,
                                                                       value);
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::NetworkCommissioning::Id: {
        using namespace app::Clusters::NetworkCommissioning;
        switch (aPath.mAttributeId)
        {
        case Attributes::MaxNetworks::Id: {
            using TypeInfo = Attributes::MaxNetworks::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::Networks::Id: {
            using TypeInfo = Attributes::Networks::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jobject newElement_0_networkID;
                jbyteArray newElement_0_networkIDByteArray = env->NewByteArray(static_cast<jsize>(entry_0.networkID.size()));
                env->SetByteArrayRegion(newElement_0_networkIDByteArray, 0, static_cast<jsize>(entry_0.networkID.size()),
                                        reinterpret_cast<const jbyte *>(entry_0.networkID.data()));
                newElement_0_networkID = newElement_0_networkIDByteArray;
                jobject newElement_0_connected;
                std::string newElement_0_connectedClassName     = "java/lang/Boolean";
                std::string newElement_0_connectedCtorSignature = "(Z)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<bool>(newElement_0_connectedClassName.c_str(),
                                                                           newElement_0_connectedCtorSignature.c_str(),
                                                                           entry_0.connected, newElement_0_connected);

                jclass networkInfoStructClass_1;
                err = chip::JniReferences::GetInstance().GetClassRef(
                    env, "chip/devicecontroller/ChipStructs$NetworkCommissioningClusterNetworkInfo", networkInfoStructClass_1);
                if (err != CHIP_NO_ERROR)
                {
                    ChipLogError(Zcl, "Could not find class ChipStructs$NetworkCommissioningClusterNetworkInfo");
                    return nullptr;
                }
                jmethodID networkInfoStructCtor_1 =
                    env->GetMethodID(networkInfoStructClass_1, "<init>", "([BLjava/lang/Boolean;)V");
                if (networkInfoStructCtor_1 == nullptr)
                {
                    ChipLogError(Zcl, "Could not find ChipStructs$NetworkCommissioningClusterNetworkInfo constructor");
                    return nullptr;
                }

                newElement_0 = env->NewObject(networkInfoStructClass_1, networkInfoStructCtor_1, newElement_0_networkID,
                                              newElement_0_connected);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::ScanMaxTimeSeconds::Id: {
            using TypeInfo = Attributes::ScanMaxTimeSeconds::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::ConnectMaxTimeSeconds::Id: {
            using TypeInfo = Attributes::ConnectMaxTimeSeconds::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::InterfaceEnabled::Id: {
            using TypeInfo = Attributes::InterfaceEnabled::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Boolean";
            std::string valueCtorSignature = "(Z)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<bool>(valueClassName.c_str(), valueCtorSignature.c_str(), cppValue,
                                                                       value);
            return value;
        }
        case Attributes::LastNetworkingStatus::Id: {
            using TypeInfo = Attributes::LastNetworkingStatus::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            if (cppValue.IsNull())
            {
                value = nullptr;
            }
            else
            {
                std::string valueClassName     = "java/lang/Integer";
                std::string valueCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                              static_cast<uint8_t>(cppValue.Value()), value);
            }
            return value;
        }
        case Attributes::LastNetworkID::Id: {
            using TypeInfo = Attributes::LastNetworkID::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            if (cppValue.IsNull())
            {
                value = nullptr;
            }
            else
            {
                jbyteArray valueByteArray = env->NewByteArray(static_cast<jsize>(cppValue.Value().size()));
                env->SetByteArrayRegion(valueByteArray, 0, static_cast<jsize>(cppValue.Value().size()),
                                        reinterpret_cast<const jbyte *>(cppValue.Value().data()));
                value = valueByteArray;
            }
            return value;
        }
        case Attributes::LastConnectErrorValue::Id: {
            using TypeInfo = Attributes::LastConnectErrorValue::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            if (cppValue.IsNull())
            {
                value = nullptr;
            }
            else
            {
                std::string valueClassName     = "java/lang/Long";
                std::string valueCtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<int32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                              cppValue.Value(), value);
            }
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::AdministratorCommissioning::Id: {
        using namespace app::Clusters::AdministratorCommissioning;
        switch (aPath.mAttributeId)
        {
        case Attributes::WindowStatus::Id: {
            using TypeInfo = Attributes::WindowStatus::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          static_cast<uint8_t>(cppValue), value);
            return value;
        }
        case Attributes::AdminFabricIndex::Id: {
            using TypeInfo = Attributes::AdminFabricIndex::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            if (cppValue.IsNull())
            {
                value = nullptr;
            }
            else
            {
                std::string valueClassName     = "java/lang/Integer";
                std::string valueCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                              cppValue.Value(), value);
            }
            return value;
        }
        case Attributes::AdminVendorId::Id: {
            using TypeInfo = Attributes::AdminVendorId::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            if (cppValue.IsNull())
            {
                value = nullptr;
            }
            else
            {
                std::string valueClassName     = "java/lang/Integer";
                std::string valueCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                               cppValue.Value(), value);
            }
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    case app::Clusters::OperationalCredentials::Id: {
        using namespace app::Clusters::OperationalCredentials;
        switch (aPath.mAttributeId)
        {
        case Attributes::NOCs::Id: {
            using TypeInfo = Attributes::NOCs::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jobject newElement_0_noc;
                jbyteArray newElement_0_nocByteArray = env->NewByteArray(static_cast<jsize>(entry_0.noc.size()));
                env->SetByteArrayRegion(newElement_0_nocByteArray, 0, static_cast<jsize>(entry_0.noc.size()),
                                        reinterpret_cast<const jbyte *>(entry_0.noc.data()));
                newElement_0_noc = newElement_0_nocByteArray;
                jobject newElement_0_icac;
                if (entry_0.icac.IsNull())
                {
                    newElement_0_icac = nullptr;
                }
                else
                {
                    jbyteArray newElement_0_icacByteArray = env->NewByteArray(static_cast<jsize>(entry_0.icac.Value().size()));
                    env->SetByteArrayRegion(newElement_0_icacByteArray, 0, static_cast<jsize>(entry_0.icac.Value().size()),
                                            reinterpret_cast<const jbyte *>(entry_0.icac.Value().data()));
                    newElement_0_icac = newElement_0_icacByteArray;
                }
                jobject newElement_0_fabricIndex;
                std::string newElement_0_fabricIndexClassName     = "java/lang/Integer";
                std::string newElement_0_fabricIndexCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(newElement_0_fabricIndexClassName.c_str(),
                                                                              newElement_0_fabricIndexCtorSignature.c_str(),
                                                                              entry_0.fabricIndex, newElement_0_fabricIndex);

                jclass NOCStructStructClass_1;
                err = chip::JniReferences::GetInstance().GetClassRef(
                    env, "chip/devicecontroller/ChipStructs$OperationalCredentialsClusterNOCStruct", NOCStructStructClass_1);
                if (err != CHIP_NO_ERROR)
                {
                    ChipLogError(Zcl, "Could not find class ChipStructs$OperationalCredentialsClusterNOCStruct");
                    return nullptr;
                }
                jmethodID NOCStructStructCtor_1 = env->GetMethodID(NOCStructStructClass_1, "<init>", "([B[BLjava/lang/Integer;)V");
                if (NOCStructStructCtor_1 == nullptr)
                {
                    ChipLogError(Zcl, "Could not find ChipStructs$OperationalCredentialsClusterNOCStruct constructor");
                    return nullptr;
                }

                newElement_0 = env->NewObject(NOCStructStructClass_1, NOCStructStructCtor_1, newElement_0_noc, newElement_0_icac,
                                              newElement_0_fabricIndex);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::Fabrics::Id: {
            using TypeInfo = Attributes::Fabrics::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jobject newElement_0_rootPublicKey;
                jbyteArray newElement_0_rootPublicKeyByteArray =
                    env->NewByteArray(static_cast<jsize>(entry_0.rootPublicKey.size()));
                env->SetByteArrayRegion(newElement_0_rootPublicKeyByteArray, 0, static_cast<jsize>(entry_0.rootPublicKey.size()),
                                        reinterpret_cast<const jbyte *>(entry_0.rootPublicKey.data()));
                newElement_0_rootPublicKey = newElement_0_rootPublicKeyByteArray;
                jobject newElement_0_vendorID;
                std::string newElement_0_vendorIDClassName     = "java/lang/Integer";
                std::string newElement_0_vendorIDCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(
                    newElement_0_vendorIDClassName.c_str(), newElement_0_vendorIDCtorSignature.c_str(),
                    static_cast<uint16_t>(entry_0.vendorID), newElement_0_vendorID);
                jobject newElement_0_fabricID;
                std::string newElement_0_fabricIDClassName     = "java/lang/Long";
                std::string newElement_0_fabricIDCtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(newElement_0_fabricIDClassName.c_str(),
                                                                               newElement_0_fabricIDCtorSignature.c_str(),
                                                                               entry_0.fabricID, newElement_0_fabricID);
                jobject newElement_0_nodeID;
                std::string newElement_0_nodeIDClassName     = "java/lang/Long";
                std::string newElement_0_nodeIDCtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint64_t>(newElement_0_nodeIDClassName.c_str(),
                                                                               newElement_0_nodeIDCtorSignature.c_str(),
                                                                               entry_0.nodeID, newElement_0_nodeID);
                jobject newElement_0_label;
                newElement_0_label = env->NewStringUTF(std::string(entry_0.label.data(), entry_0.label.size()).c_str());
                jobject newElement_0_fabricIndex;
                std::string newElement_0_fabricIndexClassName     = "java/lang/Integer";
                std::string newElement_0_fabricIndexCtorSignature = "(I)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(newElement_0_fabricIndexClassName.c_str(),
                                                                              newElement_0_fabricIndexCtorSignature.c_str(),
                                                                              entry_0.fabricIndex, newElement_0_fabricIndex);

                jclass fabricDescriptorStructStructClass_1;
                err = chip::JniReferences::GetInstance().GetClassRef(
                    env, "chip/devicecontroller/ChipStructs$OperationalCredentialsClusterFabricDescriptorStruct",
                    fabricDescriptorStructStructClass_1);
                if (err != CHIP_NO_ERROR)
                {
                    ChipLogError(Zcl, "Could not find class ChipStructs$OperationalCredentialsClusterFabricDescriptorStruct");
                    return nullptr;
                }
                jmethodID fabricDescriptorStructStructCtor_1 = env->GetMethodID(
                    fabricDescriptorStructStructClass_1, "<init>",
                    "([BLjava/lang/Integer;Ljava/lang/Long;Ljava/lang/Long;Ljava/lang/String;Ljava/lang/Integer;)V");
                if (fabricDescriptorStructStructCtor_1 == nullptr)
                {
                    ChipLogError(Zcl, "Could not find ChipStructs$OperationalCredentialsClusterFabricDescriptorStruct constructor");
                    return nullptr;
                }

                newElement_0 = env->NewObject(fabricDescriptorStructStructClass_1, fabricDescriptorStructStructCtor_1,
                                              newElement_0_rootPublicKey, newElement_0_vendorID, newElement_0_fabricID,
                                              newElement_0_nodeID, newElement_0_label, newElement_0_fabricIndex);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::SupportedFabrics::Id: {
            using TypeInfo = Attributes::SupportedFabrics::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::CommissionedFabrics::Id: {
            using TypeInfo = Attributes::CommissionedFabrics::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::TrustedRootCertificates::Id: {
            using TypeInfo = Attributes::TrustedRootCertificates::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                jbyteArray newElement_0ByteArray = env->NewByteArray(static_cast<jsize>(entry_0.size()));
                env->SetByteArrayRegion(newElement_0ByteArray, 0, static_cast<jsize>(entry_0.size()),
                                        reinterpret_cast<const jbyte *>(entry_0.data()));
                newElement_0 = newElement_0ByteArray;
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::CurrentFabricIndex::Id: {
            using TypeInfo = Attributes::CurrentFabricIndex::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint8_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                          cppValue, value);
            return value;
        }
        case Attributes::GeneratedCommandList::Id: {
            using TypeInfo = Attributes::GeneratedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AcceptedCommandList::Id: {
            using TypeInfo = Attributes::AcceptedCommandList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::EventList::Id: {
            using TypeInfo = Attributes::EventList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::AttributeList::Id: {
            using TypeInfo = Attributes::AttributeList::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            chip::JniReferences::GetInstance().CreateArrayList(value);

            auto iter_value_0 = cppValue.begin();
            while (iter_value_0.Next())
            {
                auto & entry_0 = iter_value_0.GetValue();
                jobject newElement_0;
                std::string newElement_0ClassName     = "java/lang/Long";
                std::string newElement_0CtorSignature = "(J)V";
                chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(
                    newElement_0ClassName.c_str(), newElement_0CtorSignature.c_str(), entry_0, newElement_0);
                chip::JniReferences::GetInstance().AddToList(value, newElement_0);
            }
            return value;
        }
        case Attributes::FeatureMap::Id: {
            using TypeInfo = Attributes::FeatureMap::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Long";
            std::string valueCtorSignature = "(J)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint32_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        case Attributes::ClusterRevision::Id: {
            using TypeInfo = Attributes::ClusterRevision::TypeInfo;
            TypeInfo::DecodableType cppValue;
            *aError = app::DataModel::Decode(aReader, cppValue);
            if (*aError != CHIP_NO_ERROR)
            {
                return nullptr;
            }
            jobject value;
            std::string valueClassName     = "java/lang/Integer";
            std::string valueCtorSignature = "(I)V";
            chip::JniReferences::GetInstance().CreateBoxedObject<uint16_t>(valueClassName.c_str(), valueCtorSignature.c_str(),
                                                                           cppValue, value);
            return value;
        }
        default:
            *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
            break;
        }
        break;
    }
    default:
        *aError = CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB;
        break;
    }
    return nullptr;
}

} // namespace chip
