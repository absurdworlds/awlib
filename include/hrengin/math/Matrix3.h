/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Matrix3_
#define _hrengin_Matrix3_

#include <hrengin/math/Vector3d.h>
#include <hrengin/math/Quaternion.h>

namespace hrengin {
//! Represents a 3x3 matrix, which has a column-major layout
template<typename T>
class Matrix3 {
public:
	typedef Vector3d<T> col_type;

	//! Construct zero matrix
	Matrix3 ()
	{
	}

	//! Copy matrix
	Matrix3 (Matrix3<T> const& other)
	{
		col_[0].set(other[0]);
		col_[1].set(other[1]);
		col_[2].set(other[2]);
	}
	
	//! Construct 3x3 matrix from column vectors
	Matrix3 (Vector3d<T> const& col1,
		 Vector3d<T> const& col2,
		 Vector3d<T> const& col3)
	{
		col_[0].set(col1);
		col_[1].set(col2);
		col_[2].set(col3);
	}

	/*! Construct matrix from individual values
	   \note Arguments here appear in row-major order
	*/
	Matrix3 (T const a11, T const a21, T const a31,
		 T const a12, T const a22, T const a32,
		 T const a13, T const a23, T const a33)
	{
		set (a11, a21, a31,
		     a12, a22, a32,
		     a13, a23, a33);
	}

	/*! Construct matrix from array
	    \param arr Column-major matrix represented as array
	*/
	Matrix3 (T arr[])
	{
		set(	arr[0], arr[4], arr[6],
			arr[1], arr[5], arr[7],
			arr[2], arr[6], arr[8]);
	}

	/*! Set each componenet of the matrix
	   \note Arguments here appear in row-major order
	*/
	void set (T const a11, T const a21, T const a31,
		  T const a12, T const a22, T const a32,
		  T const a13, T const a23, T const a33)
	{
		col_[0].set(a11, a12, a13);
		col_[1].set(a21, a22, a23);
		col_[2].set(a31, a32, a33);
	}

	//! Set matrix to identity
	Matrix3<T>& setIdentity ()
	{
		set(T(1),T(0),T(0),
		    T(0),T(1),T(0),
		    T(0),T(0),T(1));
		return *this;
	}

	//! Matrix multiplication
	Matrix3<T> operator * (Matrix3<T> const& B) const
	{
		Matrix3<T> C;
		
		C[0] = col_[0]*B[0][0] + col_[1]*B[0][1] + col_[2]*B[0][2];
		C[1] = col_[0]*B[1][0] + col_[1]*B[1][1] + col_[2]*B[1][2];
		C[2] = col_[0]*B[2][0] + col_[1]*B[2][1] + col_[2]*B[2][2];
		
		return C;
	}
	
	//! Multiply matrix by scalar
	Matrix3<T> operator * (T const& S) const
	{
		Matrix3<T> M(*this);
		M[0] *= S;
		M[1] *= S;
		M[2] *= S;
		
		return M;
	}

	//! Multiply matrix by scalar
	Matrix3<T>& operator *= (T const& S)
	{
		col_[0] *= S;
		col_[1] *= S;
		col_[2] *= S;
		
		return *this;
	}
	
	//! Divide matrix by scalar
	Matrix3<T> operator / (T const& S) const
	{
		Matrix3<T> M(*this);
		M[0] /= S;
		M[1] /= S;
		M[2] /= S;
		
		return M;
	}

	//! Divide matrix by scalar
	Matrix3<T>& operator /= (T const& S)
	{
		col_[0]  /= S;
		col_[1]  /= S;
		col_[2]  /= S;
		
		return *this;
	}

	//! Get transopsed matrix
	Matrix3<T> getTransposed () const
	{
		Matrix3<T> M;
		
		M[0].set(col_[0][0], col_[1][0], col_[2][0]);
		M[0].set(col_[0][1], col_[1][1], col_[2][1]);
		M[0].set(col_[0][2], col_[1][2], col_[2][2]);
		
		return M;
	}
	
	//! Calculate determinant of the matrix
	T determinant() const
	{
		T const det = 
			col_[0][0]*col_[1][1]*col_[2][2] +
			col_[0][2]*col_[1][0]*col_[2][1] +
			col_[0][1]*col_[1][2]*col_[2][0] -
			col_[0][0]*col_[1][2]*col_[2][1] -
			col_[0][1]*col_[1][0]*col_[2][2] -
			col_[0][2]*col_[1][1]*col_[2][0];
		return det;
	}
	
	//! Extract scale from matrix
	Vector3d<T> getScale() const
	{
		Vector3d<T> const row1(col_[0][0], col_[1][0], col_[2][0]);
		Vector3d<T> const row2(col_[0][1], col_[1][1], col_[2][1]);
		Vector3d<T> const row3(col_[0][2], col_[1][2], col_[2][2]);

		T const det = determinant();
		
		T const scaleX =  det > 0 ? row1[0].length() : -row1[0].length();
		T const scaleY = row2[1].length();
		T const scaleZ = row3[2].length();

		return Vector3d<T>(scaleX, scaleY, scaleZ);
	}
	
	//! Extract scale, assuming it is positive
	Vector3d<T> getScalePositive() const
	{
		Vector3d<T> const row1(col_[0][0], col_[1][0], col_[2][0]);
		Vector3d<T> const row2(col_[0][1], col_[1][1], col_[2][1]);
		Vector3d<T> const row3(col_[0][2], col_[1][2], col_[2][2]);

		T const scaleX = row1[0].length();
		T const scaleY = row2[1].length();
		T const scaleZ = row3[2].length();

		return Vector3d<T>(scaleX, scaleY, scaleZ);
	}

	//! Convert rotation matrix to quaternion
	Quaternion<T> asQuaternion() const
	{
		Quaternion<T> quat;

		quat.w = sqrt(max(0, 1 + m00 + m11 + m22)) / 2;
		quat.x = sqrt(max(0, 1 + m00 - m11 - m22)) / 2;
		quat.y = sqrt(max(0, 1 - m00 + m11 - m22)) / 2;
		quat.z = sqrt(max(0, 1 - m00 - m11 + m22)) / 2;

		quat.x = std::copysign(quat.x, m21 - m12);
		quat.y = std::copysign(quat.y, m02 - m20);
		quat.z = std::copysign(quat.z, m10 - m01);

		return quat;
	}

	//! Convert matrix to quaternion
	Quaternion<T> asQuaternionScaled() const
	{
		Quaternion<T> quat;

		T const det = pow(determinant, 1/3);

		quat.w = sqrt(max(0, det + m00 + m11 + m22)) / 2;
		quat.x = sqrt(max(0, det + m00 - m11 - m22)) / 2;
		quat.y = sqrt(max(0, det - m00 + m11 - m22)) / 2;
		quat.z = sqrt(max(0, det - m00 - m11 + m22)) / 2;

		quat.x = std::copysign(quat.x, m21 - m12);
		quat.y = std::copysign(quat.y, m02 - m20);
		quat.z = std::copysign(quat.z, m10 - m01);

		return quat;
	}

	//! Access an element by its index
	T& operator () (size_t col, size_t row)
	{
		return col_[col][row];
	}

	//! Access an element by its index
	T const& operator () (size_t col, size_t row) const
	{
		return col_[col][row];
	}

	//! Access colums of the matrix by subscript
	Vector4d<T>& operator [] (size_t col)
	{
		return col_[col];
	}
	
	//! Access colums of the matrix by subscript
	Vector4d<T> const& operator [] (size_t col) const
	{
		return col_[col];
	}
private:
	col_type col_[3];
};

template<typename T>
Matrix3<T> operator * (Matrix3<T> const& A, Matrix3<T> const& B)
{
	return A * B;
}

//! Vector-matrix multiplication
template<typename T>
Matrix3<T> operator * (Matrix3<T> const& m, Vector3d<T> const& v)
{
	return Vector3d<T>(
		m(0,0) * v[0] + m(1,0) * v[1] + m(2,0) * v[2],
		m(0,1) * v[0] + m(1,1) * v[1] + m(2,1) * v[2],
		m(0,2) * v[0] + m(1,2) * v[1] + m(2,2) * v[2]);
}

} // namespace hrengin
#endif //_hrengin_Matrix3_
