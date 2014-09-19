/*
   hrengin game engine library
   Copyright (C) 2013-2014  absurdworlds
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License, version 3
   as published by the Free Software Foundation.
   
   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this program.  If not, see
   <http://www.gnu.org/licenses/>. 
 */
#ifndef _hrengin_Matrix4_
#define _hrengin_Matrix4_

namespace hrengin {

/* Represents a 4x4 matrix, whcih has a column-major layout
 */
template<typename T>
class Matrix4 {
public:
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
	Matrix4<T>& operator = *(T const& S)
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
	
	// operator for accessing an element by it's index
	T& operator () (size_t col, size_t row)
	{
		return T[col*4 + row];
	}

	// operator for accessing an element by it's index
	T const& operator () (size_t col, size_t row) const
	{
		return T[col*4 + row];
	}

	// operator for directly accessing the matrix
	T& operator [] (size_t col)
	{
		return m_[col];
	}
	
	// operator for directly accessing the matrix
	T const& operator [] (size_t col) const
	{
		return m_[col];
	}
private:
	T m_[16];
};

template<typename T>
Matrix4<T> operator * (Matrix4<T> const& A, Matrix4<T> const& B)
{
	return A * B;
}

} // namespace hrengin

#endif //_hrengin_Matrix4_
