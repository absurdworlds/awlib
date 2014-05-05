
#ifndef __HR_C_UNIT__
#define __HR_C_UNIT__

#include <hriUnit.h>
#include <hriModel.h>
#include <hriNavAgent.h>
#include <hrtVector2d.h>

namespace hrengin
{
	class hrcUnit : public hriUnit
	{
	public:
		hrcUnit(graphics::hriModel* Model) {};
		hrcUnit(hriUnit& Unit) {};
		virtual ~hrcUnit() {};

	private:
		graphics::hriModel* Model;
		ai::hriNavAgent* Agent;
		vectorf2d positon;
	};
}

#endif __HR_C_UNIT__
