use hound;
use knf_rs::compute_fbank;
use std::fs::File;
use std::io::BufReader;

fn main() {
    let file_path = "short.wav";
    let reader = BufReader::new(File::open(file_path).unwrap());
    let mut wav_reader = hound::WavReader::new(reader).unwrap();

    // Read samples as f32
    let samples: Vec<f32> = wav_reader
        .samples::<i16>()
        .map(|sample| sample.unwrap() as f32 / i16::MAX as f32)
        .collect();

    // Get the sample rate from the WAV header
    let sample_rate = wav_reader.spec().sample_rate;

    // Call the compute_fbank function
    let features = compute_fbank(&samples).unwrap();

    // Print the computed features (if needed)
    println!("{:?}", features.row(0));
}
