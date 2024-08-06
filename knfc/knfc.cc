#include "kaldi-native-fbank/csrc/feature-window.h"
#include "kaldi-native-fbank/csrc/mel-computations.h"
#include "kaldi-native-fbank/csrc/feature-fbank.h"
#include "kaldi-native-fbank/csrc/online-feature.h"
#include "knfc.h"
#include <iostream>


void DestroyFbankResult(FbankResult* result) {
    if (result) {
        delete[] result->frames;
        result->frames = nullptr;
        result->num_frames = 0;
        result->num_bins = 0;
    }
}

FbankResult ComputeFbank(const float *waveform, int32_t waveform_size) {
    knf::FrameExtractionOptions frame_opts;
    knf::MelBanksOptions mel_opts;
    knf::FbankOptions fbank_opts;

    // Frame options
    frame_opts.dither = 0.0;
    frame_opts.samp_freq = 16000;
    frame_opts.snip_edges = true;

    // Mel options
    mel_opts.num_bins = 80;
    mel_opts.debug_mel = false;

    fbank_opts.mel_opts = mel_opts;
    fbank_opts.frame_opts = frame_opts;
    knf::OnlineFbank fbank(fbank_opts);
    fbank.AcceptWaveform(frame_opts.samp_freq, waveform, waveform_size);
    fbank.InputFinished();

    int32_t num_frames = fbank.NumFramesReady();
    int32_t num_bins = mel_opts.num_bins;

    // Allocate memory for the frames
    float* frames = new float[num_frames * num_bins];

    // Fill the frames
    for (int32_t i = 0; i < num_frames; i++) {
        const float* frame = fbank.GetFrame(i);
        std::copy(frame, frame + num_bins, frames + i * num_bins);
    }

    FbankResult result;
    result.frames = frames;
    result.num_frames = num_frames;
    result.num_bins = num_bins;
    return result;
}

// int main() {
//     // Generate dummy data: a simple sine wave
//     int32_t sample_rate = 16000;
//     int32_t duration = 1; // 1 second
//     int32_t waveform_size = sample_rate * duration;
//     std::vector<float> waveform(waveform_size);

//     float frequency = 440.0; // A4 note
//     for (int32_t i = 0; i < waveform_size; ++i) {
//         waveform[i] = 0.5 * sin(2.0 * M_PI * frequency * i / sample_rate);
//     }

//     FbankResult result = ComputeFbank(waveform.data(), waveform_size);

//     for (int32_t i = 0; i < result.num_frames; ++i) {
//         for (int32_t j = 0; j < result.num_bins; ++j) {
//             std::cout << result.frames[i * result.num_bins + j] << " ";
//         }
//         std::cout << std::endl;
//     }

//     DestroyFbankResult(&result);

//     return 0;
// }