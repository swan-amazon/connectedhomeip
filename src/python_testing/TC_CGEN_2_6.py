#
#    Copyright (c) 2024 Project CHIP Authors
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

# === BEGIN CI TEST ARGUMENTS ===
# test-runner-runs: run1
# test-runner-run/run1/app: ${TERMS_AND_CONDITIONS_APP}
# test-runner-run/run1/factoryreset: True
# test-runner-run/run1/quiet: True
# test-runner-run/run1/app-args: --KVS kvs1
# test-runner-run/run1/script-args: --in-test-commissioning-method on-network --qr-code MT:-24J0AFN00KA0648G00 --trace-to json:log
# === END CI TEST ARGUMENTS ===

import random

import chip.clusters as Clusters
from chip import ChipDeviceCtrl
from matter_testing_support import MatterBaseTest, TestStep, async_test_body, default_matter_test_main
from mobly import asserts


class TC_CGEN_2_6(MatterBaseTest):
    def desc_TC_CGEN_2_6(self) -> str:
        return "[TC-CGEN-2.6] Verification For CommissioningComplete no terms accepted when required [DUT as Server]"

    def steps_TC_CGEN_2_6(self) -> list[TestStep]:
        return [
            TestStep("1",  "TH starts commissioning the DUT. It performs all commissioning steps from ArmFailSafe to CommissioningComplete, except for TC configuration with SetTCAcknowledgements.", is_commissioning=False),
        ]

    @async_test_body
    async def test_TC_CGEN_2_6(self):
        th1: ChipDeviceCtrl.ChipDeviceController = self.default_controller
        self.discriminator = random.randint(0, 4095)

        self.step("1")

        # Don't set TCs for the next commissioning and skip CommissioningComplete so we can manually call CommissioningComplete in order to check the response error code
        th1.SetTCRequired(False)
        th1.SetSkipCommissioningComplete(True)
        self.matter_test_config.commissioning_method = self.matter_test_config.in_test_commissioning_method
        await self.commission_devices()

        cmd = Clusters.GeneralCommissioning.Commands.CommissioningComplete()
        resp = await th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(
            resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kTCAcknowledgementsNotReceived, 'Incorrect error code')

        cmd = Clusters.GeneralCommissioning.Commands.SetTCAcknowledgements(1, 0)
        resp = await th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(
            resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kRequiredTCNotAccepted, 'Incorrect error code')

        cmd = Clusters.GeneralCommissioning.Commands.CommissioningComplete()
        resp = await th1.SendCommand(nodeid=self.dut_node_id, endpoint=0, payload=cmd, timedRequestTimeoutMs=6000)
        asserts.assert_equal(
            resp.errorCode, Clusters.GeneralCommissioning.Enums.CommissioningErrorEnum.kTCAcknowledgementsNotReceived, 'Incorrect error code')


if __name__ == "__main__":
    default_matter_test_main()
