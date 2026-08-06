#include <vector>
#include <aw/archive/archive_base.h>
#include <aw/utility/ranges/char_view.h>
namespace aw {
namespace arc {

struct testarc : input_archive<testarc>, output_archive<testarc> {
	using input_archive<testarc>::operator();
	using output_archive<testarc>::operator();

	template<typename T>
	static constexpr bool is_directly_serializable {
		is_arithmetic<T> || is_string<T>
	};

	template<typename T>
	void save(T const& value, opt_string name = nullopt)
	{
		if constexpr(is_string<T>) {
			save(value.size());
			for (char c : value) {
				data.push_back(c);
			}
		} else {
			for (char c : char_view_iterator{value})
				data.push_back(c);
		}
	}

	template<typename T>
	void load(T& value, opt_string name = nullopt)
	{
		if constexpr(is_string<T>) {
			value.clear();
			size_t size; load(size);
			while (size --> 0) {
				value.push_back(data[iter++]);
			}
		} else {
			for (char& c : char_edit_iterator{value})
				c = data[iter++];
		}
	}

	void clear()
	{
		data.clear();
		iter = 0;
	}

	std::vector<char> data;
	size_t iter = 0;
};

template<>
void start_save_virtual(testarc& arc, string_view type, opt_string name)
{
	arc.save(type);
}

template<>
std::string start_load_virtual(testarc& arc, opt_string name)
{
	return std::string{ arc };
}

aw_register_archive( testarc );


} // namespace arc
} // namespace aw
