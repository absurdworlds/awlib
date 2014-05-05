
// This is 2d vector, currently almost fully replicating the irr:vector2d

#ifndef __HR_T_VECTOR_2D_H__
#define __HR_T_VECTOR_2D_H__

namespace hrengin
{
template <class T>
class vector2d
{
public:
	// Constructors	
	vector2d() : X(0), Y(0) {}
	vector2d(T vx, T vy) : X(vx), Y(vy) {}
	
	explicit vector2d(T v) : X(v), Y(v) {}

	// Copy
	vector2d(const vector2d<T>& other) : X(other.X), Y(other.Y) {}

	// All operators

	vector2d<T>& operator=(const vector2d<T>& other) {X = other.X; Y = other.Y; return *this; }

	vector2d<T> operator-() const {return vector2d<T>(-X, -Y);}

	
	vector2d<T> operator+(const vector2d<T>& other) const {return vector2d<T>(X + other.X, Y + other.Y);}
	vector2d<T>& operator+=(const vector2d<T>& other) { X+=other.X; Y+=other.Y; return *this; }

	vector2d<T> operator-(const vector2d<T>& other) const { return vector2d<T>(X - other.X, Y - other.Y); }
	vector2d<T>& operator-=(const vector2d<T>& other) { X-=other.X; Y-=other.Y; return *this; }
	vector2d<T> operator-(const T v) const { return vector2d<T>(X - v, Y - v); }
	vector2d<T>& operator-=(const T v) { X-=v; Y-=v; return *this; }

	vector2d<T> operator*(const vector2d<T>& other) const { return vector2d<T>(X * other.X, Y * other.Y); }
	vector2d<T>& operator*=(const vector2d<T>& other) { X*=other.X; Y*=other.Y; return *this; }
	vector2d<T> operator*(const T v) const { return vector2d<T>(X * v, Y * v); }
	vector2d<T>& operator*=(const T v) { X*=v; Y*=v; return *this; }

	vector2d<T> operator/(const vector2d<T>& other) const { return vector2d<T>(X / other.X, Y / other.Y); }
	vector2d<T>& operator/=(const vector2d<T>& other) { X/=other.X; Y/=other.Y; return *this; }
	vector2d<T> operator/(const T v) const { return vector2d<T>(X / v, Y / v); }
	vector2d<T>& operator/=(const T v) { X/=v; Y/=v; return *this; }


	bool operator<=(const vector2d<T>&other) const
	{
		return 	(X<other.X || math::equals(X, other.X)) ||
				(math::equals(X, other.X) && (Y<other.Y || math::equals(Y, other.Y)));
	}

	bool operator>=(const vector2d<T>&other) const
	{
		return 	(X>other.X || math::equals(X, other.X)) ||
				(math::equals(X, other.X) && (Y>other.Y || math::equals(Y, other.Y)));
	}

	bool operator<(const vector2d<T>&other) const
	{
		return 	(X<other.X && !math::equals(X, other.X)) ||
				(math::equals(X, other.X) && Y<other.Y && !math::equals(Y, other.Y));
	}

	bool operator>(const vector2d<T>&other) const
	{
		return 	(X>other.X && !math::equals(X, other.X)) ||
				(math::equals(X, other.X) && Y>other.Y && !math::equals(Y, other.Y));
	}

	bool operator==(const vector2d<T>& other) const { return equals(other); }
	bool operator!=(const vector2d<T>& other) const { return !equals(other); }

	// Functions

	bool equals(const vector2d<T>& other) const
	{
		return math::equals(X, other.X) && math::equals(Y, other.Y);
	}

	// Vector coordinates
	T X;
	T Y;
};

typedef vector2d<float32>	vectorf2d;
typedef vector2d<float64>	vectord2d;
typedef vector2d<int32>		vectori2d;
}

#endif //__HR_T_VECTOR_2D_H__