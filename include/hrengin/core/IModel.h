#ifndef __HRENGIN_IModel_H__
#define __HRENGIN_IModel_H__

#include <vector>
#include <hrengin/core/hrenginmodels.h>


namespace hrengin {

class IModel
{
public:
	std::vector<SPrimitive> primitives;
};

}

#endif//__HRENGIN_IMesh_H__