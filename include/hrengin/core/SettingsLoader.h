/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_SettingsLoader_
#define _hrengin_SettingsLoader_
#include <string>

#include <hrengin/common/types.h>

#include <hrengin/core/core.h>
#include <hrengin/core/SettingsManager.h>

namespace hrengin {
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
} // namespace hrengin
#endif//_hrengin_SettingsLoader_
