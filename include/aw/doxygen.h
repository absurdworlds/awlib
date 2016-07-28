/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

/* -------------------------------------------------------- */

/*!
 * \defgroup traits Traits
 *
 * Provides various traits and template metaprogramming facilities.
 *
 */

/*!
 * \defgroup logging Loggers
 *
 * Logging facilities.
 */

/*!
 * \brief
 * Primary namespace. Contains everything else.
 */
namespace aw {
/*!
 * \brief
 * Contains miscellaneous helpers and utilities.
 */
namespace utils {}

/*!
 * \brief
 * String manipulation utilities.
 */
namespace string {}

/*!
 * \brief
 * AW serialization library.
 */
namespace arc {}

/*!
 * \brief
 * Game GUI toolkit.
 */
namespace gui {}

/*!
 * \brief
 * HDF parser & writer library.
 */
namespace hdf {}

/*!
 * \brief
 * itd/awpk archive format packer and unpacker
 */
namespace itd {}

/*!
 * \brief
 * Tools for file & console io
 */
namespace io {}

/*!
 * \ingroup logging
 * \brief
 * Interfaces/tools for logging.
 */
inline namespace log {}

/*!
 * \brief
 * Containts various mathematical and numeric functions.
 */
namespace math {}

/*!
 * \brief
 * Wrapper for physics library
 */
namespace physics {}

/*!
 * \brief
 * Wrappers for different OS APIs
 */
namespace platform {}

/*!
 * \brief
 * AW signals and slots library.
 */
namespace signals {}

/*!
 * \brief
 * AW 3D audio library
 */
namespace sound {}

} // namespace aw
