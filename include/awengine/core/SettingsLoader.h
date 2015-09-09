/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_SettingsLoader_
#define _awrts_SettingsLoader_
#include <string>

#include <awrts/common/types.h>

#include <awrts/core/core.h>
#include <awrts/core/SettingsManager.h>

namespace awrts {
namespace core {
class SettingsManager;
/*!
 * Helper class to load settings from a known file format
 */
class SettingsLoader {
public:
	//! Virtual destructor
	virtual ~SettingsLoader()
	{
	}

	/*!
	 * Load settings and transfer them to \a manager
	 * \param manager Settings manager which will store settings.
	 */
	virtual void loadSettings() = 0;
};

} // namespace core
} // namespace awrts
#endif//_awrts_SettingsLoader_
