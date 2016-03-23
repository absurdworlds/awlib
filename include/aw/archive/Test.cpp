#include <iostream>
#include <aw/archive/ClassDef.h>
#include <aw/archive/InputArchive.h>
#include <aw/archive/OutputArchive.h>

namespace aw {
namespace arc {
template <typename T, EnableIf<is_float<T>> = dummy>
constexpr auto typeName(T const&) -> char const* {
	return "float";
};

template <typename T, EnableIf<is_bool<T>> = dummy>
constexpr auto typeName(T const&) -> char const* {
	return "bool";
};

template <typename T, EnableIf<is_string<T>> = dummy>
constexpr auto typeName(T const&) -> char const* {
	return "string";
};

template <typename T, EnableIf<is_int<T>> = dummy>
constexpr auto typeName(T const&) -> char const* {
	return "int";
};


class Couter : public OutputArchive {
	virtual void object_start(char const* name)
	{
		printIndent();
		std::cout << "[" << name << "\n";
		addIndent();
	}

	virtual void object_start(char const* name, char const* type)
	{
		printIndent();
		std::cout << "[" << name << " : " << type << "\n";
		addIndent();
	}

	virtual void object_end(char const* name)
	{
		removeIndent();
		printIndent();
		std::cout << "]" << "\n";
	}

	virtual void list_start(char const* name)
	{
		printIndent();
		std::cout << "[" << name << "\n";
		addIndent();
	}

	virtual void list_end(char const* name)
	{
		removeIndent();
		printIndent();
		std::cout << "]" << "\n";
	}

	virtual void value_start(char const* name)
	{
		printIndent();
		std::cout << name << " = ";
	}

	virtual void value_end(char const* name) { }

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

std::istream & operator >> (std::istream & stream, const skip & x)
{
	using namespace std::literals::string_literals;
	std::ios_base::fmtflags f = stream.flags();
	//stream >> std::noskipws;

	char c;
	auto text = x.text.begin();
	while (stream && *text) {
		stream >> c;
		std::cerr << c << "|";
		std::cerr << *text;
		if (c != *text) std::cerr << "fuck";
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

class Cinner : public InputArchive {
	virtual void object_start(char const* name)
	{
		std::cin >> skip("[") >> skip(name);
	}

	virtual void object_end(char const* name)
	{
		std::cin >> skip("]");
	}

	virtual void list_start(char const* name)
	{
		std::cin >> skip("[") >> skip(name);
	}

	virtual void list_end(char const* name)
	{
		std::cin >> skip("]");
	}

	virtual bool list_atend()
	{
		return false;
	}

	virtual char const* polymorphic_type()
	{
		static std::string type;
		std::cin >> skip(":");
		std::cin >> type;
		return type.c_str();
	}

	virtual void value_start(char const* name)
	{
		std::cin >> skip(name);
	}

	virtual void value_end(char const* name) {}

	virtual void read(char& value)
	{
		int val;
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> val;
		value = val;
	}

	virtual void read(std::string& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}

	virtual void read(i8 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}
	virtual void read(u8 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}

	virtual void read(i16 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}
	virtual void read(u16 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}

	virtual void read(i32 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}
	virtual void read(u32 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}

	virtual void read(i64 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}
	virtual void read(u64 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}

	virtual void read(f32 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}
	virtual void read(f64 const& value)
	{
		std::cin >> skip("=") >> skip(typeName(value)) >> skip(":") >> value;
	}
};

struct Base {
	using ClassDef = aw::ClassDef<Base, Base*(char)>;

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
Base::ClassDef Base::classdef = Base::ClassDef::base("Base", nullptr);

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

Derived::ClassDef Derived::classdef = Derived::ClassDef::derived<Base>(
	"Derived",
	[] (char c) -> Base* {
		return new Derived(c);
	}
);

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

Derived2::ClassDef Derived2::classdef = Derived2::ClassDef::derived<Base>(
	"Derived2",
	[] (char c) -> Base* {
		return new Derived2(c);
	}
);
} // namespace arc
} // namespace aw

int main()
{
	using namespace aw::arc;

	Couter arc;
	Cinner arc2;

	Base* test  = 0;
	Base* test2 = 0;

	arc2("test",  test,  std::make_tuple(111));
	arc2("test2", test2, std::make_tuple(99));

	arc("test",  test);
	arc("test2", test2);
}
