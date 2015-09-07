/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_container_
#define _awrts_GUI_container_
#include <memory>

namespace awrts {
namespace gui {
class Element;

class Container {
public:
	/*!
	 * Add a child element
	 */
	virtual void addElement(std::unique_ptr<Element> e);

	/*!
	 * Remove child. Returns unique_ptr to detached child,
	 * allowing to rebind it to different object.
	 */
	virtual std::unique_ptr<Element> removeElement(Element* e);

	typedef std::vector<std::unique_ptr<Element>> elements_t;

	class iterator :
		public std::iterator<std::random_access_iterator_tag, Element> {
	public:
		typedef elements_t::const_iterator base_t;

		iterator(base_t base)
			: base(base)
		{}

		reference operator*() const
		{
			return **base;
		}

		pointer operator->() const
		{
			return (*base).get();
		}

		iterator& operator++()
		{
			++base;
			return *this;
		}

		iterator& operator--()
		{
			++base;
			return *this;
		}

		bool operator==(iterator const& other)
		{
			return base == other.base;
		}

		bool operator!=(iterator const& other)
		{
			return base != other.base;
		}
	private:
		friend class Container;
		base_t base;
	};

	virtual iterator begin() const
	{
		return iterator(std::begin(elements));
	}
	virtual iterator end() const
	{
		return iterator(std::end(elements));
	}
protected:
	elements_t elements;
};
} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_container_
