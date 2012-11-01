
local common = {}

--Iterates over all requested extensions
--Calls Extension(hFile, extName, spec, options)
common.extensions = 
{ type="group",
	{ type="ext-iter",
		{ type="write", name="Extension(hFile, extName, spec, options)", },
	},
}

--Iterates over every enumerator, in order:
-- Requested extension enums.
-- For each version:
--  Core extension enumerators from version X
--  Core enumerators from version X
-- Calls Enumerator(hFile, enum, enumTable, spec, options, enumSeen)
-- Optional small headers
common.enumerators =
{ type="group",
{ type="enum-seen",
	{ type="ext-iter",
		{type="enum-iter",
			{ type="write", name="SmallHeader(hFile, value, options)", value="Extension: %extName", first=true, optional=true},
			{ type="write", name="Enumerator(hFile, enum, enumTable, spec, options, enumSeen)", },
			{ type="blank", last=true },
		},
	},
	{ type="version-iter",
		{ type="core-ext-cull-iter",
			{type="enum-iter",
				{ type="write", name="SmallHeader(hFile, value, options)", value="Core Extension: %extName", first=true, optional=true},
				{ type="write", name="Enumerator(hFile, enum, enumTable, spec, options, enumSeen)", },
				{ type="blank", last=true },
			},
		},
		{type="enum-iter",
			{ type="write", name="SmallHeader(hFile, value, options)", value="Version: %version", first=true, optional=true},
			{ type="write", name="Enumerator(hFile, enum, enumTable, spec, options, enumSeen)", },
			{ type="blank", last=true },
		},
	},
},
}

--Iterates over each function, in order:
-- Requested extension functions.
-- For each version:
--  Core extensions from for version X
--  Core functions from version X
-- Calls Function(hFile, func, typemap, spec, options, funcSeen)
-- Optional small headers.
common.functions =
{ type="group",
{ type="func-seen",
	{ type="ext-iter",
		{type="func-iter",
			{ type="write", name="SmallHeader(hFile, value, options)", value="Extension: %extName", first=true, optional=true},
			{ type="write", name="Function(hFile, func, typemap, spec, options, funcSeen)", },
			{ type="blank", last=true },
		},
	},
	{ type="version-iter",
		{ type="core-ext-cull-iter",
			{type="func-iter",
				{ type="write", name="SmallHeader(hFile, value, options)", value="Extension: %extName", first=true, optional=true},
				{ type="write", name="Function(hFile, func, typemap, spec, options, funcSeen)", },
				{ type="blank", last=true },
			},
		},
		{type="func-iter",
			{ type="write", name="SmallHeader(hFile, value, options)", value="Extension: %version", first=true, optional=true},
			{ type="write", name="Function(hFile, func, typemap, spec, options, funcSeen)", },
			{ type="blank", last=true },
		},
	},
},
}

return common
