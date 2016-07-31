#include <iostream>
#include <aw/types/composite_int.h>

static inline unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

namespace aw {
using s_u64 = aw::composite_int<aw::u32>;
using s_i64 = aw::composite_int<aw::i32>;

static const u64 val1 = 0x0000'0002'0000'1000;
static const u64 val2 = 0x0000'0000'0100'2000;

static const i64 val3 = -0x0000'0002'0000'1000;
static const i64 val4 = 0x0000'0000'0100'2000;

static const s_u64 comp1 {0x0000'0002, 0x0000'1000};
static const s_u64 comp2 {0x0000'0000, 0x0100'2000};

static const i32 hi3 = val3 >> 32;
static const u32 lo3 = u32(val3);
static const i32 hi4 = val4 >> 32;
static const u32 lo4 = u32(val4);

static const s_i64 comp3 {hi3, lo3};
static const s_i64 comp4 {hi4, lo4};

u64 to_i(s_u64 const& v)
{
	return v.low_part() | (u64(v.high_part()) << 32);
}

i64 to_i(s_i64 const& v)
{
	return i64(v.low_part() | (u64(v.high_part()) << 32));
}

template<typename T>
std::ostream& operator<<(std::ostream& os, composite_int<T> const& v)
{
	os << as_string(v);
	return os;
}

void test_uadd()
{
	std::cout << "uadd\n";
	std::cout << "synt:" << comp1 + comp2 << "\n";
	std::cout << "hard:" << val1 + val2 << "\n";
}

void test_umul()
{
	std::cout << "umul\n";
	std::cout << "synt:" << comp1 * comp2 << "\n";
	std::cout << "hard:" << val1 * val2 << "\n";
}

void test_imul()
{
	std::cout << "imul\n";
	std::cout << "synt:" << comp3 * comp4 << "\n";
	std::cout << "hard:" << val3 * val4 << "\n";
}


void test_udiv()
{
	std::cout << "udiv\n";
	std::cout << "synt:" << comp1 / comp2 << "\n";
	std::cout << "hard:" << val1 / val2 << "\n";
}



void test_idiv()
{
	std::cout << "idiv\n";
	std::cout << "synt:" << comp3 / comp4 << "\n";
	std::cout << "hard:" << val3 / val4 << "\n";
}

void test_uneg()
{
	std::cout << "uneg\n";
	std::cout << "synt:" << -comp1 << "\n";
	std::cout << "hard:" << -i64(val1) << "\n";
}

void test_construct()
{
	std::cout << aw::composite_int<signed>(-3333) << "\n";
	std::cout << aw::composite_int<unsigned>(7777u) << "\n";
}

} // namespace aw

int main()
{
	using namespace aw;
	test_construct();
	test_uadd();
	test_umul();
	test_imul();
	test_udiv();
	test_idiv();
	test_uneg();
}
