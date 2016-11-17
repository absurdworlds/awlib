/*
 * Copyright (C) 2016  Spectre, Hedede
 *
 * License — WTFPL
 */
#include "smb_format.h"
#include <aw/types/array_view.h>

namespace aw {
namespace smb {

void load_mesh( aw::io::input_stream& file )
{
	rModelFormat model;
	model.Load( file );

}

} // namespace smb
} // namespace aw
