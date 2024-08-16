/**
 *
 *    Copyright (c) 2021-2024 Project CHIP Authors
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
/****************************************************************************
 * @file
 * @brief Routines for the Content Launch plugin, the
 *server implementation of the Content Launch cluster.
 *******************************************************************************
 ******************************************************************************/

#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/cluster-objects.h>
#include <app/AttributeAccessInterfaceRegistry.h>
#include <app/CommandHandler.h>
#include <app/ConcreteCommandPath.h>
#include <app/server/CommissioningWindowManager.h>
#if CHIP_CONFIG_TC_REQUIRED
#include <app/server/EnhancedSetupFlowProvider.h>
#endif
#include <app/server/Server.h>
#include <app/util/attribute-storage.h>
#include <lib/support/Span.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/CHIPDeviceConfig.h>
#include <platform/ConfigurationManager.h>
#include <platform/DeviceControlServer.h>
#include <tracing/macros.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::GeneralCommissioning;
using namespace chip::app::Clusters::GeneralCommissioning::Attributes;
using namespace chip::DeviceLayer;
using Transport::SecureSession;
using Transport::Session;

#define CheckSuccess(expr, code)                                                                                                   \
    do                                                                                                                             \
    {                                                                                                                              \
        if (!::chip::ChipError::IsSuccess(expr))                                                                                   \
        {                                                                                                                          \
            commandObj->AddStatus(commandPath, Protocols::InteractionModel::Status::code, #expr);                                  \
            return true;                                                                                                           \
        }                                                                                                                          \
    } while (false)

namespace {

class GeneralCommissioningAttrAccess : public AttributeAccessInterface
{
public:
    // Register for the GeneralCommissioning cluster on all endpoints.
    GeneralCommissioningAttrAccess() : AttributeAccessInterface(Optional<EndpointId>::Missing(), GeneralCommissioning::Id) {}

    CHIP_ERROR Read(const ConcreteReadAttributePath & aPath, AttributeValueEncoder & aEncoder) override;

private:
    CHIP_ERROR ReadIfSupported(CHIP_ERROR (ConfigurationManager::*getter)(uint8_t &), AttributeValueEncoder & aEncoder);
    CHIP_ERROR ReadBasicCommissioningInfo(AttributeValueEncoder & aEncoder);
    CHIP_ERROR ReadSupportsConcurrentConnection(AttributeValueEncoder & aEncoder);
    template <typename Provider, typename T>
    CHIP_ERROR ReadFromProvider(Provider * const aProvider, CHIP_ERROR (Provider::*const aConstGetter)(T &) const,
                                AttributeValueEncoder & aEncoder);
};

GeneralCommissioningAttrAccess gAttrAccess;

CHIP_ERROR GeneralCommissioningAttrAccess::Read(const ConcreteReadAttributePath & aPath, AttributeValueEncoder & aEncoder)
{
    if (aPath.mClusterId != GeneralCommissioning::Id)
    {
        // We shouldn't have been called at all.
        return CHIP_ERROR_INVALID_ARGUMENT;
    }

    switch (aPath.mAttributeId)
    {
    case RegulatoryConfig::Id: {
        return ReadIfSupported(&ConfigurationManager::GetRegulatoryLocation, aEncoder);
    }
    case LocationCapability::Id: {
        return ReadIfSupported(&ConfigurationManager::GetLocationCapability, aEncoder);
    }
    case BasicCommissioningInfo::Id: {
        return ReadBasicCommissioningInfo(aEncoder);
    }
    case SupportsConcurrentConnection::Id: {
        return ReadSupportsConcurrentConnection(aEncoder);
    }
#if CHIP_CONFIG_TC_REQUIRED
    case TCAcceptedVersion::Id: {
        auto provider = Server::GetInstance().GetEnhancedSetupFlowProvider();
        auto getter   = &EnhancedSetupFlowProvider::GetTermsAndConditionsAcceptedAcknowledgementsVersion;
        return ReadFromProvider(provider, getter, aEncoder);
    }
    case TCMinRequiredVersion::Id: {
        auto provider = Server::GetInstance().GetEnhancedSetupFlowProvider();
        auto getter   = &EnhancedSetupFlowProvider::GetTermsAndConditionsRequiredAcknowledgementsVersion;
        return ReadFromProvider(provider, getter, aEncoder);
    }
    case TCAcknowledgements::Id: {
        auto provider = Server::GetInstance().GetEnhancedSetupFlowProvider();
        auto getter   = &EnhancedSetupFlowProvider::GetTermsAndConditionsAcceptedAcknowledgements;
        return ReadFromProvider(provider, getter, aEncoder);
    }
    case TCAcknowledgementsRequired::Id: {
        auto provider = Server::GetInstance().GetEnhancedSetupFlowProvider();
        auto getter   = &EnhancedSetupFlowProvider::IsTermsAndConditionsAcceptanceRequired;
        return ReadFromProvider(provider, getter, aEncoder);
    }
#endif
    default: {
        break;
    }
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR GeneralCommissioningAttrAccess::ReadIfSupported(CHIP_ERROR (ConfigurationManager::*getter)(uint8_t &),
                                                           AttributeValueEncoder & aEncoder)
{
    uint8_t data;
    CHIP_ERROR err = (DeviceLayer::ConfigurationMgr().*getter)(data);
    if (err == CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE)
    {
        data = 0;
    }
    else if (err != CHIP_NO_ERROR)
    {
        return err;
    }

    return aEncoder.Encode(data);
}

CHIP_ERROR GeneralCommissioningAttrAccess::ReadBasicCommissioningInfo(AttributeValueEncoder & aEncoder)
{
    BasicCommissioningInfo::TypeInfo::Type basicCommissioningInfo;

    // TODO: The commissioner might use the critical parameters in BasicCommissioningInfo to initialize
    // the CommissioningParameters at the beginning of commissioning flow.
    basicCommissioningInfo.failSafeExpiryLengthSeconds  = CHIP_DEVICE_CONFIG_FAILSAFE_EXPIRY_LENGTH_SEC;
    basicCommissioningInfo.maxCumulativeFailsafeSeconds = CHIP_DEVICE_CONFIG_MAX_CUMULATIVE_FAILSAFE_SEC;
    static_assert(CHIP_DEVICE_CONFIG_MAX_CUMULATIVE_FAILSAFE_SEC >= CHIP_DEVICE_CONFIG_FAILSAFE_EXPIRY_LENGTH_SEC,
                  "Max cumulative failsafe seconds must be larger than failsafe expiry length seconds");

    return aEncoder.Encode(basicCommissioningInfo);
}

CHIP_ERROR GeneralCommissioningAttrAccess::ReadSupportsConcurrentConnection(AttributeValueEncoder & aEncoder)
{
    SupportsConcurrentConnection::TypeInfo::Type supportsConcurrentConnection;

    // TODO: The commissioner might use the critical parameters in BasicCommissioningInfo to initialize
    // the CommissioningParameters at the beginning of commissioning flow.
    supportsConcurrentConnection = (CHIP_DEVICE_CONFIG_SUPPORTS_CONCURRENT_CONNECTION) != 0;

    return aEncoder.Encode(supportsConcurrentConnection);
}

template <typename Provider, typename T>
CHIP_ERROR GeneralCommissioningAttrAccess::ReadFromProvider(Provider * const aProvider,
                                                            CHIP_ERROR (Provider::*const aConstGetter)(T &) const,
                                                            AttributeValueEncoder & aEncoder)
{
    if (nullptr == aProvider)
    {
        return CHIP_ERROR_PERSISTED_STORAGE_FAILED;
    }

    T value;
    CHIP_ERROR err = (aProvider->*aConstGetter)(value);
    if (err != CHIP_NO_ERROR)
    {
        return err;
    }

    return aEncoder.Encode(value);
}

#if CHIP_CONFIG_TC_REQUIRED
CHIP_ERROR checkTermsAndConditionsAcknowledgementsState(CommissioningErrorEnum & errorCode)
{
    EnhancedSetupFlowProvider * enhancedSetupFlowProvider = Server::GetInstance().GetEnhancedSetupFlowProvider();

    CHIP_ERROR err;

    uint16_t termsAndConditionsAcceptedAcknowledgements;
    bool hasRequiredTermAccepted;
    bool hasRequiredTermVersionAccepted;

    err = enhancedSetupFlowProvider->GetTermsAndConditionsAcceptedAcknowledgements(termsAndConditionsAcceptedAcknowledgements);
    if (!::chip::ChipError::IsSuccess(err))
    {
        ChipLogError(AppServer, "Failed to GetTermsAndConditionsAcceptedAcknowledgements");
        return err;
    }

    err = enhancedSetupFlowProvider->HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted(hasRequiredTermAccepted);
    if (!::chip::ChipError::IsSuccess(err))
    {
        ChipLogError(AppServer, "Failed to HasTermsAndConditionsRequiredAcknowledgementsBeenAccepted");
        return err;
    }

    err =
        enhancedSetupFlowProvider->HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted(hasRequiredTermVersionAccepted);
    if (!::chip::ChipError::IsSuccess(err))
    {
        ChipLogError(AppServer, "Failed to HasTermsAndConditionsRequiredAcknowledgementsVersionBeenAccepted");
        return err;
    }

    if (!hasRequiredTermVersionAccepted)
    {
        uint16_t requiredAcknowledgementsVersion = 0;
        (void) enhancedSetupFlowProvider->GetTermsAndConditionsRequiredAcknowledgementsVersion(requiredAcknowledgementsVersion);
        ChipLogProgress(AppServer, "Minimum terms and conditions version, 0x%04x, has not been accepted",
                        requiredAcknowledgementsVersion);
        errorCode = CommissioningErrorEnum::kTCMinVersionNotMet;
        return CHIP_NO_ERROR;
    }

    if (!hasRequiredTermAccepted)
    {
        uint16_t requiredAcknowledgements = 0;
        (void) enhancedSetupFlowProvider->GetTermsAndConditionsRequiredAcknowledgements(requiredAcknowledgements);

        ChipLogProgress(AppServer, "Required terms and conditions, 0x%04x,have not been accepted", requiredAcknowledgements);
        errorCode = (0 == termsAndConditionsAcceptedAcknowledgements) ? CommissioningErrorEnum::kTCAcknowledgementsNotReceived
                                                                      : CommissioningErrorEnum::kRequiredTCNotAccepted;
        return CHIP_NO_ERROR;
    }

    errorCode = CommissioningErrorEnum::kOk;
    return CHIP_NO_ERROR;
}
#endif

} // anonymous namespace

bool emberAfGeneralCommissioningClusterArmFailSafeCallback(app::CommandHandler * commandObj,
                                                           const app::ConcreteCommandPath & commandPath,
                                                           const Commands::ArmFailSafe::DecodableType & commandData)
{
    MATTER_TRACE_SCOPE("ArmFailSafe", "GeneralCommissioning");
    auto & failSafeContext = Server::GetInstance().GetFailSafeContext();
    Commands::ArmFailSafeResponse::Type response;

    ChipLogProgress(FailSafe, "GeneralCommissioning: Received ArmFailSafe (%us)",
                    static_cast<unsigned>(commandData.expiryLengthSeconds));

    /*
     * If the fail-safe timer is not fully disarmed, don't allow arming a new fail-safe.
     * If the fail-safe timer was not currently armed, then the fail-safe timer SHALL be armed.
     * If the fail-safe timer was currently armed, and current accessing fabric matches the fail-safe
     * context’s Fabric Index, then the fail-safe timer SHALL be re-armed.
     */

    FabricIndex accessingFabricIndex = commandObj->GetAccessingFabricIndex();

    // We do not allow CASE connections to arm the failsafe for the first time while the commissioning window is open in order
    // to allow commissioners the opportunity to obtain this failsafe for the purpose of commissioning
    if (!failSafeContext.IsFailSafeBusy() &&
        (!failSafeContext.IsFailSafeArmed() || failSafeContext.MatchesFabricIndex(accessingFabricIndex)))
    {
        // We do not allow CASE connections to arm the failsafe for the first time while the commissioning window is open in order
        // to allow commissioners the opportunity to obtain this failsafe for the purpose of commissioning
        if (!failSafeContext.IsFailSafeArmed() &&
            Server::GetInstance().GetCommissioningWindowManager().IsCommissioningWindowOpen() &&
            commandObj->GetSubjectDescriptor().authMode == Access::AuthMode::kCase)
        {
            response.errorCode = CommissioningErrorEnum::kBusyWithOtherAdmin;
            commandObj->AddResponse(commandPath, response);
        }
        else if (commandData.expiryLengthSeconds == 0)
        {
            // Force the timer to expire immediately.
            failSafeContext.ForceFailSafeTimerExpiry();
            // Don't set the breadcrumb, since expiring the failsafe should
            // reset it anyway.
            response.errorCode = CommissioningErrorEnum::kOk;
            commandObj->AddResponse(commandPath, response);
        }
        else
        {
            CheckSuccess(
                failSafeContext.ArmFailSafe(accessingFabricIndex, System::Clock::Seconds16(commandData.expiryLengthSeconds)),
                Failure);
            Breadcrumb::Set(commandPath.mEndpointId, commandData.breadcrumb);
            response.errorCode = CommissioningErrorEnum::kOk;
            commandObj->AddResponse(commandPath, response);
        }
    }
    else
    {
        response.errorCode = CommissioningErrorEnum::kBusyWithOtherAdmin;
        commandObj->AddResponse(commandPath, response);
    }

    return true;
}

bool emberAfGeneralCommissioningClusterCommissioningCompleteCallback(
    app::CommandHandler * commandObj, const app::ConcreteCommandPath & commandPath,
    const Commands::CommissioningComplete::DecodableType & commandData)
{
    MATTER_TRACE_SCOPE("CommissioningComplete", "GeneralCommissioning");

    DeviceControlServer * devCtrl = &DeviceLayer::DeviceControlServer::DeviceControlSvr();
    auto & failSafe               = Server::GetInstance().GetFailSafeContext();
    auto & fabricTable            = Server::GetInstance().GetFabricTable();

    ChipLogProgress(FailSafe, "GeneralCommissioning: Received CommissioningComplete");

    Commands::CommissioningCompleteResponse::Type response;
    if (!failSafe.IsFailSafeArmed())
    {
        response.errorCode = CommissioningErrorEnum::kNoFailSafe;
    }
    else
    {
        SessionHandle handle = commandObj->GetExchangeContext()->GetSessionHandle();
        // If not a CASE session, or the fabric does not match the fail-safe,
        // error out.
        if (handle->GetSessionType() != Session::SessionType::kSecure ||
            handle->AsSecureSession()->GetSecureSessionType() != SecureSession::Type::kCASE ||
            !failSafe.MatchesFabricIndex(commandObj->GetAccessingFabricIndex()))
        {
            response.errorCode = CommissioningErrorEnum::kInvalidAuthentication;
            ChipLogError(FailSafe, "GeneralCommissioning: Got commissioning complete in invalid security context");
        }
        else
        {
#if CHIP_CONFIG_TC_REQUIRED
            CheckSuccess(checkTermsAndConditionsAcknowledgementsState(response.errorCode), Failure);
#endif

            if (failSafe.NocCommandHasBeenInvoked())
            {
                CHIP_ERROR err = fabricTable.CommitPendingFabricData();
                if (err != CHIP_NO_ERROR)
                {
                    // No need to revert on error: CommitPendingFabricData always reverts if not fully successful.
                    ChipLogError(FailSafe, "GeneralCommissioning: Failed to commit pending fabric data: %" CHIP_ERROR_FORMAT,
                                 err.Format());
                }
                else
                {
                    ChipLogProgress(FailSafe, "GeneralCommissioning: Successfully commited pending fabric data");
                }
                CheckSuccess(err, Failure);
            }

            /*
             * Pass fabric of commissioner to DeviceControlSvr.
             * This allows device to send messages back to commissioner.
             * Once bindings are implemented, this may no longer be needed.
             */
            failSafe.DisarmFailSafe();
            CheckSuccess(
                devCtrl->PostCommissioningCompleteEvent(handle->AsSecureSession()->GetPeerNodeId(), handle->GetFabricIndex()),
                Failure);

            Breadcrumb::Set(commandPath.mEndpointId, 0);
            response.errorCode = CommissioningErrorEnum::kOk;
        }
    }

    commandObj->AddResponse(commandPath, response);

    return true;
}

bool emberAfGeneralCommissioningClusterSetRegulatoryConfigCallback(app::CommandHandler * commandObj,
                                                                   const app::ConcreteCommandPath & commandPath,
                                                                   const Commands::SetRegulatoryConfig::DecodableType & commandData)
{
    MATTER_TRACE_SCOPE("SetRegulatoryConfig", "GeneralCommissioning");
    DeviceControlServer * server = &DeviceLayer::DeviceControlServer::DeviceControlSvr();
    Commands::SetRegulatoryConfigResponse::Type response;

    auto & countryCode = commandData.countryCode;
    bool isValidLength = countryCode.size() == DeviceLayer::ConfigurationManager::kMaxLocationLength;
    if (!isValidLength)
    {
        ChipLogError(Zcl, "Invalid country code: '%.*s'", static_cast<int>(countryCode.size()), countryCode.data());
        commandObj->AddStatus(commandPath, Protocols::InteractionModel::Status::ConstraintError);
        return true;
    }

    if (commandData.newRegulatoryConfig > RegulatoryLocationTypeEnum::kIndoorOutdoor)
    {
        response.errorCode = CommissioningErrorEnum::kValueOutsideRange;
        // TODO: How does using the country code in debug text make sense, if
        // the real issue is the newRegulatoryConfig value?
        response.debugText = countryCode;
    }
    else
    {
        uint8_t locationCapability;
        uint8_t location = to_underlying(commandData.newRegulatoryConfig);

        CheckSuccess(ConfigurationMgr().GetLocationCapability(locationCapability), Failure);

        // If the LocationCapability attribute is not Indoor/Outdoor and the NewRegulatoryConfig value received does not match
        // either the Indoor or Outdoor fixed value in LocationCapability.
        if ((locationCapability != to_underlying(RegulatoryLocationTypeEnum::kIndoorOutdoor)) && (location != locationCapability))
        {
            response.errorCode = CommissioningErrorEnum::kValueOutsideRange;
            // TODO: How does using the country code in debug text make sense, if
            // the real issue is the newRegulatoryConfig value?
            response.debugText = countryCode;
        }
        else
        {
            CheckSuccess(server->SetRegulatoryConfig(location, countryCode), Failure);
            Breadcrumb::Set(commandPath.mEndpointId, commandData.breadcrumb);
            response.errorCode = CommissioningErrorEnum::kOk;
        }
    }

    commandObj->AddResponse(commandPath, response);

    return true;
}

bool emberAfGeneralCommissioningClusterSetTCAcknowledgementsCallback(
    chip::app::CommandHandler * commandObj, const chip::app::ConcreteCommandPath & commandPath,
    const chip::app::Clusters::GeneralCommissioning::Commands::SetTCAcknowledgements::DecodableType & commandData)
{
#if !CHIP_CONFIG_TC_REQUIRED
    return false;

#else
    auto & failSafeContext = Server::GetInstance().GetFailSafeContext();

    MATTER_TRACE_SCOPE("SetTCAcknowledgements", "GeneralCommissioning");
    Commands::SetTCAcknowledgementsResponse::Type response;
    EnhancedSetupFlowProvider * const enhancedSetupFlowProvider = Server::GetInstance().GetEnhancedSetupFlowProvider();
    uint16_t acknowledgements                                   = commandData.TCUserResponse;
    uint16_t acknowledgementsVersion                            = commandData.TCVersion;
    CheckSuccess(enhancedSetupFlowProvider->SetTermsAndConditionsAcceptance(acknowledgements, acknowledgementsVersion), Failure);
    CheckSuccess(checkTermsAndConditionsAcknowledgementsState(response.errorCode), Failure);
    failSafeContext.SetUpdateTermsAndConditionsHasBeenInvoked();
    commandObj->AddResponse(commandPath, response);
    return true;

#endif
}

namespace {
void OnPlatformEventHandler(const DeviceLayer::ChipDeviceEvent * event, intptr_t arg)
{
    if (event->Type == DeviceLayer::DeviceEventType::kFailSafeTimerExpired)
    {
        // Spec says to reset Breadcrumb attribute to 0.
        Breadcrumb::Set(0, 0);

#if CHIP_CONFIG_TC_REQUIRED
        if (event->FailSafeTimerExpired.updateTermsAndConditionsHasBeenInvoked)
        {
            // Clear terms and conditions acceptance on failsafe timer expiration
            Server::GetInstance().GetEnhancedSetupFlowProvider()->RevertTermsAndConditionsAcceptance();
        }
#endif
    }

    if (event->Type == DeviceLayer::DeviceEventType::kCommissioningComplete)
    {
#if CHIP_CONFIG_TC_REQUIRED
        auto & failSafeContext = Server::GetInstance().GetFailSafeContext();
        if (failSafeContext.UpdateTermsAndConditionsHasBeenInvoked())
        {
            // Commit terms and conditions acceptance on commissioning complete
            Server::GetInstance().GetEnhancedSetupFlowProvider()->CommitTermsAndConditionsAcceptance();
        }
#endif
    }
}

} // anonymous namespace

void MatterGeneralCommissioningPluginServerInitCallback()
{
    Breadcrumb::Set(0, 0);
    AttributeAccessInterfaceRegistry::Instance().Register(&gAttrAccess);
    DeviceLayer::PlatformMgrImpl().AddEventHandler(OnPlatformEventHandler);
}

namespace chip {
namespace app {
namespace Clusters {
namespace GeneralCommissioning {
void SetBreadcrumb(Attributes::Breadcrumb::TypeInfo::Type breadcrumb)
{
    Breadcrumb::Set(0, breadcrumb);
}
} // namespace GeneralCommissioning
} // namespace Clusters
} // namespace app
} // namespace chip
