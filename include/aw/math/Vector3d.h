/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Vector3d_
#define _aw_Vector3d_
#include <aw/math/Vector.h>

namespace aw {
//! Represents vector in 3D space
template <class T>
class Vector<T,3> {
public:
	//! Default constructor. Constructs zero vector.
	Vector()
		: coord()
	{
	}

	//! Construct vector with same value for coordinates
	explicit Vector(T const v)
		: coord({v, v, v})
	{
	}

	//! Construct vector with x, y coordinates of \a vec2
	explicit Vector(Vector<T,2> const& vec2)
		: coord({vec2[0], vec2[1], 0})
	{
	}

	//! Construct vector with individual coodrinates
	Vector(T const x, T const y, T const z)
		: coord({x, y, z})
	{
	}

	//! Copy constructor
	Vector(Vector<T,3> const& other)
		: coord{other[0], other[1], other[2]}
	{
	}

	//! Convert from vector of another datatype
	template<typename Tp>
	Vector(Vector<Tp,3> const& other)
		: coord{static_cast<T>(other[0]),
		        static_cast<T>(other[1]),
		        static_cast<T>(other[2])}
	{
	}

	//! Set coordinates of the vector
	void set(T const x, T const y, T const z)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}

	//! Copy coordinates of other vector
	void set(Vector<T,3> const& other)
	{
		coord[0] = other[0];
		coord[1] = other[1];
		coord[2] = other[2];
	}

	//! Copy coordinates of other vector
	Vector<T,3>& operator = (Vector<T,3> const& other)
	{
		set(other);
		return *this;
	}

	//! Vector addition
	Vector<T,3>& operator += (Vector<T,3> const& other)
	{ 
		coord[0] += other[0]; 
		coord[1] += other[1]; 
		coord[2] += other[2]; 
		return *this;
	}

	Vector<T,3>& operator += (T const val)
	{
		coord[0] += val;
		coord[1] += val;
		coord[2] += val;
		return *this;
	}

	Vector<T,3>& operator -= (Vector<T,3> const& other)
	{
		coord[0] -= other[0];
		coord[1] -= other[1];
		coord[2] -= other[2];
		return *this;
	}

	Vector<T,3>& operator -= (T const val)
	{
		coord[0] -= val;
		coord[1] -= val;
		coord[2] -= val;
		return *this;
	}

	//! Element-by-element multiplication
	Vector<T,3>& operator *= (Vector<T,3> const& other)
	{
		coord[0] *= other[0];
		coord[1] *= other[1];
		coord[2] *= other[2];
		return *this;
	}

	Vector<T,3>& operator *= (T const v)
	{
		coord[0] *= v;
		coord[1] *= v;
		coord[2] *= v;
		return *this;
	}

	//! Element-by-element division
	Vector<T,3>& operator /= (Vector<T,3> const& other)
	{
		coord[0] /= other[0];
		coord[1] /= other[1];
		coord[2] /= other[2];
		return *this;
	}

	Vector<T,3>& operator /= (T const val)
	{
		T const inv = T(1.0/val);
		return (*this *= inv);
	}

#if 0
	/*!
	 * Check if vectors are identical.
	 * \return
	 * 	`true` if vectors are identical, otherwise `false`.
	 */
	bool operator == (Vector<T,3> const& other) const
	{
		return (math::equals(coord[0], other[0]) &&
		        math::equals(coord[1], other[1]) &&
		        math::equals(coord[2], other[2]));
	}
#endif

	//! Calculate the dot product with another vector
	T dot(Vector<T,3> const& other) const
	{
		return coord[0]*other[0] +
		       coord[1]*other[1] +
		       coord[2]*other[2];
	}

	//! Get squared length of the vector.
	T lengthSquared() const
	{
		return dot(*this);
	}

	//! Get length of the vector.
	T length() const
	{
		return math::sqrt(lengthSquared());
	}

	//! Calculate the cross product with another vector
	Vector<T,3> cross(Vector<T,3> const& other) const
	{
		f32 const cx = coord[1] * other[2] - coord[2] * other[1];
		f32 const cy = coord[2] * other[0] - coord[0] * other[2];
		f32 const cz = coord[0] * other[1] - coord[1] * other[0];
		return {cx, cy, cz};
	}

	//! Get distance from another point
	T distance(Vector<T,3> const& other) const
	{
		return (*this - other).length();
	}

	//! Get squared distance from another point
	T distanceSquared(Vector<T,3> const& other) const
	{
		return (*this - other).lengthSquared();
	}

	//! Set the length of the vector to a new value
	Vector<T,3>& setLength(T const newlength)
	{
		normalize();
		return (*this *= newlength);
	}

	//! Normalize the vector
	Vector<T,3>& normalize()
	{
		f64 length = lengthSquared();
		if (length == 0)
			return *this;

		length = math::invSqrt(length);

		return (*this *= length);
	}

	//! Get a normalized version of a vector without modifying it
	Vector<T,3> normalized() const
	{
		Vector<T,3> temp(*this);
		temp.normalize();

		return temp;
	}

	//! Invert the vector.
	Vector<T,3>& invert()
	{
		return (*this *= -1);
	}

	/*!
	 * Get rotation around Y axis
	 */
	T yaw() const
	{
		T yaw = T(atan2(f64(x()), f64(z())));

		if (yaw <= -math::Pi) {
			yaw += math::DoublePi;
		} else if (yaw > math::Pi) {
			yaw -= math::DoublePi;
		}

		return math::radToDeg(yaw);
	}

	/*!
	 * Get rotation around X axis
	 */
	T pitch() const
	{
		f64 const xz = math::sqrt(x()*x() + z()*z());
		T const pitch = T(atan2(f64(xz), f64(y)) - math::HalfPi);

		if (pitch <= -math::Pi) {
			pitch += math::DoublePi;
		} else if (pitch >= math::Pi) {
			pitch -= math::DoublePi;
		}

		return math::radToDeg(pitch);
	}

	/*!
	 * Get euler angles such that when applied to a (0,0,1) direction
	 * vector would make it point in the same direction as this vector.
         *
	 * \return
	 *     A rotation vector containing the X (pitch) and Y (raw)
	 *     rotations in degrees, of this vector.
	 *     The Z (roll) rotation is always 0, since direction vector
	 *     doesn't have roll rotation.
	 */
	Vector<T,3> horizontalAngle() const
	{
		return {yaw(), pitch(), 0};
	}

	//! Fill an array of 4 values with the vector data
	void toArrayOf4(T* array) const
	{
		array[0] = coord[0];
		array[1] = coord[1];
		array[2] = coord[2];
		array[3] = 0;
	}

	//! Fill an array of 3 values with the vector data
	void toArrayOf3(T* array) const
	{
		array[0] = coord[0];
		array[1] = coord[1];
		array[2] = coord[2];
	}

	//! Access elements of the vector by subscript
	T& operator [] (size_t elem)
	{
		return coord[elem];
	}

	//! Access elements of the vector by subscript
	T const& operator [] (size_t elem) const
	{
		return coord[elem];
	}

	//! Get coordinate along X axis
	T& x()
	{
		return coord[0];
	}

	//! Get coordinate along Y axis
	T& y()
	{
		return coord[1];
	}

	//! Get coordinate along Z axis
	T& z()
	{
		return coord[2];
	}

	//! Get coordinate along X axis
	T x() const
	{
		return coord[0];
	}

	//! Get coordinate along Y axis
	T y() const
	{
		return coord[1];
	}

	//! Get coordinate along Z axis
	T z() const
	{
		return coord[2];
	}

private:
	//! Coordinates of the vector
	std::array<T, 3> coord;
};

template<typename T>
using Vector3d = Vector<T,3>;

//! Partial specialization for integer vectors
template <>
inline Vector3d<i32>& Vector3d<i32>::operator /= (i32 const val) 
{
	coord[0] /= val;
	coord[1] /= val;
	coord[2] /= val;
	return *this;
}
} // namespace aw
#endif//_aw_Vector3d_
