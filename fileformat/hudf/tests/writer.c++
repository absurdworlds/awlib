#include <aw/hudf/writer.h>

#include <aw/test/test.h>

#include <sstream>

TestFile("hudf::writer")

namespace aw {
Test(hudf_write_node)
{
	std::stringstream stream;
	hudf::writer writer {stream};
	writer.set_indentation_style(aw::hudf::indentation_style::none);
	writer.set_line_break_style(false);

	using namespace std::string_literals;
	writer.start_node("shape"s);
	writer.write_value("type"s, hudf::value("sphere"s));
	// TODO: fix double representation
	writer.write_value("radius"s, hudf::value(1));
	writer.end_node();

	TestEqual(stream.str(), "[shape type=string:\"sphere\" radius=int:1]");
}
} // namespace aw
