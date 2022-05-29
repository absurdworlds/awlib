/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_canvas_
#define _aw_GUI_canvas_
#include <memory>

#include <aw/gui/Element.h>
namespace aw {
namespace gui {
class Canvas : public Element {
public:
	typedef std::vector<std::unique_ptr<Element>> elements_t;

	Canvas() = default;
	virtual ~Canvas() = default;
 
	/*!
	 * Add a child element
	 */
	virtual void addElement(std::unique_ptr<Element> e);

	/*!
	 * Remove child. Returns unique_ptr to detached child,
	 * allowing to rebind it to different object.
	 */
	virtual std::unique_ptr<Element> removeElement(Element* e);
 
	/*!
	 * Get currently active element (which is
	 * currently being interacted with).
	 */
	virtual Element* getActiveElement();

	void bringToFront(Element* e);
	void sendToBack(Element* e);
	virtual bool onEvent(Event* event);
	virtual void accept(Visitor& visitor);

	virtual Canvas* toCanvas()
	{
		return this;
	}

	virtual Widget* toWidget()
	{
		return nullptr;
	}

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
			--base;
			return *this;
		}

		bool operator == (iterator const& other)
		{
			return base == other.base;
		}

		bool operator != (iterator const& other)
		{
			return base != other.base;
		}

		bool operator == (base_t const& other)
		{
			return base == other;
		}

		bool operator != (base_t const& other)
		{
			return base != other;
		}
	private:
		friend class Canvas;
		base_t base;
	};

	typedef std::reverse_iterator<iterator> reverse_iterator;

	virtual iterator getFirstChild() const
	{
		return iterator(std::begin(elements));
	}
	virtual iterator getLastChild() const
	{
		return iterator(std::end(elements));
	}

	virtual reverse_iterator rbegin() const
	{
		return reverse_iterator(std::rbegin(elements));
	}
	virtual reverse_iterator rend() const
	{
		return reverse_iterator(std::rend(elements));
	}

	iterator findElement(Element* e) const;

	virtual void invalidate()
	{
		Element::invalidate();
	}
protected:
	void makeActive(Element* element) {
		// TODO: assert(isChild(element));
		active = element;
	}
	Element* getElementFromPoint(Vector2d<i32> point, Vector2d<i32> bounds);

private:
	elements_t::iterator findElement(Element* e);
	bool processEvent(MouseEvent* event);
	bool processEvent(GUIEvent* event);

	elements_t elements;
	Element* active;
	Element* hovered;
};

inline Canvas::iterator begin(Canvas* canvas)
{
	return canvas->getFirstChild();
}

inline Canvas::iterator end(Canvas* canvas)
{
	return canvas->getLastChild();
}

inline auto rbegin(Canvas& canvas)
{
	return Canvas::reverse_iterator(canvas.getLastChild());
}

inline auto rend(Canvas& canvas)
{
	return Canvas::reverse_iterator(canvas.getFirstChild());
}
} // namespace gui
} // namespace aw
#endif //_aw_GUI_canvas_
