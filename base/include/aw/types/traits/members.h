#ifndef aw_types_traits_members_h
#define aw_types_traits_members_h

namespace aw {

template<typename Class, typename Type>
using member_ptr = Type Class::*;

template<typename T>
struct class_of;
template<typename Class, typename Type>
struct class_of<member_ptr<Class, Type>> {
	using type = Class;
};
template<typename T>
using class_of_t = typename class_of<T>::type;

template<typename T>
struct type_of;
template<typename Class, typename Type>
struct type_of<member_ptr<Class, Type>> {
	using type = Type;
};
template<typename T>
using type_of_t = typename type_of<T>::type;

} // namespace aw

#endif // aw_types_traits_members_h
