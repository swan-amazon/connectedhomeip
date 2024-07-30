/*
 *   Copyright (c) 2021 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

package com.google.chip.chiptool.setuppayloadscanner

import android.net.Uri
import android.os.Bundle
import android.util.Base64
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import com.android.volley.Request
import com.android.volley.Response.Listener
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.Volley
import com.google.chip.chiptool.R
import com.google.chip.chiptool.databinding.ChipLedgerInfoFragmentBinding
import com.google.chip.chiptool.util.FragmentUtil
import com.google.gson.Gson
import java.io.BufferedReader
import java.io.InputStreamReader
import org.json.JSONObject

/** Show the [CHIPDeviceInfo] from Ledger */
class CHIPLedgerDetailsFragment : Fragment() {
  private lateinit var deviceInfo: CHIPDeviceInfo
  private var _binding: ChipLedgerInfoFragmentBinding? = null
  private val binding
    get() = _binding!!

  override fun onCreateView(
    inflater: LayoutInflater,
    container: ViewGroup?,
    savedInstanceState: Bundle?
  ): View {
    _binding = ChipLedgerInfoFragmentBinding.inflate(inflater, container, false)
    deviceInfo = checkNotNull(requireArguments().getParcelable(ARG_DEVICE_INFO))
    val queue = Volley.newRequestQueue(context)
    // VID / PID
    binding.vendorIdTv.text = "${deviceInfo.vendorId}"
    binding.productIdTv.text = "${deviceInfo.productId}"

    // Ledger api url
    val url =
      Uri.parse(DCL_API_ROOT_URL)
        .buildUpon()
        .appendPath("${deviceInfo.vendorId}")
        .appendPath("${deviceInfo.productId}")
        .build()
        .toString()
    Log.d(TAG, "Dcl request Url: $url")

    val context = getContext()!!
    val mockDclRequestsResponsesRaw = readRawResourceFile(R.raw.mock_dcl_responses_json)
    val mockDclRequestsResponses: org.json.JSONArray = org.json.JSONArray(mockDclRequestsResponsesRaw)

    val mockDclRequestsResponseMap = HashMap<String, org.json.JSONObject>()
    for (i in 0 until mockDclRequestsResponses.length()) {
      val mockDclRequestsResponse = mockDclRequestsResponses.getJSONObject(i)

      val mockDclRequest: org.json.JSONObject = mockDclRequestsResponse.getJSONObject("request")
      val mockDclResponse: org.json.JSONObject = mockDclRequestsResponse.getJSONObject("response")

      val mockDclRequestURL = mockDclRequest.getString("url")
      val mockDclResponseBody = mockDclResponse.getJSONObject("body")

      mockDclRequestsResponseMap.put(mockDclRequestURL, mockDclResponseBody)
      Log.d(TAG, "mockDclRequestURL= $mockDclRequestURL")
      Log.d(TAG, "mockDclResponseBody= $mockDclResponseBody")
    }

    Log.d(TAG, "Request url= $url")
    val response: org.json.JSONObject = mockDclRequestsResponseMap.get(url.toString())!!
    Log.d(TAG, "Response from dcl $response")
    Toast.makeText(context, "Enhanced Setup Flow: $response", Toast.LENGTH_LONG).show()

    val enhancedSetupFlowOptions = response.optInt("enhancedSetupFlowOptions", 0)

    if (0 != (enhancedSetupFlowOptions and 0b00000001)) {
      Toast.makeText(context, "Enhanced Setup Flow supported!", Toast.LENGTH_SHORT).show()

      binding.commissionBtn.setOnClickListener {
        FragmentUtil.getHost(this@CHIPLedgerDetailsFragment, Callback::class.java)
          ?.handleEnhancedSetupFlowClicked()
      }

      binding.commissionBtn.visibility = View.VISIBLE
    }

    return binding.root
  }

  override fun onDestroyView() {
    super.onDestroyView()
    _binding = null
  }

  private fun readRawResourceFile(resourceId: Int): String? {
      return try {
          val inputStream = resources.openRawResource(resourceId)
          val bufferedReader = BufferedReader(InputStreamReader(inputStream))
          val stringBuilder = StringBuilder()
          var line: String? = bufferedReader.readLine()
          while (line != null) {
              stringBuilder.append(line)
              line = bufferedReader.readLine()
          }
          bufferedReader.close()
          inputStream.close()
          stringBuilder.toString()
      } catch (e: Exception) {
          Log.e("MainActivity", "Error reading raw resource file", e)
          null
      }
  }

  /** Interface for notifying the host. */
  interface Callback {
    /** Notifies listener of Custom flow redirect button click. */
    fun handleCustomFlowRedirectClicked(redirectUrl: String)

    /** Notifies listener of Enhanced Setup flow button click. */
    fun handleEnhancedSetupFlowClicked()
  }

  companion object {
    private const val TAG = "CUSTOM_FLOW"
    private const val ARG_DEVICE_INFO = "device_info"
    private const val DCL_CUSTOM_FLOW_URL_KEY = "commissioningCustomFlowUrl";
    private const val DCL_API_ROOT_URL = "https://on.dcl.csa-iot.org/dcl/model/models";
    private const val CUSTOM_FLOW_RETURN_URL = "mt://modelinfo";

    @JvmStatic
    fun newInstance(deviceInfo: CHIPDeviceInfo): CHIPLedgerDetailsFragment {
      return CHIPLedgerDetailsFragment().apply {
        arguments = Bundle(1).apply { putParcelable(ARG_DEVICE_INFO, deviceInfo) }
      }
    }
  }
}
