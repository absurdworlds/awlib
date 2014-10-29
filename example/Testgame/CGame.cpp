/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/common/time.h>

#include "CGame.h"

namespace hrengin {
namespace example {

CGame::CGame ()
	: settings_(core::getSettingsManager())
{
	ILogger* logger_ = createLogger();
}

CGame::~CGame ()
{
	delete logger_;
}

bool CGame::run ()
{
	bool runEngine = true;

	hrengin::u32 time = hrengin::getTime();
	hrengin::u32 lastTime;
	
	// Here I show how I implement my game loop.
	do {
		lastTime = time;
		time = hrengin::getTime();
	}
	while(runEngine);

	return runEngine;
}

void CGame::loadSettings ()
{
	settings_.loadSettings();
}
} // namespace example
} // namespace hrengin
