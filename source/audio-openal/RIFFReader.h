#ifndef _hrengin_RIFF_
#define _hrengin_RIFF_

#include <string>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/filesystem/IReadFile.h>

#include "SoundSample.h"

namespace hrengin {
namespace audio {

// assuming Little Endian
enum class WaveFields {
	RiffHeader = 'FFIR',
	WaveTag = 'EVAW',
	Format = ' tmf',
	DataTag = 'atad'
};

bool readWAV(std::string path, SoundSample& sample) 
{
	io::IReadFile* file = io::openReadFile(path);

	if(!file->isOpen()) {
		return false;
	}

	u32 riffHeader;
	file->read(&riffHeader,4);
	u32 fileSize;
	file->read(&fileSize,4);
	u32 waveTag;
	file->read(&waveTag,4);
	u32 format;
	file->read(&format,4);

	if((WaveFields)riffHeader != WaveFields::RiffHeader) {
		return false;
	} else if((WaveFields)waveTag != WaveFields::WaveTag) {
		return false;
	} else if((WaveFields)format != WaveFields::Format) {
		return false;
	}
	
	u32 headerLength;
	file->read(&headerLength,4);
	u16 type;
	file->read(&type,2);
	u16 channels;
	file->read(&channels,2);
	u32 sampleRate;
	file->read(&sampleRate,4);
	u32 bitRate;
	file->read(&bitRate,4);
	u16 bytesPerSample;
	file->read(&bytesPerSample,2);
	u16 bitsPerSample;
	file->read(&bitsPerSample,2);

	u32 dataTag;
	file->read(&dataTag,4);

	if((WaveFields)dataTag != WaveFields::DataTag) {
		return false;
	}

	u32 dataSize;
	file->read(&dataSize,4);
	
	sample.bitsPerSample = bitsPerSample;
	sample.channels = channels;
	sample.sampleRate = sampleRate;
	sample.size = dataSize;

	i8* data = new i8[dataSize*2];
	i32 bytesRead = file->read(data,dataSize);
	if(bytesRead < dataSize) {
		return false;
	}
	
	sample.data = data;

	delete file;
	return true;
}

}
} //namespace hrengin

#endif//_hrengin_RIFF_