# knf-rs

Rust bindings to [kaldi-native-fbank](https://github.com/csukuangfj/kaldi-native-fbank)

Knf C++ flow:
1. Create frameOptions
2. Create melOptions
3. Create fbankOptions(frameOptions, melOptions)
4. Create onlineFbank(fbankOptions)
5. fbank.accept_waveform(sample_rate: u32, samples: Vec<f32>)
6. fbank.input_finished()
7. for i in fbank.num_frames_ready():
8. fbank.get_frame(i)
