#include <iostream>
#include <aw/archive/v1/Archive.h>
namespace aw {
namespace arc {
namespace v1 {
template<typename T>
constexpr auto is_primitive = is_arithmetic<T> || is_string<T>;

template <typename T>
constexpr auto typeName(T) -> enable_if<is_float<T>, char const*> {
	return "float";
};

template <typename T>
constexpr auto typeName(T) -> enable_if<is_bool<T>, char const*> {
	return "bool";
};

template <typename T>
constexpr auto typeName(T) -> enable_if<is_string<T>, char const*> {
	return "string";
};

template <typename T>
constexpr auto typeName(T) -> enable_if<is_int<T>, char const*> {
	return "int";
};

struct Couter : OutputArchive<Couter> {
	size_t indent = 0;

	Couter()
		: OutputArchive<Couter>(*this)
	{
		std::cout << std::boolalpha;
	}

	void printIndent() const
	{
		if (indent > 0)
			std::cout << std::string(4*indent, ' ');
	}

	void addIndent()
	{
		++indent;
	}

	void removeIndent()
	{
		if (indent > 0)
			--indent;
	}

	template<typename T>
	friend auto start(Couter& arc, char const* name, T& value) -> void_if<!is_primitive<T>>
	{
		arc.printIndent();
		std::cout << "[" << name << std::endl;
		arc.addIndent();
	}

	template<typename T>
	friend auto end(Couter& arc, char const* name, T& value) -> void_if<!is_primitive<T>>
	{
		arc.removeIndent();
		arc.printIndent();
		std::cout << "]" << std::endl;
	}

	template<typename T>
	friend auto start(Couter& arc, char const* name, T& value) -> void_if<is_primitive<T>>
	{
		arc.printIndent();
		std::cout << name << " = " << typeName(value) << ": ";
	}

	template<typename T>
	friend auto end(Couter& arc, char const* name, T& value) -> void_if<is_primitive<T>>
	{
	}

};

template<typename T>
auto archive(Couter& arc, T& x) -> void_if<is_primitive<T> && !is_string<T>>
{
	std::cout << x << std::endl;
}

template<typename T>
auto archive(Couter& arc, T& x) -> void_if<is_string<T>>
{
	std::cout << '"' << x << '"' << std::endl;
}

struct skip {
	std::string text;
	skip(const char * text) : text(text) {}
	skip(const char ch) : text(1,ch) {}
	skip(std::string text) : text(text) {}
};

std::istream & operator >> (std::istream & stream, const skip & x)
{
	using namespace std::literals::string_literals;
	std::ios_base::fmtflags f = stream.flags();
	//stream >> std::noskipws;

	char c;
	auto text = x.text.begin();
	while (stream && *text) {
		stream >> c;
		if (c != *text)
			std::cerr << ""s + "'" + *text + "'" + " / '" + c + "'\n";
		++text;
	}

	stream.flags(f);
	return stream;
}


struct Cinner : InputArchive<Cinner> {
	size_t indent = 0;

	Cinner()
		: InputArchive<Cinner>(*this)
	{
		//std::cin >> std::boolalpha;
	}

	template<typename T>
	friend auto start(Cinner& arc, char const* name, T& value) -> void_if<!is_primitive<T>>
	{
		std::cin >> skip("[") >> skip(name);
	}

	template<typename T>
	friend auto end(Cinner& arc, char const* name, T& value) -> void_if<!is_primitive<T>>
	{
		std::cin >> skip("]");
	}

	template<typename T>
	friend auto start(Cinner& arc, char const* name, T& value) -> void_if<is_primitive<T>>
	{
		std::cin >> skip(name) >> skip("=") >> skip(typeName(value)) >> skip(":");
	}

	template<typename T>
	friend auto end(Cinner& arc, char const* name, T& value) -> void_if<is_primitive<T>>
	{
	}

};

template<typename T>
auto archive(Cinner& arc, T& x) -> void_if<is_primitive<T> && !is_string<T>>
{
	std::cin >> x;
}

template<typename T>
auto archive(Cinner& arc, T& x) -> void_if<is_string<T>>
{
	std::cin >> skip('"') >> x >> skip('"');
}
} // namespace v1
} // namespace arc
} // namespace aw

#include <aw/math/Vector3d.h>
namespace aw {
namespace arc {
namespace v1 {
template<typename Archive, typename T>
void archive(Archive& arc, Vector3d<T>& value)
{
	arc - "x" - value[0];
	arc - "y" - value[1];
	arc - "z" - value[2];
}
} // namespace v1
} // namespace arc
} // namespace aw

struct A {
	A(int a1) : val1{a1} {}
	template<typename Archive>
	void archive(Archive& arc)
	{
		arc - "val1" - val1;
	}

	int val1;
};

struct B : A {
	B(int a1, unsigned a2) : A{a1}, val2{a2} {}
	template<typename Archive>
	void archive(Archive& arc)
	{
		A::archive(arc);
		arc - "val2" - val2;
	}

	unsigned val2;
};

struct C : B {
	C(int a1, unsigned a2, float a3) : B{a1, a2}, val3{a3} {}
	template<typename Archive>
	void archive(Archive& arc)
	{
		arc - "base" - static_cast<B&>(*this);
		arc - "val2" - val3;
	}

	float val3;
};

#define _(T) #T - T
int main()
{
	using namespace aw;
	using namespace aw::arc::v1;
	Couter arc;
	// Cinner arc
	
	A a{1};
	B b{2,20};
	C c{3,123,46.3};

	(arc)- "class" -(a);
	(arc)- "cliss" -(b);
	(arc)- "clazz" -(c);

	double t1 = 21;
	float  t2 = 21.0;
	int    t3 = 21;

	arc-_(t1);
	arc-_(t2);
	arc-_(t3);
	
	std::string str = "Argh, go away, world!";

	(arc - "value") - (str);

	Vector3d<f32> v3{1.0, 2.0, 3.0};
	arc.process(v3, "vec");
	// (arc - "vec") - v3;
}
