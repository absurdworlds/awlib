#include <aw/types/support/reinterpret.h>
#include <aw/types/types.h>
#include <aw/test/test.h>
#include <algorithm>

TestFile( "aw::reinterpret" );

namespace aw {
namespace {
struct half {
	u32 a;
};

struct block {
	u32 a;
	u32 b;
};

struct wide {
	u64 lo;
	u64 hi;
};

constexpr u8 fill = 0xAA;
} // namespace

//! reinterpret() converts a value into another type of the same size
Test(reinterpret_value) {
	Checks {
		// IEEE-754 single precision 1.0
		TestEqual( reinterpret<u32>(1.0f), 0x3f800000u );
		TestEqual( reinterpret<f32>(0x3f800000u), 1.0f );
	}

	Checks {
		f32 const values[] = { 0.0f, -1.0f, 3.5f, 1e-6f };
		for (f32 value : values)
			TestEqual( reinterpret<f32>( reinterpret<u32>(value) ), value );
	}
}

//! reinterpret_any() truncates the input, or zero-fills what it lacks
Test(reinterpret_any_resize) {
	Checks {
		block const in{ 0x11111111, 0x22222222 };
		TestEqual( reinterpret_any<half>(in).a, in.a );
	}

	Checks {
		auto const out = reinterpret_any<block>( half{0x33333333} );
		TestEqual( out.a, 0x33333333u );
		TestEqual( out.b, 0u );
	}
}

/*
 * copy_to_memory()/copy_from_memory() must move the object itself, and not
 * a pointer to it: deducing the wrong T silently substitutes sizeof(void*)
 * for the size of the object.
 */
Test(copy_memory_roundtrip) {
	u8 buffer[32] = {};

	Checks {
		u32 const in = 0x12345678;
		u32 out = 0;

		copy_to_memory(in, buffer + 4);
		copy_from_memory(out, buffer + 4);

		TestEqual( out, in );
	}

	Checks {
		// an object larger than a pointer
		wide const in{ 0x0123456789abcdefull, 0xfedcba9876543210ull };
		wide out{};

		copy_to_memory(in, buffer + 16);
		copy_from_memory(out, buffer + 16);

		TestEqual( out.lo, in.lo );
		TestEqual( out.hi, in.hi );
	}

	Checks {
		// the returned reference names the output object
		u32 out = 0;
		TestAssert( &copy_from_memory(out, buffer + 4) == &out );
	}
}

//! ...and must touch nothing outside those sizeof(T) bytes
Test(copy_memory_bounds) {
	u8 buffer[8];
	std::fill( std::begin(buffer), std::end(buffer), fill );

	Checks {
		u8 const in = 0x5C;
		copy_to_memory(in, buffer + 4);

		TestEqual( buffer[3], fill );
		TestEqual( buffer[4], in );
		TestEqual( buffer[5], fill );
	}
}

/*
 * reinterpret_memory() reads sizeof(Output) bytes into the value it
 * returns — not sizeof(void*) bytes into a temporary pointer, which
 * leaves the result uninitialized and over-reads the source.
 */
Test(reinterpret_memory_size) {
	u8 buffer[32] = {};

	u8   const b = 0x5C;
	u16  const s = 0x1234;
	wide const w{ 0x0123456789abcdefull, 0xfedcba9876543210ull };

	copy_to_memory(b, buffer + 0);
	copy_to_memory(s, buffer + 2);
	copy_to_memory(w, buffer + 16);

	Checks {
		// smaller than a pointer
		TestEqual( reinterpret_memory<u8>(buffer + 0), b );
		TestEqual( reinterpret_memory<u16>(buffer + 2), s );
	}

	Checks {
		// larger than a pointer
		auto const out = reinterpret_memory<wide>(buffer + 16);
		TestEqual( out.lo, w.lo );
		TestEqual( out.hi, w.hi );
	}
}

//! Each read starts at the address it was handed
Test(reinterpret_memory_offset) {
	u8 buffer[16] = {};

	u32 const values[] = { 0xaaaa0000u, 0xbbbb1111u, 0xcccc2222u };

	copy_to_memory(values[0], buffer + 0);
	copy_to_memory(values[1], buffer + 4);
	copy_to_memory(values[2], buffer + 8);

	Checks {
		TestEqual( reinterpret_memory<u32>(buffer + 0), values[0] );
		TestEqual( reinterpret_memory<u32>(buffer + 4), values[1] );
		TestEqual( reinterpret_memory<u32>(buffer + 8), values[2] );
	}
}
} // namespace aw
