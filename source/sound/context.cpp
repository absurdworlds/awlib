/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <AL/al.h>
#include <AL/alc.h>
#include <system_error>
#include <string>
#include <vector>
#include <aw/utility/to_string.h>
#include <aw/fileformat/wav/reader.h>
#include <aw/io/input_file_stream.h>
namespace aw {
namespace audio {
enum class error {

};

std::error_category& sound_category();

struct sound_error_category : std::error_category {
	const char* name() const noexcept override
	{
		return "aw::sound";
	}

	std::string message(int i) const override
	{
		// TODO
		return to_string(i);
	}
};

struct sound_error : std::system_error {

};


struct device {
	device();
	~device();
	ALCdevice*  dev;
};

device::device()
{
	dev = alcOpenDevice(nullptr);
	if (!dev)
		throw std::runtime_error{ "could not open default device" };
}

device::~device()
{
	alcCloseDevice(dev);
}

struct context {
	context(device& dev);
	~context();
	bool make_current();
	bool is_current() const;

	device* dev;
	ALCcontext* ctx;
	ALuint      source;
};


context::context(device& dev)
	: dev(&dev)
{
	ctx = alcCreateContext(dev.dev, nullptr);
	if (!ctx)
		throw std::runtime_error{ "could not create context" };
}

context::~context()
{
	alcDestroyContext(ctx);
}

bool context::make_current()
{
	if (!alcMakeContextCurrent(ctx))
		return false;
	if (alcGetError(dev->dev) != ALC_NO_ERROR)
		return false;
	return true;
}

bool context::is_current()
{
	return ctx == alcGetCurrentContext();
}


ALenum to_al_format(short channels, short samples)
{
        bool stereo = (channels > 1);

        switch (samples) {
        case 16:
                if (stereo)
                        return AL_FORMAT_STEREO16;
                else
                        return AL_FORMAT_MONO16;
        case 8:
                if (stereo)
                        return AL_FORMAT_STEREO8;
                else
                        return AL_FORMAT_MONO8;
        default:
                return -1;
        }
}

struct buffer {
	buffer(context& ctx, wav::wave_data& wave)
		: ctx{&ctx}
	{
		if (!ctx.is_current()) ctx.make_current();

		alGenBuffers(1, &buf);
		if (alGetError() != AL_NO_ERROR)
			throw std::runtime_error{ "could not create buffer" };

		auto fmt = to_al_format(wave.channels, wave.bits_per_sample);
		alBufferData(buf, fmt, wave.data.data(), wave.data.size(), wave.sample_rate);
		if (alGetError() != AL_NO_ERROR) {
			cleanup();
			throw std::runtime_error{ "could not fill buffer with wave data" };
		}
	}

	~buffer() { cleanup(); }

	context* ctx;
	ALuint   buf;

private:
	void cleanup()
	{
		alDeleteBuffers(1, &buf);
	}

};

struct sound {
	sound(context& ctx, buffer& buf)
		: ctx{&ctx}, buf{&buf}
	{
		alGenSources(1, &source);
		if (alGetError() != AL_NO_ERROR)
			throw std::runtime_error{ "could not create sound source" };

		alSourcei(source,  AL_SOURCE_RELATIVE, AL_TRUE);
		alSourcef(source,  AL_PITCH, 1);
		alSourcef(source,  AL_GAIN, 1);
		alSource3f(source, AL_POSITION, 0, 2, 0);
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		alSourcei(source,  AL_LOOPING, AL_FALSE);

		alSourcei(source, AL_BUFFER, buf.buf);
		if (alGetError() != AL_NO_ERROR)
			throw std::runtime_error{ "could not bind buffer to source" };
	}


	bool play()
	{
		alSourcePlay(source);
		return alGetError() == AL_NO_ERROR;
	}


	context* ctx;
	buffer*  buf;
	ALuint source;
};

} // namespace audio
} // namespace aw

#include <chrono>
#include <iostream>
namespace aw {
int main()
{
	using namespace audio;

	device  dev;
	context ctx{dev};
	ctx.make_current();

	io::input_file_stream file("glass.wav");
	auto wave = wav::read(file);

	buffer buf{ctx, *wave};
	sound snd{ctx, buf};

	snd.play();

	ALint source_state;
	do {
		alGetSourcei(snd.source, AL_SOURCE_STATE, &source_state);
	} while (source_state == AL_PLAYING);

	{
		io::input_file_stream file("sine.wav");
		wave = wav::read(file);
	}


	device  dev2;
	context ctx2{dev2};
	ctx2.make_current();
	buffer buf2{ctx, *wave};
	ctx.make_current();

	sound snd2{ctx, buf2};
	//ctx2.make_current();

	using namespace std::chrono;

	float pos = -10;
	float vel = 10;
	auto time1 = steady_clock::now();
	alDopplerFactor(1.0);
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
	alSourcei(snd2.source, AL_REFERENCE_DISTANCE, 0.5);
	alSourcei(snd2.source, AL_MAX_DISTANCE, 9);
	alSourcei(snd2.source,  AL_LOOPING, AL_TRUE);
	alSource3f(snd2.source, AL_POSITION, pos, 0, 0);
	alSource3f(snd2.source, AL_VELOCITY, vel, 0, 0);
	snd2.play();
	do {
		using dur = duration<double>;
		auto time2 = steady_clock::now();
		pos += vel * duration_cast<dur>(time2 - time1).count();
		time1 = time2;
		alSource3f(snd2.source, AL_POSITION, pos, 0, 0);
		alGetSourcei(snd2.source, AL_SOURCE_STATE, &source_state);
		std::cout << pos << '\n';
	} while ((source_state == AL_PLAYING) && (pos < 100));
}
} // namespace aw

int main()
{
	return aw::main();
}
