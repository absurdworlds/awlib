/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Matrix4_
#define _hrengin_Matrix4_

#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Vector4d.h>

namespace hrengin {

//! Represents a 4x4 matrix, which has a column-major layout
template<typename T>
class Matrix4 {
public:
	void set (T const a11, T const a21, T const a31, T const a41
		  T const a12, T const a22, T const a32, T const a42,
		  T const a13, T const a23, T const a33, T const a43,
		  T const a14, T const a24, T const a34, T const a44)
	{
		m_[0]  = a11;	
		m_[1]  = a21;
		m_[2]  = a31;	
		m_[3]  = a41;	
		m_[4]  = a12;
		m_[5]  = a22;     
		m_[6]  = a32;     
		m_[7]  = a42;     
		m_[8]  = a13;     
		m_[9]  = a23;     
		m_[10] = a33;     
		m_[11] = a43;     
		m_[12] = a14;     
		m_[13] = a24;     
		m_[14] = a34;
		m_[15] = a44;     
	}	
	
	//! Set matrix to identity
	Matrix4<T>& setIdentity ()
	{
		set(T(1),T(0),T(0),T(0),
		    T(0),T(1),T(0),T(0),
		    T(0),T(0),T(1),T(0),
		    T(0),T(0),T(0),T(1));	
		return *this;
	}

	//! Matrix multiplication
	Matrix4<T> operator * (Matrix4<T> const& B)
	{
		T* A = m_;
		Matrix4<T> C;

		C[0] = A[0]*B[0] + A[4]*B[1] + A[8]* B[2] + A[12]*B[3];
		C[1] = A[1]*B[0] + A[5]*B[1] + A[9]* B[2] + A[13]*B[3];
		C[2] = A[2]*B[0] + A[6]*B[1] + A[10]*B[2] + A[14]*B[3];
		C[3] = A[3]*B[0] + A[7]*B[1] + A[11]*B[2] + A[15]*B[3];
		
		C[4] = A[0]*B[4] + A[4]*B[5] + A[8]* B[6] + A[12]*B[7];
		C[5] = A[1]*B[4] + A[5]*B[5] + A[9]* B[6] + A[13]*B[7];
		C[6] = A[2]*B[4] + A[6]*B[5] + A[10]*B[6] + A[14]*B[7];
		C[7] = A[3]*B[4] + A[7]*B[5] + A[11]*B[6] + A[15]*B[7];
		
		C[8]  = A[0]*B[8] + A[4]*B[9] + A[8]* B[10] + A[12]*B[11];
		C[9]  = A[1]*B[8] + A[5]*B[9] + A[9]* B[10] + A[13]*B[11];
		C[10] = A[2]*B[8] + A[6]*B[9] + A[10]*B[10] + A[14]*B[11];
		C[11] = A[3]*B[8] + A[7]*B[9] + A[11]*B[10] + A[15]*B[11];

		C[12] = A[0]*B[12] + A[4]*B[13] + A[8]* B[14] + A[12]*B[15];
		C[13] = A[1]*B[12] + A[5]*B[13] + A[9]* B[14] + A[13]*B[15];
		C[14] = A[2]*B[12] + A[6]*B[13] + A[10]*B[14] + A[14]*B[15];
		C[15] = A[3]*B[12] + A[7]*B[13] + A[11]*B[14] + A[15]*B[15];
		
		return C;
	}
	
	//! Multiply matrix by scalar
	Matrix4<T> operator * (T const& S)
	{
		Matrix4<T> M[16];
		M[0]  = m_[0]  * S;
		M[1]  = m_[1]  * S;
		M[2]  = m_[2]  * S;
		M[3]  = m_[3]  * S;
		M[4]  = m_[4]  * S;
		M[5]  = m_[5]  * S;
		M[6]  = m_[6]  * S;
		M[7]  = m_[7]  * S;
		M[8]  = m_[8]  * S;
		M[9]  = m_[9]  * S;
		M[10] = m_[10] * S;
		M[11] = m_[11] * S;
		M[12] = m_[12] * S;
		M[13] = m_[13] * S;
		M[14] = m_[14] * S;
		M[15] = m_[15] * S;
		
		return M;
	}

	//! Multiply matrix by scalar
	Matrix4<T>& operator *= (T const& S)
	{
		m_[0]  *= S;
		m_[1]  *= S;
		m_[2]  *= S;
		m_[3]  *= S;
		m_[4]  *= S;
		m_[5]  *= S;
		m_[6]  *= S;
		m_[7]  *= S;
		m_[8]  *= S;
		m_[9]  *= S;
		m_[10] *= S;
		m_[11] *= S;
		m_[12] *= S;
		m_[13] *= S;
		m_[14] *= S;
		m_[15] *= S;
		
		return *this;
	}

	//! Access an element by its index
	T& operator () (size_t row, size_t col)
	{
		return T[col*4 + row];
	}

	//! Access an element by its index
	T const& operator () (size_t row, size_t col) const
	{
		return T[col*4 + row];
	}

	//! Linear access to elements of the matrix
	T& operator [] (size_t col)
	{
		return m_[col];
	}
	
	//! Linear access to elements of the matrix
	T const& operator [] (size_t col) const
	{
		return m_[col];
	}
private:
	T m_[16];
};

template<typename T>
Matrix4<T> operator * (Matrix4<T> const& A, Matrix4<T> const& B) const
{
	return A * B;
}

//! Vector-matrix multiplication
template<typename T>
Matrix4<T> operator * (Matrix4<T> const& m, Vector3d<T> const& v)
{
	return Vector3d(
		m(0,0) * v.x + m(1,0) * v.y + m(2,0) * v.z + m(3,0) * 1,
		m(0,1) * v.x + m(1,1) * v.y + m(2,1) * v.z + m(3,1) * 1,
		m(0,2) * v.x + m(1,2) * v.y + m(2,2) * v.z + m(3,2) * 1,
		m(0,3) * v.x + m(1,3) * v.y + m(2,3) * v.z + m(3,3) * 1);
}

template<typename T>
Matrix4<T> operator * (Matrix4<T> const& m, Vector4d<T> const& v)
{
	return Vector4d(
		m(0,0) * v.x + m(1,0) * v.y + m(2,0) * v.z + m(3,0) * v.w,
		m(0,1) * v.x + m(1,1) * v.y + m(2,1) * v.z + m(3,1) * v.w,
		m(0,2) * v.x + m(1,2) * v.y + m(2,2) * v.z + m(3,2) * v.w,
		m(0,3) * v.x + m(1,3) * v.y + m(2,3) * v.z + m(3,3) * v.w);
}

} // namespace hrengin

#endif //_hrengin_Matrix4_
