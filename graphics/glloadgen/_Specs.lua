--[[ This module contains all of the spec-specific constructs (except where specs and styles overlap. That is, where styles have to do spec-specific work).

This module has a function called GetSpec which is given the spec name and returns a table containing functions/data that can be evaluated to do different jobs. This "class" contains:

- FilePrefix: nullary function that returns the filename prefix for this spec type.

- PlatformSetup: Takes a file and writes out platform-specific setup stuff.

- GetHeaderInit: Nullary function that returns a string to be written to the beginning of a header, just after the include guards.
]]

require "_util"

local gl_spec = {}
local wgl_spec = {}
local glx_spec = {}

local specTbl =
{
	gl = gl_spec,
	wgl = wgl_spec,
	glX = glx_spec,
}

-------------------------------------------------
-- Spec-specific functions.


---FilePrefix
function gl_spec.FilePrefix() return "gl_" end
function wgl_spec.FilePrefix() return "wgl_" end
function glx_spec.FilePrefix() return "glX_" end

--Include-guard string.
function gl_spec.GetIncludeGuardString() return "OPENGL" end
function wgl_spec.GetIncludeGuardString() return "WINDOWSGL" end
function glx_spec.GetIncludeGuardString() return "GLXWIN" end

--Header initialization.
function gl_spec.GetHeaderInit()
	return dofile(GetDataFilePath() .. "gl_specinit.lua")
end
function wgl_spec.GetHeaderInit()
	return dofile(GetDataFilePath() .. "wgl_specinit.lua")
end
function glx_spec.GetHeaderInit()
	return dofile(GetDataFilePath() .. "glx_specinit.lua")
end




--------------------------------------------------
-- Spec retrieval machinery
local function CopyTable(tbl)
	local ret = {}
	for key, value in pairs(tbl) do
		ret[key] = value
	end
	return ret
end

local function GetSpec(spec)
	local spec_tbl = specTbl[spec]
	assert(spec_tbl, "Unknown specification " .. spec)
	return CopyTable(spec_tbl)
end

return { GetSpec = GetSpec }
