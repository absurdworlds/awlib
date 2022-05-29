#include <aw/fileformat/wav/reader.h>
#include <aw/io/input_file_stream.h>
#include <aw/test/test.h>

TestFile("WAV");

namespace aw {
Test(read) {
	io::input_file_stream file("glass.wav");

	wav::wave_data data;

	Checks {
		TestAssert(wav::read(file, data));
	}

	Postconditions {
		TestEqual(data.channels, 2);
	}
};
} // namespace aw

#include <aw/test/test_runner.h>
