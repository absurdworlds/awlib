#include "multi_vector.h"

int main()
{
	using namespace aw;
	multi_vector<int, float> vec;
	vec.create_storage(10);
	vec.destroy_storage();
}
