/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_attribute_
#define _awrts_attribute_
#include <unordered_map>
#include <memory>

namespace awrts {
class Attribute {
public:
	size_t getAttributeTypeCount()
	{
		return typesCount;
	}

protected:
	// TODO: put Attribute::typesCount in a .cpp file
	static size_t typesCount;
};

template <typename Derived>
class AttributeId : public Attribute {
public:
	static size_t getId()
	{
		static size_t id = typesCount++;
		return id;
	}
};

class Health : public AttributeId<Health> {
public:
	float current;
	float max;
};

class AttributeContainer {
public:
	template <typename T>
	void add(std::unique_ptr<T> attribute)
	{
		// TODO: == empty
		attributes[T::getId()] = std::move(attribute);
	}

	template <typename T>
	T& get()
	{
		// TODO: != empty
		Attribute* attr = attributes[T::getId()].get();
		return *static_cast<T*>(attr);
	}
private:
	std::unordered_map<size_t, std::unique_ptr<Attribute>> attributes;
};

} // namespace awrts
#endif//_awrts_attribute_
