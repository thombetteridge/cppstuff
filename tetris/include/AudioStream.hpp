#ifndef RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
#define RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RaylibException.hpp"

namespace raylib {
/**
 * AudioStream management functions
 */
class AudioStream : public ::AudioStream {
 public:
    AudioStream(const ::AudioStream& music) {
        set(music);
    }

    AudioStream(rAudioBuffer* buffer = nullptr,
            rAudioProcessor *processor = nullptr,
            unsigned int sampleRate = 0,
            unsigned int sampleSize = 0,
            unsigned int channels = 0) : ::AudioStream{buffer, processor, sampleRate, sampleSize, channels} {
        // Nothing.
    }

    /**
     * Init audio stream (to stream raw audio pcm data)
     *
     * @throws raylib::RaylibException Throws if the AudioStream failed to load.
     */
    AudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels = 2) {
        Load(sampleRate, sampleSize, channels);
    }

    AudioStream(const AudioStream&) = delete;

    AudioStream(AudioStream&& other) {
        set(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;
    }

    ~AudioStream() {
        Unload();
    }

    GETTERSETTER(rAudioBuffer *, Buffer, buffer)
    GETTERSETTER(rAudioProcessor *, Processor, processor)
    GETTERSETTER(unsigned int, SampleRate, sampleRate)
    GETTERSETTER(unsigned int, SampleSize, sampleSize)
    GETTERSETTER(unsigned int, Channels, channels)

    auto operator=(const ::AudioStream& stream) -> AudioStream&
    {
        set(stream);
        return *this;
    }

    auto operator=(const AudioStream&) -> AudioStream& = delete;

    auto operator=(AudioStream&& other) noexcept -> AudioStream&
    {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;

        return *this;
    }

    /**
     * Update audio stream buffers with data
     */
    inline auto Update(const void* data, int samplesCount) -> AudioStream&
    {
        ::UpdateAudioStream(*this, data, samplesCount);
        return *this;
    }

    /**
     * Unload audio stream and free memory
     */
    inline void Unload() {
        ::UnloadAudioStream(*this);
    }

    /**
     * Check if any audio stream buffers requires refill
     */
    inline auto IsProcessed() const -> bool
    {
        return ::IsAudioStreamProcessed(*this);
    }

    /**
     * Play audio stream
     */
    inline auto Play() -> AudioStream&
    {
        ::PlayAudioStream(*this);
        return *this;
    }

    /**
     * Pause audio stream
     */
    inline auto Pause() -> AudioStream&
    {
        ::PauseAudioStream(*this);
        return *this;
    }

    /**
     * Resume audio stream
     */
    inline auto Resume() -> AudioStream&
    {
        ::ResumeAudioStream(*this);
        return *this;
    }

    /**
     * Check if audio stream is playing
     */
    inline auto IsPlaying() const -> bool
    {
        return ::IsAudioStreamPlaying(*this);
    }

    /**
     * Stop audio stream
     */
    inline auto Stop() -> AudioStream&
    {
        ::StopAudioStream(*this);
        return *this;
    }

    /**
     * Set volume for audio stream (1.0 is max level)
     */
    inline auto SetVolume(float volume = 1.0f) -> AudioStream&
    {
        ::SetAudioStreamVolume(*this, volume);
        return *this;
    }

    /**
     * Set pitch for audio stream (1.0 is base level)
     */
    inline auto SetPitch(float pitch) -> AudioStream&
    {
        ::SetAudioStreamPitch(*this, pitch);
        return *this;
    }

    /**
     * Set pan for audio stream (0.5 is centered)
     */
    inline auto SetPan(float pan = 0.5f) -> AudioStream&
    {
        ::SetAudioStreamPitch(*this, pan);
        return *this;
    }

    /**
     * Default size for new audio streams
     */
    inline static void SetBufferSizeDefault(int size) {
        ::SetAudioStreamBufferSizeDefault(size);
    }

    /**
     * Audio thread callback to request new data
     */
    inline void SetCallback(::AudioCallback callback) {
        ::SetAudioStreamCallback(*this, callback);
    }

    /**
     * Attach audio stream processor to stream
     */
    inline void AttachProcessor(::AudioCallback processor) {
        ::SetAudioStreamCallback(*this, processor);
    }

    /**
     * Detach audio stream processor from stream
     */
    inline void DetachProcessor(::AudioCallback processor) {
        ::SetAudioStreamCallback(*this, processor);
    }

    /**
     * Retrieve whether or not the audio stream is ready.
     */
    auto IsReady() -> bool
    {
        return ::IsAudioStreamReady(*this);
    }

    /**
     * Load audio stream (to stream raw audio pcm data)
     *
     * @throws raylib::RaylibException Throws if the AudioStream failed to load.
     */
    void Load(unsigned int SampleRate, unsigned int SampleSize, unsigned int Channels = 2) {
        Unload();
        set(::LoadAudioStream(SampleRate, SampleSize, Channels));
        if (!IsReady()) {
            throw RaylibException("Failed to load audio stream");
        }
    }

 private:
    void set(const ::AudioStream& stream) {
        buffer = stream.buffer;
        processor = stream.processor;
        sampleRate = stream.sampleRate;
        sampleSize = stream.sampleSize;
        channels = stream.channels;
    }
};
}  // namespace raylib

using RAudioStream = raylib::AudioStream;

#endif  // RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
