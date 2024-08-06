use hound;
use knf_rs::compute_fbank;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file_path = "short.wav";
    let mut wav_reader = hound::WavReader::open(file_path)?;

    // Read samples as i16
    let i16_samples: Vec<i16> = wav_reader.samples::<i16>().map(|s| s.unwrap()).collect();

    // Convert i16 samples to f32
    let mut float_samples = vec![0.0; i16_samples.len()];
    knf_rs::convert_integer_to_float_audio(&i16_samples, &mut float_samples);

    // Get the sample rate from the WAV header
    // let sample_rate = wav_reader.spec().sample_rate;

    // Call the compute_fbank function
    let features = compute_fbank(&float_samples)?;

    // Print the computed features (if needed)
    println!("{:?}", features.row(0));

    Ok(())
}
