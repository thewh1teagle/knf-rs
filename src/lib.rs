#[cxx::bridge]
pub(crate) mod ffi {
    unsafe extern "C++" {
        include!("knf/kaldi-native-fbank/csrc/feature-fbank.h");

    }
}