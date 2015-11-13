#include <stdio.h>
#include <utility>

#include <awengine/string/compose.h>

int main (int c, char** a)
{
	using namespace awrts::string;

	if (c < 3) {
		return 1;
	}

	std::string fmt = a[1];
	std::string tst;
	c -= 2;

	switch(c) {
	case 1:
		tst = compose(fmt, a[2]);
		break;
	case 2:
		tst = compose(fmt, a[2], a[3]);
		break;
	case 3:
		tst = compose(fmt, a[2], a[3], a[4]);
		break;
	case 4:
		tst = compose(fmt, a[2], a[3], a[4], a[5]);
		break;
	case 5:
		tst = compose(fmt, a[2], a[3], a[4], a[5], a[6]);
		break;
	case 6:
		tst = compose(fmt, a[2], a[3], a[4], a[5], a[6], a[7]);
		break;
	case 7:
		tst = compose(fmt, a[2], a[3], a[4], a[5], a[6], a[7], a[8]);
		break;
	default:
	case 8:
		tst = compose(fmt, a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
		break;
	}

	printf("%s\n", tst.c_str());
	return 1;
}
