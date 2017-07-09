/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_resource_manager_h
#define aw_graphics_gl3_resource_manager_h
#include <vector>
#include <aw/graphics/gl/array_chain.h>
#include <aw/graphics/gl/program.h>
#include <aw/types/string_view.h>
namespace aw {
namespace gl3 {
template<typename Resource>
struct resource_ref {
	resource_ref() = default;

	resource_ref(Resource& res, int& ref_ctr)
		: res{&res}, ref_ctr{&ref_ctr}
	{
		add_ref();
	}

	resource_ref(resource_ref const& other)
		: resource_ref{*other.res, *other.ref_ctr}
	{
	}

	~resource_ref() { release(); }

	resource_ref& operator=(resource_ref const& other)
	{
		release();
		res     = other.res;
		ref_ctr = other.ref_ctr;
		add_ref();
	}

	operator Resource&    () { return *res; }
	         Resource& get() { return *res; }

	operator Resource const&    () const { return *res; }
	         Resource const& get() const { return *res; }

	         Resource* ptr() { return res; }
	
	bool is_valid() const
	{
		return res != nullptr;
	}

	operator bool()
	{
		return is_valid();
	}

private:
	void add_ref()
	{
		++*ref_ctr;
	}

	void release()
	{
		if (res == nullptr)
			return;

		// Just decrease the reference count
		// No automatic resource deallocation - this is by design
		--*ref_ctr;
	}

	Resource* res     = nullptr;
	int*      ref_ctr = nullptr;
};


template<typename Resource>
struct resource_manager {
	using reference = resource_ref<Resource>;

	resource_manager() = default;
	resource_manager(resource_manager const&) = delete;
	resource_manager(resource_manager&&)      = delete;

	// get count of allocated resource slots
	size_t size() const
	{
		return aux_list.size();
	}

	// get count of currently used resources
	size_t count() const
	{
		return size() - free_list.size();
	}

	reference operator[]( size_t idx )
	{
		auto& ctr = aux_list[idx].ref_ctr;
		if (ctr < 0)
			return {};

		auto& res = res_list.get(idx).get_ref();
		return { res, ctr };
	}

	size_t add_resource( string_view name, Resource&& resource )
	{
		if ( free_list.empty() ) {
			size_t idx = size();
			aux_list.emplace_back( aux_data{std::string{name}, 0} );

			res_list.grow(idx + 1);
			res_list.construct(idx, std::move(resource) );
			return idx;
		}

		auto idx = free_list.back(); free_list.pop_back();
		aux_list[idx].name.assign( name );
		aux_list[idx].ref_ctr = 0;
		res_list.construct(idx, std::move(resource));

		return idx;
	}

	bool is_available( size_t idx )
	{
		return ref_ctr(idx) > 0;
	}

	void release( size_t idx )
	{
		if ( ref_ctr(idx) == 0 )
			destroy(idx);
	}

	void release_all( )
	{
		for (size_t i = 0; i < aux_list.size(); ++i)
			release(i);
	}

	size_t find_by_name( string_view name )
	{
		auto begin = aux_list.begin();
		auto end = aux_list.end();
		auto has_name = [=] (aux_data const& data) {
			return data.name == name;
		};
		auto pos = std::find_if( begin, end, has_name );
		if (pos == end) return -1;
		return pos - begin;
	}

protected:
	struct aux_data {
		std::string name;
		int ref_ctr;
	};

	void ref_ctr( size_t idx )
	{
		return aux_list[idx].ref_ctr;
	}

	void destroy( size_t idx )
	{
		free_list.push_back( idx );
		res_list[idx].destruct( idx );
		--aux_list[idx].ref_ctr;
	}

private:
	chain_storage<Resource> res_list;
	array_chain<aux_data>   aux_list;
	std::vector<size_t>     free_list;
};


// note: names are deliberately different from those used in containers,
// because this is a different kind of beast

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_manager_h
