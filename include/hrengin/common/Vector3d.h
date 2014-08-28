#ifndef _hrengin_Vector3d_
#define _hrengin_Vector3d_

#include <hrengin/common/math.h>

namespace hrengin {

template <class T>
class hrVector3d
{
public: /* Data */
// Vector coordinates
	T X;
	T Y;
	T Z;
public:
	hrVector3d() 
		: X(0), Y(0), Z(0) 
	{	}

	hrVector3d(T x, T y, T z) 
		: X(x), Y(y), Z(z) 
	{	}

	explicit hrVector3d(T v) 
		: X(v), Y(v), Z(v) 
	{	}

	// Copy constructor
	hrVector3d(const hrVector3d<T>& other) 
		: X(other.X), Y(other.Y), Z(other.Z) 
	{	}

	// operators

	hrVector3d<T> operator-() const 
	{
		return hrVector3d<T>(-X, -Y, -Z);
	}

	hrVector3d<T>& operator=(const hrVector3d<T>& other)
	{
		X = other.X; 
		Y = other.Y; 
		Z = other.Z; 
		return *this;
	}

	hrVector3d<T> operator+(const hrVector3d<T>& other) const
	{
		return hrVector3d<T>(X + other.X, Y + other.Y, Z + other.Z); 
	}

	hrVector3d<T>& operator+=(const hrVector3d<T>& other)
	{ 
		X+=other.X; 
		Y+=other.Y; 
		Z+=other.Z; 
		return *this;
	}

	hrVector3d<T> operator+(const T val) const
	{
		return hrVector3d<T>(X + val, Y + val, Z + val);
	}

	hrVector3d<T>& operator+=(const T val)
	{
		X+=val;
		Y+=val;
		Z+=val;
		return *this;
	}

	hrVector3d<T> operator-(const hrVector3d<T>& other) const
	{
		return hrVector3d<T>(X - other.X, Y - other.Y, Z - other.Z);
	}

	hrVector3d<T>& operator-=(const hrVector3d<T>& other)
	{
		X-=other.X;
		Y-=other.Y;
		Z-=other.Z;
		return *this;
	}

	hrVector3d<T> operator-(const T val) const
	{
		return hrVector3d<T>(X - val, Y - val, Z - val);
	}

	hrVector3d<T>& operator-=(const T val)
	{
		X-=val;
		Y-=val;
		Z-=val;
		return *this;
	}

	hrVector3d<T> operator*(const hrVector3d<T>& other) const
	{
		return hrVector3d<T>(X * other.X, Y * other.Y, Z * other.Z);
	}

	hrVector3d<T>& operator*=(const hrVector3d<T>& other)
	{
		X*=other.X;
		Y*=other.Y;
		Z*=other.Z;
		return *this;
	}

	hrVector3d<T> operator*(const T v) const
	{
		return hrVector3d<T>(X * v, Y * v, Z * v);
	}

	hrVector3d<T>& operator*=(const T v)
	{
		X*=v;
		Y*=v;
		Z*=v;
		return *this;
	}

	hrVector3d<T> operator/(const hrVector3d<T>& other) const
	{
		return hrVector3d<T>(X / other.X, Y / other.Y, Z / other.Z);
	}

	hrVector3d<T>& operator/=(const hrVector3d<T>& other)
	{
		X/=other.X;
		Y/=other.Y;
		Z/=other.Z;
		return *this;
	}

	hrVector3d<T> operator/(const T v) const
	{
		T i=(T)1.0/v;
		return hrVector3d<T>(X * i, Y * i, Z * i);
	}

	hrVector3d<T>& operator/=(const T v)
	{
		T i=(T)1.0/v;
		X*=i; 
		Y*=i; 
		Z*=i; 
		return *this; 
	}
	/*
	hrVector3d<T>& set(const T nx, const T ny, const T nz) {X=nx; Y=ny; Z=nz; return *this;}
	hrVector3d<T>& set(const hrVector3d<T>& p) {X=p.X; Y=p.Y; Z=p.Z;return *this;}-*/
	
	// Normalize the vector
	hrVector3d<T>& normalize()
	{
		f64 length = squareLength();
		if (length == 0 )
		{
			// don't normalize zero vector
			return *this;
		}

		length = math::inverseSqrt(length);

		X = (T)(X * length);
		Y = (T)(Y * length);
		Z = (T)(Z * length);
		return *this;
	}

	// Returns normalized vector without modifying it
	hrVector3d<T> normalized() const
	{
		f64 length = squareLength();
		if (length == 0 )
		{
			// don't normalize zero vector
			return hrVector3d<T>();
		}
		length = math::inverseSqrt(length);

		return hrVector3d<T>((T)(X * length), (T)(Y * length), (T)(Z * length));
	}

	//! Get length of the vector.
	T length() const 
	{ 
		return math::sqrt( X*X + Y*Y + Z*Z ); 
	}
	
	//! Get squared length of the vector.
	T squareLength() const 
	{ 
		return X*X + Y*Y + Z*Z; 
	}

	/*

	//! Get the dot product with another vector.
	T dotProduct(const hrVector3d<T>& other) const
	{
		return X*other.X + Y*other.Y + Z*other.Z;
	}

	//! Get distance from another point.
	//** Here, the vector is interpreted as point in 3 dimensional space. *
	T getDistanceFrom(const hrVector3d<T>& other) const
	{
		return hrVector3d<T>(X - other.X, Y - other.Y, Z - other.Z).getLength();
	}

	//! Returns squared distance from another point.
	//** Here, the vector is interpreted as point in 3 dimensional space. *
	T getDistanceFromSQ(const hrVector3d<T>& other) const
	{
		return hrVector3d<T>(X - other.X, Y - other.Y, Z - other.Z).getLengthSQ();
	}

	//! Calculates the cross product with another vector.
	//** \param p Vector to multiply with.
	\return Crossproduct of this vector with p. *
	hrVector3d<T> crossProduct(const hrVector3d<T>& p) const
	{
		return hrVector3d<T>(Y * p.Z - Z * p.Y, Z * p.X - X * p.Z, X * p.Y - Y * p.X);
	}

	//! Returns if this vector interpreted as a point is on a line between two other points.
	//** It is assumed that the point is on the line.
	\param begin Beginning vector to compare between.
	\param end Ending vector to compare between.
	\return True if this vector is between begin and end, false if not. *
	bool isBetweenPoints(const hrVector3d<T>& begin, const hrVector3d<T>& end) const
	{
		const T f = (end - begin).getLengthSQ();
		return getDistanceFromSQ(begin) <= f &&
			getDistanceFromSQ(end) <= f;
	}


	//! Sets the length of the vector to a new value
	hrVector3d<T>& setLength(T newlength)
	{
		normalize();
		return (*this *= newlength);
	}

	//! Inverts the vector.
	hrVector3d<T>& invert()
	{
		X *= -1;
		Y *= -1;
		Z *= -1;
		return *this;
	}

	//! Rotates the vector by a specified number of degrees around the Y axis and the specified center.
	//** \param degrees Number of degrees to rotate around the Y axis.
	\param center The center of the rotation. *
	void rotateXZBy(f64 degrees, const hrVector3d<T>& center=hrVector3d<T>())
	{
		degrees *= DEGTORAD64;
		f64 cs = cos(degrees);
		f64 sn = sin(degrees);
		X -= center.X;
		Z -= center.Z;
		set((T)(X*cs - Z*sn), Y, (T)(X*sn + Z*cs));
		X += center.X;
		Z += center.Z;
	}

	//! Rotates the vector by a specified number of degrees around the Z axis and the specified center.
	//** \param degrees: Number of degrees to rotate around the Z axis.
	\param center: The center of the rotation. *
	void rotateXYBy(f64 degrees, const hrVector3d<T>& center=hrVector3d<T>())
	{
		degrees *= DEGTORAD64;
		f64 cs = cos(degrees);
		f64 sn = sin(degrees);
		X -= center.X;
		Y -= center.Y;
		set((T)(X*cs - Y*sn), (T)(X*sn + Y*cs), Z);
		X += center.X;
		Y += center.Y;
	}

	//! Rotates the vector by a specified number of degrees around the X axis and the specified center.
	//** \param degrees: Number of degrees to rotate around the X axis.
	\param center: The center of the rotation. *
	void rotateYZBy(f64 degrees, const hrVector3d<T>& center=hrVector3d<T>())
	{
		degrees *= DEGTORAD64;
		f64 cs = cos(degrees);
		f64 sn = sin(degrees);
		Z -= center.Z;
		Y -= center.Y;
		set(X, (T)(Y*cs - Z*sn), (T)(Y*sn + Z*cs));
		Z += center.Z;
		Y += center.Y;
	}

	//! Creates an interpolated vector between this vector and another vector.
	//** \param other The other vector to interpolate with.
	\param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
	Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
	\return An interpolated vector.  This vector is not modified. *
	hrVector3d<T> getInterpolated(const hrVector3d<T>& other, f64 d) const
	{
		const f64 inv = 1.0 - d;
		return hrVector3d<T>((T)(other.X*inv + X*d), (T)(other.Y*inv + Y*d), (T)(other.Z*inv + Z*d));
	}

	//! Creates a quadratically interpolated vector between this and two other vectors.
	//** \param v2 Second vector to interpolate with.
	\param v3 Third vector to interpolate with (maximum at 1.0f)
	\param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
	Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
	\return An interpolated vector. This vector is not modified. *
	hrVector3d<T> getInterpolated_quadratic(const hrVector3d<T>& v2, const hrVector3d<T>& v3, f64 d) const
	{
		// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
		const f64 inv = (T) 1.0 - d;
		const f64 mul0 = inv * inv;
		const f64 mul1 = (T) 2.0 * d * inv;
		const f64 mul2 = d * d;

		return hrVector3d<T> ((T)(X * mul0 + v2.X * mul1 + v3.X * mul2),
				(T)(Y * mul0 + v2.Y * mul1 + v3.Y * mul2),
				(T)(Z * mul0 + v2.Z * mul1 + v3.Z * mul2));
	}

	//! Sets this vector to the linearly interpolated vector between a and b.
	//** \param a first vector to interpolate with, maximum at 1.0f
	\param b second vector to interpolate with, maximum at 0.0f
	\param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
	Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
	*
	hrVector3d<T>& interpolate(const hrVector3d<T>& a, const hrVector3d<T>& b, f64 d)
	{
		X = (T)((f64)b.X + ( ( a.X - b.X ) * d ));
		Y = (T)((f64)b.Y + ( ( a.Y - b.Y ) * d ));
		Z = (T)((f64)b.Z + ( ( a.Z - b.Z ) * d ));
		return *this;
	}*/

	// Took this from Irrlicht.

	//! Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
	/** Thanks to Arras on the Irrlicht forums for this method.  This utility method is very useful for
	orienting scene nodes towards specific targets.  For example, if this vector represents the difference
	between two scene nodes, then applying the result of getHorizontalAngle() to one scene node will point
	it at the other one.
	Example code:
	// Where target and seeker are of type ISceneNode*
	const vector3df toTarget(target->getAbsolutePosition() - seeker->getAbsolutePosition());
	const vector3df requiredRotation = toTarget.getHorizontalAngle();
	seeker->setRotation(requiredRotation);

	\return A rotation vector containing the X (pitch) and Y (raw) rotations (in degrees) that when applied to a
	+Z (e.g. 0, 0, 1) direction vector would make it point in the same direction as this vector. The Z (roll) rotation
	is always 0, since two Euler rotations are sufficient to point in any given direction. */
	hrVector3d<T> getHorizontalAngle() const
	{
		hrVector3d<T> angle;

		angle.Y = (T) atan2((f64)X, (f64)Z);

		if (angle.Y < 0)
			angle.Y += math::DOUBLE_PI64;
		if (angle.Y >= math::DOUBLE_PI64)
			angle.Y -= math::DOUBLE_PI64;

		const f64 z1 = math::sqrt(X*X + Z*Z);

		angle.X = (T)(atan2((f64)z1, (f64)Y) - math::HALF_PI64);

		if (angle.X < 0)
			angle.X += math::DOUBLE_PI64;
		if (angle.X >= math::DOUBLE_PI64)
			angle.X -= math::DOUBLE_PI64;

		return angle * math::RADTODEG64;
	}
	/*
	//! Get the spherical coordinate angles
	//** This returns Euler degrees for the point represented by
	this vector.  The calculation assumes the pole at (0,1,0) and
	returns the angles in X and Y.
	*
	hrVector3d<T> getSphericalCoordinateAngles() const
	{
		hrVector3d<T> angle;
		const f64 length = X*X + Y*Y + Z*Z;

		if (length)
		{
			if (X!=0)
			{
				angle.Y = (T)(atan2((f64)Z,(f64)X) * RADTODEG64);
			}
			else if (Z<0)
				angle.Y=180;

			angle.X = (T)(acos(Y * core::reciprocal_squareroot(length)) * RADTODEG64);
		}
		return angle;
	}

	//! Builds a direction vector from (this) rotation vector.
	///** This vector is assumed to be a rotation vector composed of 3 Euler angle rotations, in degrees.
	The implementation performs the same calculations as using a matrix to do the rotation.

	\param[in] forwards  The direction representing "forwards" which will be rotated by this vector.
	If you do not provide a direction, then the +Z axis (0, 0, 1) will be assumed to be forwards.
	\return A direction vector calculated by rotating the forwards direction by the 3 Euler angles
	(in degrees) represented by this vector. *
	hrVector3d<T> rotationToDirection(const hrVector3d<T> & forwards = hrVector3d<T>(0, 0, 1)) const
	{
		const f64 cr = cos( core::DEGTORAD64 * X );
		const f64 sr = sin( core::DEGTORAD64 * X );
		const f64 cp = cos( core::DEGTORAD64 * Y );
		const f64 sp = sin( core::DEGTORAD64 * Y );
		const f64 cy = cos( core::DEGTORAD64 * Z );
		const f64 sy = sin( core::DEGTORAD64 * Z );

		const f64 srsp = sr*sp;
		const f64 crsp = cr*sp;

		const f64 pseudoMatrix[] = {
			( cp*cy ), ( cp*sy ), ( -sp ),
			( srsp*cy-cr*sy ), ( srsp*sy+cr*cy ), ( sr*cp ),
			( crsp*cy+sr*sy ), ( crsp*sy-sr*cy ), ( cr*cp )};

		return hrVector3d<T>(
			(T)(forwards.X * pseudoMatrix[0] +
				forwards.Y * pseudoMatrix[3] +
				forwards.Z * pseudoMatrix[6]),
			(T)(forwards.X * pseudoMatrix[1] +
				forwards.Y * pseudoMatrix[4] +
				forwards.Z * pseudoMatrix[7]),
			(T)(forwards.X * pseudoMatrix[2] +
				forwards.Y * pseudoMatrix[5] +
				forwards.Z * pseudoMatrix[8]));
	}

	//! Fills an array of 4 values with the vector data (usually floats).
	///** Useful for setting in shader constants for example. The fourth value
	will always be 0. *
	void getAs4Values(T* array) const
	{
		array[0] = X;
		array[1] = Y;
		array[2] = Z;
		array[3] = 0;
	}

	//! Fills an array of 3 values with the vector data (usually floats).
	///** Useful for setting in shader constants for example.*
	void getAs3Values(T* array) const
	{
		array[0] = X;
		array[1] = Y;
		array[2] = Z;
	}*/
		
};

//! partial specialization for integer vectors
template <>
inline hrVector3d<i32> hrVector3d<i32>::operator /(i32 val) const 
{
	return hrVector3d<i32>(X/val,Y/val,Z/val);
}

template <>
inline hrVector3d<i32>& hrVector3d<i32>::operator /=(i32 val) 
{
	X/=val;
	Y/=val;
	Z/=val;
	return *this;
}

/*
template <>
inline hrVector3d<s32> hrVector3d<s32>::getSphericalCoordinateAngles() const
{
	hrVector3d<s32> angle;
	const f64 length = X*X + Y*Y + Z*Z;

	if (length)
	{
		if (X!=0)
		{
			angle.Y = round32((f32)(atan2((f64)Z,(f64)X) * RADTODEG64));
		}
		else if (Z<0)
			angle.Y=180;

		angle.X = round32((f32)(acos(Y * core::reciprocal_squareroot(length)) * RADTODEG64));
	}
	return angle;
}*/

// multiply scalar and vector
template<class S, class T>
hrVector3d<T> operator*(const S scalar, const hrVector3d<T>& vector) { return vector*scalar; }

typedef hrVector3d<f32> Vectorf3d;
typedef hrVector3d<f64> Vectord3d;
typedef hrVector3d<i32> Vectori3d;
typedef hrVector3d<f64> Vector3d;

} // end namespace hrengin

#endif//_hrengin_Vector3d_
