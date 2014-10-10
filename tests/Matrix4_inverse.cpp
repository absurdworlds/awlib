
#include <hrengin/common/Matrix4.h>

void main ()
{
	Matrix4<double> A(
		1,2,3,4,
		5,6,7,8,
		9,1,1,2,
		3,4,5,1);
		
	Matrix4<double> B;

	giga.getInverse(B);

	Matrix4<double> I = A * B;
}