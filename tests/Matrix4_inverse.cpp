
#include <hrengin/math/Matrix4.h>

void main ()
{
	hrengin::Matrix4<double> A(
		1,2,3,4,
		5,6,7,8,
		9,1,1,2,
		3,4,5,1);
		
	hrengin::Matrix4<double> B;

	A.getInverse(B);

	hrengin::Matrix4<double> I = A * B;
}
