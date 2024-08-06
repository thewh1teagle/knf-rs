# Building


*Build knf*

```console
cmake -B build .  -DKALDI_NATIVE_FBANK_BUILD_PYTHON=OFF -DKALDI_NATIVE_FBANK_BUILD_TESTS=OFF
cmake --build build --config Release
```