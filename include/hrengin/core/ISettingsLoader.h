/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISettingsLoader_
#define _hrengin_ISettingsLoader_
#include <string>

#include <hrengin/common/types.h>

#include <hrengin/core/core.h>

namespace hrengin {
namespace core {
class ISettingsManager;
/*!
 * Helper class to load settings from known file format
 */
class ISettingsLoader {
public:
	//! Virtual destructor
	virtual ~ISettingsLoader()
	{
	}

	/*!
	 * Load settings and transfer them to \a manager
	 * \param manager Settings manager which will store settings.
	 */
	virtual void loadSettings(ISettingsManager & manager) = 0;
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_ISettingsLoader_
