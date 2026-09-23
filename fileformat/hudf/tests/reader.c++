/*
 * Copyright (C) 2015  hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/hudf/parser.h>
#include <aw/hudf/utility.h>
#include <aw/io/input_file_stream.h>
#include <aw/log/log.h>

#include <aw/test/test.h>

#include <string>
#include <vector>

TestFile("hudf::reader");

namespace aw::hudf {
namespace {
//! Keeps everything the parser reports, so that a test can check it
struct recording_log : aw::log {
	std::vector<std::string> messages;

	void message(level, string_view, string_view msg) override
	{
		messages.emplace_back(msg);
	}
};

struct sample {
	bool has_error;
	std::vector<std::string> messages;
	aw::document doc;
};

/*!
 * Parse one of the documents in data/, which the build copies next to
 * the test and ctest runs the test from. A file that is not there throws,
 * and fails the test with its name.
 */
sample read_sample(std::string const& name)
{
	io::input_file_stream stream{"data/" + name};
	recording_log log;
	hudf::parser parser(stream, &log);
	aw::document doc( parse_node(parser) );

	return { parser.has_error(), std::move(log.messages), std::move(doc) };
}
} // namespace

Test(reads_typed_values) {
	auto s = read_sample("settings.hdf");

	Checks {
		TestAssert(!s.has_error);
		TestAssert(s.messages.empty());

		TestEqual(s.doc.get<intmax_t>("settings/graphics/resolutionX", 0), intmax_t(1066));
		TestEqual(s.doc.get<intmax_t>("settings/graphics/resolutionY", 0), intmax_t(600));
		TestEqual(s.doc.get<bool>("settings/graphics/fullscreen", true), false);
	}
}

Test(reads_bare_words_and_spaced_types) {
	auto s = read_sample("sphere5.hdf");

	// `type = sphere` is a bare word, `float : 5.0` has spaces around the ':'
	Checks {
		TestAssert(!s.has_error);
		TestAssert(s.messages.empty());

		TestEqual(s.doc.get<std::string>("model/shapes/shape/type", ""), std::string("sphere"));
		TestEqual(s.doc.get<double>("model/shapes/shape/radius", 0.0), 5.0);
	}
}

Test(reads_nested_nodes) {
	auto s = read_sample("sotank.hdf");

	Checks {
		TestAssert(!s.has_error);
		TestAssert(s.messages.empty());

		auto* shape = s.doc.node("model/shapes/shape");
		TestAssert(shape != nullptr);
		if (!shape)
			return;

		TestEqual(shape->children.size(), size_t(4));
		TestEqual(shape->try_get<std::string>("type", ""), std::string("capsule"));
		TestEqual(shape->try_get<std::string>("direction", ""), std::string("axisZ"));
		TestEqual(shape->try_get<double>("height", 0.0), 8.111);
		TestEqual(shape->try_get<double>("radius", 0.0), 1.997);
	}
}

Test(reads_node_values_and_vectors) {
	auto s = read_sample("test.hdf");

	// a node can carry a value of its own, and share its name with a child
	Checks {
		TestAssert(!s.has_error);
		TestAssert(s.messages.empty());

		TestEqual(s.doc.get<std::string>("test", ""), std::string("val1"));
		TestEqual(s.doc.get<std::string>("test/tit", ""), std::string("tat"));
		TestEqual(s.doc.get<intmax_t>("test/val", 0), intmax_t(1));
		TestEqual(s.doc.get<intmax_t>("test/test/val", 0), intmax_t(2));

		// the trailing comma in {1,1,2,} does not add an element
		auto bob = s.doc.get<std::vector<intmax_t>>("test/test/bob", {});
		TestEqual(bob.size(), size_t(3));
		TestAssert(bob == std::vector<intmax_t>{1, 1, 2});
	}
}

Test(reads_repeated_sibling_nodes) {
	auto s = read_sample("messages.hdf");

	// three nodes with the same name are kept apart, and in order
	Checks {
		TestAssert(!s.has_error);
		TestAssert(s.messages.empty());

		std::vector<std::string> texts;
		node const* last = nullptr;
		for (auto const& msg : s.doc) {
			texts.push_back(msg.try_get<std::string>("text", ""));
			last = &msg;
		}

		TestEqual(texts.size(), size_t(3));
		TestAssert(texts == std::vector<std::string>{
			"Starting the endine", "Success!", "Reading config..."});

		// its children are in a different order from the other two
		auto* color = last ? last->find_child("color") : nullptr;
		TestAssert(color != nullptr);
		if (color)
			TestEqual(color->try_get<intmax_t>("blue", 0), intmax_t(240));
	}
}

/*!
 * A malformed document is reported through the log, and whatever could
 * be made of it is still returned rather than thrown away
 */
Test(reports_malformed_document) {
	auto s = read_sample("invalid.hdf");

	Checks {
		TestAssert(s.has_error);
		TestAssert(!s.messages.empty());
		TestAssert(s.doc.node("closed_twice") != nullptr);
	}
}
} // namespace aw::hudf
