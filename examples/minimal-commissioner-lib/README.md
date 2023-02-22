The example provides a limited data model definition to disable generating code for clusters which are never used during device commissioning.

# Building the example

```
./scripts/run_in_build_env.sh "./scripts/build/build_examples.py \
   --target android-${cpu}-minimal-commissioner-lib \
   build"
```

Where cpu is one of: `arm`, `arm64` `x86` `x64`.

# Manually generating and building the example

```
source scripts/activate.sh

cd examples/minimal-commissioner-lib/android

gn gen -v out/jameswan --args="\
    target_os=\"android\" \
    target_cpu=\"arm64\" \
    android_ndk_root=\"${ANDROID_NDK_HOME}\" \
    android_sdk_root=\"${ANDROID_HOME}\" \
    is_debug=false \
    optimize_for_size=true"

ninja -C out
```

# Re-generated IDL definitions

The `examples/minimal-commissioner-lib/data_model/commissioner-clusters.zap` serves as the main input for the code generation.

1. Given `commissioner-clusters.zap` generate `commissioner-clusters.matter`
    ```
    ./scripts/tools/zap/generate.py examples/minimal-commissioner-lib/data_model/commissioner-clusters.zap \
        -t src/app/zap-templates/matter-idl.json \
        -o examples/minimal-commissioner-lib/data_model/
    ```

2. Given `commissioner-clusters.zap` generate Java and C++ bindings
    ```
    ./scripts/tools/zap/generate.py examples/minimal-commissioner-lib/data_model/commissioner-clusters.zap \
        -t src/controller/java/templates/templates.json \
        -o examples/minimal-commissioner-lib/data_model/
    ```