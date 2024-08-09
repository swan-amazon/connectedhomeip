#
#    Copyright (c) 2022 Project CHIP Authors
#    All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

# test-runner-runs: run1
# test-runner-run/run1/app: ${ALL_CLUSTERS_APP}
# test-runner-run/run1/factoryreset: True
# test-runner-run/run1/quiet: True
# test-runner-run/run1/app-args: --discriminator 1234 --KVS kvs1 --trace-to json:${TRACE_APP}.json
# test-runner-run/run1/script-args: --storage-path admin_storage.json --commissioning-method on-network --discriminator 1234 --passcode 20202021 --trace-to json:${TRACE_TEST_JSON}.json --trace-to perfetto:${TRACE_TEST_PERFETTO}.perfetto

import logging
import random

import chip.clusters as Clusters
from chip.exceptions import ChipStackError
from matter_testing_support import DiscoveryFilterType, MatterBaseTest, async_test_body, default_matter_test_main
from mobly import asserts


class TC_CGEN_2_5(MatterBaseTest):

    async def commission_device(self) -> bool:
        dev_ctrl = self.default_controller
        conf = self.matter_test_config
        info = self.get_setup_payload_info()[0]

        if conf.commissioning_method == "on-network":
            try:
                await dev_ctrl.CommissionOnNetwork(
                    nodeId=self.dut_node_id,
                    setupPinCode=info.passcode,
                    filterType=info.filter_type,
                    filter=info.filter_value
                )
                return True
            except ChipStackError as e:
                logging.error("Commissioning failed: %s" % e)
                return False
        elif conf.commissioning_method == "ble-wifi":
            try:
                await dev_ctrl.CommissionWiFi(
                    info.filter_value,
                    info.passcode,
                    conf.self.dut_node_id,
                    conf.wifi_ssid,
                    conf.wifi_passphrase,
                    isShortDiscriminator=(info.filter_type == DiscoveryFilterType.SHORT_DISCRIMINATOR)
                )
                return True
            except ChipStackError as e:
                logging.error("Commissioning failed: %s" % e)
                return False
        elif conf.commissioning_method == "ble-thread":
            try:
                await dev_ctrl.CommissionThread(
                    info.filter_value,
                    info.passcode,
                    conf.self.dut_node_id,
                    conf.thread_operational_dataset,
                    isShortDiscriminator=(info.filter_type == DiscoveryFilterType.SHORT_DISCRIMINATOR)
                )
                return True
            except ChipStackError as e:
                logging.error("Commissioning failed: %s" % e)
                return False
        else:
            raise ValueError("Invalid commissioning method %s!" % conf.commissioning_method)

    async def verify_tc_attributes(self, expected_tc_version: int, expected_tc_acknowledgements: int):
        attr = Clusters.GeneralCommissioning.Attributes.TCAcceptedVersion
        tc_accepted_version = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=attr)
        asserts.assert_equal(tc_accepted_version, expected_tc_version,
                             f"Expected TCAcceptedVersion to be {expected_tc_version}, but got {tc_accepted_version}")

        attr = Clusters.GeneralCommissioning.Attributes.TCAcknowledgements
        tc_acknowedgements = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=attr)
        asserts.assert_equal(tc_acknowedgements, expected_tc_acknowledgements,
                             f"Expected TCAcknowledgements to be {expected_tc_acknowledgements}, but got {tc_acknowedgements}")

    @async_test_body
    async def test_TC_CGEN_2_5(self):
        self.th1 = self.default_controller
        self.discriminator = random.randint(0, 4095)

        logging.info('Step 1 - TH reads the TCAcceptedVersion attribute')
        attr = Clusters.GeneralCommissioning.Attributes.TCAcceptedVersion
        tc_accepted_version = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=attr)

        print(f"tc_accepted_version: {tc_accepted_version}")

        logging.info('Step 2 - TH reads the TCAcknowledgements attribute')
        attr = Clusters.GeneralCommissioning.Attributes.TCAcknowledgements
        tc_acknowedgements = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=attr)
        print(f"tc_acknowedgements: {tc_acknowedgements}")

        logging.info('Step 3 - TH reads the TCMinRequiredVersion attribute')
        attr = Clusters.GeneralCommissioning.Attributes.TCMinRequiredVersion
        tc_min_requried_version = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=attr)

        logging.info('Step 4 - TH reads the TCAcknowledgementsRequired attribute')
        attr = Clusters.GeneralCommissioning.Attributes.TCAcknowledgementsRequired
        tc_required = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=attr)

        logging.info('Step 5 - TH sends SetTCAcknowledgements with greater values than current and verify set')
        new_accepted_version = tc_accepted_version + 1
        new_acknowledgements = 65535

        cmd = Clusters.GeneralCommissioning.Commands.SetTCAcknowledgements(new_accepted_version, new_acknowledgements)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kOk, 'Incorrect error code')
        self.verify_tc_attributes(new_accepted_version, new_acknowledgements)

        logging.info('Step 6 - TH sends SetTCAcknowledgements with no accepted terms at version 0')
        cmd = Clusters.GeneralCommissioning.Commands.SetTCAcknowledgements(0, 0)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(
            resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kTCMinVersionNotMet, 'Incorrect error code'
        )
        self.verify_tc_attributes(new_accepted_version, new_acknowledgements)

        logging.info('Step 7 - TH sends SetTCAcknowledgements with no accepted terms at version 1')
        cmd = Clusters.GeneralCommissioning.Commands.SetTCAcknowledgements(1, 0)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(
            resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kRequiredTCNotAccepted, 'Incorrect error code'
        )
        self.verify_tc_attributes(new_accepted_version, new_acknowledgements)

        logging.info('Step 8 - TH sends ArmFailSafe with ExpiryLengthSeconds set to 60')
        cmd = Clusters.GeneralCommissioning.Commands.ArmFailSafe(60)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kNoError,
                             'Incorrect error code')

        logging.info('Step 9 - TH sends SetTCAcknowledgements with incremented TCVersion')
        new_accepted_version += 1
        cmd = Clusters.GeneralCommissioning.Commands.SetTCAcknowledgements(new_accepted_version, new_acknowledgements)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kNoError,
                             'Incorrect error code')

        logging.info('Step 10 - TH sends ArmFailSafe with ExpiryLengthSeconds set to 0')
        cmd = Clusters.GeneralCommissioning.Commands.ArmFailSafe(0)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kNoError,
                             'Incorrect error code')

        self.verify_tc_attributes(new_accepted_version, new_acknowledgements)

        logging.info('Step 11 - TH removes all fabrics from the device')
        fabrics = await self.read_single_attribute(dev_ctrl=self.th1, node_id=self.dut_node_id, endpoint=0, attribute=Clusters.OperationalCredentials.Attributes.Fabrics)
        for fabric in fabrics:
            if fabric.fabricIndex == self.th1.fabricId:
                continue
            cmd = Clusters.OperationalCredentials.Commands.RemoveFabric(fabric.fabricIndex)
            resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
            asserts.assert_equal(resp.statusCode, Clusters.OperationalCredentials.Enums.NodeOperationalCertStatusEnum.kOk)

        # Remove TH1 fabric last
        cmd = Clusters.OperationalCredentials.Commands.RemoveFabric(self.th1.fabricId)
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)

        # Give a prompt for the user to make the device in a commissionable state.
        # Currently with the sample apps the device doesn't have an opening commissioning window after removing all fabrics.
        print("Please return the device to a commissionable state if needed (reboot) and press any key to continue...")
        input()

        logging.info('Step 12 - TH commissions the DUT without setting TCs')
        self.th1.ResetTestCommissioner()
        self.th1.ExpireSessions(self.dut_node_id)

        # Don't set TCs for the next commissioning and skip CommissioningComplete so we can check the error code
        self.th1.SetTCRequired(False)
        self.th1.SetTCAcknowledgements(0, 0)
        self.th1.SetSkipCommissioningComplete(True)

        await self.commission_device()

        cmd = Clusters.GeneralCommissioning.Commands.CommissioningComplete()
        resp = await self.th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kTCAcknowledgementsNotReceived,
                             'Incorrect error code')


if __name__ == "__main__":
    default_matter_test_main()
