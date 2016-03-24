/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_Archive_base
#define aw_Archive_base
#include <cassert>
#include <utility>
#include <aw/types/types.h>
#include <aw/types/traits/enable_if.h>
#include <aw/types/traits/detect.h>
#include <aw/types/traits/basic_traits.h>
namespace aw {
namespace arc {
namespace v1 {
template<class T, class A> using m_load     = decltype(std::declval<T>().load(std::declval<A&>()));
template<class T, class A> using m_save     = decltype(std::declval<T>().save(std::declval<A&>()));
template<class T, class A> using m_archive  = decltype(std::declval<T>().archive(std::declval<A&>()));
template<class T, class A> using nm_load    = decltype(load(std::declval<A&>(),std::declval<T&>()));
template<class T, class A> using nm_save    = decltype(save(std::declval<A&>(),std::declval<T&>()));
template<class T, class A> using nm_archive = decltype(archive(std::declval<A&>(),std::declval<T&>()));

template <typename Derived>
class OutputArchive {
	Derived& derived;
public:
	operator Derived&()
	{
		return derived;
	}

	operator Derived const&() const
	{
		return derived;
	}

	OutputArchive(Derived& derived)
		: derived(derived)
	{
	}

	template<typename T>
	void process(T& value, char const* name)
	{
		start(derived, name, value);
		call_archive(value);
		end(derived, name, value);
	}

	class Proxy {
	public:
		Proxy(OutputArchive& arc, char const* name)
			: arc(arc), name(name)
		{
		}

		template<typename T>
		void operator - (T& value)
		{
			arc.process(value, name);
		}
	private:
		OutputArchive& arc;
		char const* name;
	};

	Proxy operator - (char const* name)
	{
		return Proxy(*this, name);
	}

private:
	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<m_archive,T,Derived>>
	{
		value.archive(derived);
	}

	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<nm_archive,T,Derived>>
	{
		archive(derived, value);
	}

	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<m_save,T,Derived>>
	{
		value.save(derived);
	}

	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<nm_save,T,Derived>>
	{
		save(derived, value);
	}
};

template <typename Derived>
class InputArchive {
	Derived& derived;
public:
	operator Derived&()
	{
		return derived;
	}

	operator Derived const&() const
	{
		return derived;
	}

	InputArchive(Derived& derived)
		: derived(derived)
	{
	}

	template<typename T>
	void process(T& value, char const* name)
	{
		start(derived, name, value);
		call_archive(value);
		end(derived, name, value);
	}

	class Proxy {
	public:
		Proxy(InputArchive& arc, char const* name)
			: arc(arc), name(name)
		{
		}

		template<typename T>
		void operator - (T& value)
		{
			arc.process(value, name);
		}
	private:
		InputArchive& arc;
		char const* name;
	};

	Proxy operator - (char const* name)
	{
		return Proxy(*this, name);
	}

private:
	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<m_archive,T,Derived>>
	{
		value.archive(derived);
	}

	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<nm_archive,T,Derived>>
	{
		archive(derived, value);
	}

	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<m_load,T,Derived>>
	{
		value.load(derived);
	}

	template<typename T>
	auto call_archive(T& value) -> void_if<is_detected<nm_load,T,Derived>>
	{
		load(derived, value);
	}
};
} // namespace v1
} // namespace arc
} // namespace aw
#endif//aw_Archive_base
