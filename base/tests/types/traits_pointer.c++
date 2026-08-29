#include <aw/types/traits/pointer_traits.h>
#include <cstdio>
#include <memory>

namespace aw {
namespace {
struct file_deleter {
	void operator()(std::FILE* f) const { std::fclose(f); }
};
} // namespace

static_assert(is_smart_pointer<std::shared_ptr<int>>);
static_assert(is_smart_pointer<std::weak_ptr<int>>);
static_assert(is_smart_pointer<std::unique_ptr<int>>);
// a deleter of its own does not make it any less of a smart pointer
static_assert(is_smart_pointer<std::unique_ptr<std::FILE, file_deleter>>);

static_assert(!is_smart_pointer<int*>);
static_assert(!is_smart_pointer<int>);

static_assert(is_pointer_type<int*>);
static_assert(is_pointer_type<std::unique_ptr<std::FILE, file_deleter>>);
static_assert(!is_pointer_type<int>);
} // namespace aw
