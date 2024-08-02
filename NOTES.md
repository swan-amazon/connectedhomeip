scripts/setup/nxp/update_nxp_sdk.py
gn gen --check --fail-on-unused-args --export-compile-commands --root=examples/contact-sensor-app/nxp/k32w/k32w0 out/nxp-k32w0-freertos-contact-sensor-low-power



 1228  exit
 1229  cd src/python_testing/TC_CGEN_2_4.py
 1230  cd src/python_testing/
 1231  python3 ./TC_CGEN_2_4.py 
 1232  export PYTHONPATH=/workspace/connectedhomeip/src/controller/python
 1233  python3 ./TC_CGEN_2_4.py 
 1234  python3 -mpip install ./requirements.txt 
 1235  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 -mpip install ./requirements.txt 
 1236  set -o vi
 1237  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 -mpip install -r ./requirements.txt 
 1238  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 ./TC_CGEN_2_4.py 
 1239  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 -mpip install rich
 1240  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 ./TC_CGEN_2_4.py 
 1241  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 -mpip install dacite
 1242  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 ./TC_CGEN_2_4.py ]\
 1243  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 ./TC_CGEN_2_4.py 
 1244  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 -mpip install aenum
 1245  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 ./TC_CGEN_2_4.py 
 1246  ls /workspace/connectedhomeip/src/controller/python/chip/native
 1247  cd /workspace/connectedhomeip/src/controller/python
 1248  cd /workspace/connectedhomeip/
 1249  scripts/build_python.sh -m platform -i separate
 1250  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python
 1251  export PATH=$PATH:/workspace/connectedhomeip/.environment/pigweed-venv/bin
 1252  scripts/build_python.sh -m platform -i separate
 1253  history


source separate/bin/activate



//src/controller/python:ChipDeviceCtrl(//build/toolchain/host:linux_x64_clang)
//src/controller/python:ChipDeviceCtrl(//build/toolchain/host:linux_x64_gcc)


gn gen --args='chip_controller=true target_cpu="x64" is_clang=true' out/unified/
ninja -C out/unified/ src/controller/python:ChipDeviceCtrl

mkdir -p /workspace/connectedhomeip/src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/

/workspace/connectedhomeip/src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/_ChipDeviceCtrl.so




---


1287  ninja -C out/unified/ '//src/controller/python:ChipDeviceCtrl'
 1288  ninja -C out/unified //src/controller/python:ChipDeviceCtrl --toolchain=//build/toolchain/host:linux_x64_gcc
 1289  ninja -C out/unified/ -t list
 1290  find out/unified/ | grep ChipDeviceCtrl
 1291  ninja -C out/unified/linux_x64_gcc/obj/src/controller/python/ChipDeviceCtrl.ninja
 1292  ninja -C out/unified/linux_x64_gcc/obj/src/controller/python/
 1293  chip-repl
 1294  scripts/build_python.sh --help`
 1295  scripts/build_python.sh --help
 1296  gn desc out/unified  '//src/controller/python'
 1297  gn desc out/unified  '//src/controller/python' all
 1298  ninja -C out/unified/ src/controller/python:ChipDeviceCtrl
 1299  gn ls out/unified/ | less
 1300  ninja -C out/unified/ build/toolchain/host:linux_x64_clang
 1301  ninja -C out/unified/ //build/toolchain/host:linux_x64_clang
 1302  gn ls out/unified/ | grep ChipDeviceCtrl
 1303  gen gen --args='chip_controller=true' out/unified/
 1304  gn gen --args='chip_controller=true' out/unified/
 1305  ninja -C out/unified/
 1306  gn gen --args='chip_controller=true target_cpu="x64" is_clang=true' out/unified/
 1307  gn gen --args='chip_controller=true' out/unified/
 1308  ninja -C out/unified/
 1309  gn gen --args='chip_controller=true target_cpu="x64" is_clang=true' out/unified/
 1310  ninja -C out/unified/
 1311  gn ls out/unified/
 1312  gn ls out/unified/ | grep ChipDeviceCtrl
 1313  ninja -C out/unified/ src/controller/python:ChipDeviceCtrl
 1314  python /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1315  cp obj/src/controller/python/chip/_ChipDeviceCtrl.so /workspace/connectedhomeip/src/controller/python/chip/native/
 1316  cp out/unified/obj/src/controller/python/chip/_ChipDeviceCtrl.so /workspace/connectedhomeip/src/controller/python/chip/native/
 1317  python /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1318  ls -al /workspace/connectedhomeip/src/controller/python/chip/native
 1319  /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1320  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1321  ls /workspace/connectedhomeip/src/controller/python/chip/native
 1322  file /workspace/connectedhomeip/src/controller/python/chip/native/_ChipDeviceCtrl.so 
 1323  sudo apt-get update
 1324  file /workspace/connectedhomeip/src/controller/python/chip/native/_ChipDeviceCtrl.so 
 1325  sudo apt-get install file
 1326  file /workspace/connectedhomeip/src/controller/python/chip/native/_ChipDeviceCtrl.so 
 1327  nm /workspace/connectedhomeip/src/controller/python/chip/native/_ChipDeviceCtrl.so
 1328  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1329  ls -al /workspace/connectedhomeip/src/controller/python/chip/native
 1330  mkdir /workspace/connectedhomeip/src/controller/python/chip/native/.libs
 1331  mv /workspace/connectedhomeip/src/controller/python/chip/native/_ChipDeviceCtrl.so /workspace/connectedhomeip/src/controller/python/chip/native/.libs/
 1332  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1333  ls /workspace/connectedhomeip/src/controller/python/chip/native/build/x86_64-*-linux*/src/controller/python/.libs/_ChipDeviceCtrl.so
 1334  find out -name _ChipDeviceCtrl.so
 1335  ls out/python_lib/
 1336  ls out
 1337  mkdir -p /workspace/connectedhomeip/src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/
 1338  cp out/unified/obj/src/controller/python/chip/_ChipDeviceCtrl.so /workspace/connectedhomeip/src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/
 1339  ls /workspace/connectedhomeip/src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/_ChipDeviceCtrl.so
 1340  /workspace/connectedhomeip/.environment/pigweed-venv/bin/python3 /workspace/connectedhomeip/src/python_testing/TC_CGEN_2_4.py
 1341  history

./scripts/build_python.sh --enable_pybindings true

---

```
source ./scripts/bootscript.sh
./.environment/pigweed-venv/bin/python3 -mpip install aenum dacite rich -r ./src/python_testing/requirements.txt

gn gen --args='chip_controller=true target_cpu="x64" is_clang=true' out/python_lib/
ninja -C out/python_lib/ src/controller/python:ChipDeviceCtrl

mkdir -p ./src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/
cp ./out/python_lib/obj/src/controller/python/chip/_ChipDeviceCtrl.so ./src/controller/python/chip/native/build/x86_64--linux/src/controller/python/.libs/
```


```
export PYTHONPATH=./src/controller/python
./.environment/pigweed-venv/bin/python3 ./src/python_testing/TC_CGEN_2_4.py
```
