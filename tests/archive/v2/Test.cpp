#include <iostream>
#include <aw/archive/ClassDef.h>
#include <aw/archive/OutputArchive.h>
#include <aw/archive/InputArchive.h>

namespace aw {
namespace arc {
template <typename T>
constexpr auto typeName(T const&) -> enable_if<is_float<T>, char const*> {
	return "float";
};

template <typename T>
constexpr auto typeName(T const&) -> enable_if<is_bool<T>, char const*> {
	return "bool";
};

template <typename T>
constexpr auto typeName(T const&) -> enable_if<is_string<T>, char const*> {
	return "string";
};

template <typename T>
constexpr auto typeName(T const&) -> enable_if<is_int<T>, char const*> {
	return "int";
};


class Couter : public OutputArchive {
	virtual void start(ObjectKind kind, char const* name)
	{
		printIndent();
		if (kind == ObjectKind::Basic) {
			std::cout << name << " = ";
			return;
		}
		std::cout << "[" << name << "\n";
		addIndent();
	}

	virtual void start(ObjectKind kind, char const* name, char const* type)
	{
		printIndent();
		std::cout << "[" << name << " : " << type << "\n";
		addIndent();
	}

	virtual void end(ObjectKind kind, char const* name)
	{
		if (kind == ObjectKind::Basic)
			return;
		removeIndent();
		printIndent();
		std::cout << "]" << "\n";
	}

	virtual void write(char const& value)
	{
		std::cout << typeName(value) << " : " << int{value} << "\n";
	}

	virtual void write(std::string const& value) 
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}

	virtual void write(i8 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}
	virtual void write(u8 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}

	virtual void write(i16 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}
	virtual void write(u16 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}

	virtual void write(i32 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}
	virtual void write(u32 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}

	virtual void write(i64 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}
	virtual void write(u64 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}

	virtual void write(f32 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
	}
	virtual void write(f64 const& value)
	{
		std::cout << typeName(value) << " : " << value << "\n";
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
	
	unsigned indent = 0;
};

struct skip {
	std::string text;
	skip(const char * text) : text(text) {}
	skip(const char ch) : text(1,ch) {}
	skip(std::string text) : text(text) {}
};

bool atend = false;
std::istream & operator >> (std::istream & stream, const skip & x)
{
	using namespace std::literals::string_literals;
	std::ios_base::fmtflags f = stream.flags();
	//stream >> std::noskipws;

	char c;
	auto text = x.text.begin();
	while (stream && *text) {
		stream >> c;
		if (c == ']') atend = true;
		std::cerr << *text << "|" << c;
		if (c != *text) std::cerr << " !fuck";
		/*
			std::string x = ""s + "'" + *text + "'" + " / '" + c + "'";
			std::cerr << "fuck: " << x << std::endl;
		}*/
		std::cerr << "\n";
		++text;
	}

	stream.flags(f);
	return stream;
}

using namespace std::literals::string_literals;

class Cinner : public InputArchive {

	virtual void start(ObjectKind kind, char const* name)
	{
		if (kind == ObjectKind::Basic) {
			std::cin >> skip(name);
			return;
		}
		if (kind == ObjectKind::List)
			atend = false;
		std::cin >> skip("[") >> skip(name);
	}

	virtual void end(ObjectKind kind, char const* name)
	{
		if (kind == ObjectKind::Basic)
			return;
		std::cin >> skip("]");
	}

	virtual bool at_end()
	{
		char c = std::cin.peek();
		if (std::isspace(c))
			std::cin.get(c);

		if (std::cin.peek() == ']')
			return true;
		return atend;
	}

	virtual char const* read_type()
	{
		static std::string type;
		std::cin >> skip(":");
		std::cin >> type;
		return type.c_str();
	}

	virtual void read(char& value)
	{
		int val;
		std::cin >> skip("="s + typeName(value) + ":");
		std::cin >> val;
		value = val;
	}

	virtual void read(std::string& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}

	virtual void read(i8& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}
	virtual void read(u8& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}

	virtual void read(i16& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}
	virtual void read(u16& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}

	virtual void read(i32& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}
	virtual void read(u32& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}

	virtual void read(i64& value)
	{
		i64 val;
		std::cin >> skip("="s + typeName(value) + ":");
		std::cin >> val;
		value = val;
	}
	virtual void read(u64& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}

	virtual void read(f32& value)
	{
		std::cin >> skip("="s + typeName(value) + ":") >> value;
	}
	virtual void read(f64& value)
	{
		f64 val;
		std::cin >> skip("="s + typeName(value) + ":");
		std::cin >> val;
		value = val;
	}
};

struct Base {
	using ClassDef = aw::arc::ClassDef<Base*(char)>;

	static ClassDef classdef;
	virtual ClassDef& classDef() const
	{
		return classdef;
	}

	Base(char var1)
		: var1(var1)
	{}

	virtual void save(OutputArchive& arc) const
	{
		arc("var1", var1);
	}

	virtual void load(InputArchive& arc) = 0;

	char var1;
};
Base::ClassDef Base::classdef = Base::ClassDef::create<Base>("Base");

void Base::load(InputArchive& arc)
{
	char x;
	arc("var1", x);
}

struct Derived : Base {
	using ClassDef = Base::ClassDef;

	static ClassDef classdef;
	virtual ClassDef& classDef() const
	{
		return classdef;
	}

	Derived(char var1)
		: Base(var1)
	{
	}

	virtual void save(OutputArchive& arc) const
	{
		Base::save(arc);
		arc("var2", var2);
	}

	virtual void load(InputArchive& arc)
	{
		Base::load(arc);
		arc("var2", var2);
	}
	
	char var2;
};

Base::ClassDef Derived::classdef = Base::ClassDef::create<Derived>("Derived");

struct Derived2 : Base {
	using ClassDef = Base::ClassDef;

	static ClassDef classdef;
	virtual ClassDef& classDef() const
	{
		return classdef;
	}

	Derived2(char var1)
		: Base(var1)
	{
	}

	virtual void save(OutputArchive& arc) const
	{
		Base::save(arc);
		arc("var2", var2);
	}

	virtual void load(InputArchive& arc)
	{
		Base::load(arc);
		arc("var2", var2);
	}
	
	char var2;
};

Base::ClassDef Derived2::classdef = Base::ClassDef::create<Derived2>("Derived2");
} // namespace arc
} // namespace aw

#include <aw/archive/types/std_vector.h>
#include <aw/archive/types/std_map.h>
#include <aw/archive/types/math_Vector4d.h>
int main()
{
	using namespace aw;
	using namespace aw::arc;

	Couter arc;
	Cinner arc2;

	Base* test  = new Derived(100);
	Base* test2 = 0;

	std::vector<i64> vec1{1,2,3,4,5};
	std::vector<f64> vec2{1,2,3,4,5};

	std::map<int,int> map;
	map[1] = 10;
	map[2] = 100;
	map[3] = 1000;
	map[4] = 10000;

	//std::cout << IsContainer<decltype(map)> << std::endl;

	arc("map", map);

	arc("vec", vec1);
	arc("vec", vec2);

	Vector4d<f32> v4{0.0, 1.0, 2.0, 1.0};
	arc("v3", v4);

	arc("test", test);
/*
	arc2("test",  test,  std::make_tuple(111));
	arc2("test2", test2, std::make_tuple(99));

	arc("test",  test);
	arc("test2", test2);

	arc2("vec", vec1);
	arc2("vec", vec2);
	
	arc("vec", vec1);
	arc("vec", vec2);*/
}
