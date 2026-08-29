#include <aw/meta/detect.h>

#include <utility>

namespace aw {
namespace {
struct archive {};

//! Has a member load(), and no free one
struct with_member {
	void load(archive&) {}
};

//! Has a free load(), and no member
struct with_free {};
void load(archive&, with_free&) {}

template<class T, class A>
using member_load = decltype(std::declval<T&>().load(std::declval<A&>()));

template<class T, class A>
using free_load = decltype(load(std::declval<A&>(), std::declval<T&>()));
} // namespace

static_assert(  is_detected<member_load, with_member, archive> );
static_assert( !is_detected<free_load,   with_member, archive> );

static_assert( !is_detected<member_load, with_free, archive> );
static_assert(  is_detected<free_load,   with_free, archive> );

// a type with neither is detected as neither
static_assert( !is_detected<member_load, archive, archive> );
static_assert( !is_detected<free_load,   archive, archive> );
} // namespace aw
