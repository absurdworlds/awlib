package.path = package.path .. ";./SLAXML/?.lua"
local slaxml = require "slaxml"

local data = nil

local function InitData()
	data = {}
	function data:PushChildElement(name, nsURI)
		local elem = {}
		elem._elem = name
		elem._ns = nsURI

		if(not self._curr) then
			self._stack = {}
			self._top = 0

			self._root = elem
		end

		self._stack[self._top + 1] = elem
		
		if(self._stack[self._top]) then
			table.insert(self._stack[self._top], elem)
		end
		
		self._top = self._top + 1
		self._curr = elem
	end
	
	function data:AddText(text)
		--Ignore stuff before/after the root.
		if(self._curr) then
			--if(text:match("%S")) then
				table.insert(self._curr, text)
			--end
		end
	end
	
	function data:AddComment(comment)
		local node = {}
		node._comment = comment
		
		--Ignore stuff before/after the root.
		if(self._curr) then
			table.insert(self._curr, node)
		end
	end
	
	function data:PopChildElement(name, nsURI)
		assert(self._curr)
		
		if(name ~= self._curr._elem) then
			self._errors = self._errors or {}
			table.insert(self._errors, "Element name mismatch: " .. name)
		end

		self._stack[self._top] = nil
		self._top = self._top - 1
		self._curr = self._stack[self._top]
	end
	
	function data:Top()
		assert(self._curr)
		return self._curr
	end
	
	function data:GetAll()
		return self._root, self._errors
	end
end

local builder = {}

function builder.startElement(name, nsURI)
	data:PushChildElement(name, nsURI)
end

function builder.closeElement(name, nsURI)
	data:PopChildElement(name, nsURI)
end

function builder.attribute(name, value, nsURI)
	assert(data:Top()[name] == nil, "Multiply-defined attribute " .. name)
	data:Top()[name] = value
end

function builder.text(text)
	data:AddText(text)
end

function builder.comment(content)
	data:AddComment(content)
end

function builder.pi(target, content)
end


local ret = {}

function ret.LoadXml(filename)
	local xml_string
	do
		local hFile = io.open(filename)
		assert(hFile, "Couldn't find file " .. filename)
		xml_string = hFile:read("*a")
		hFile:close()
	end

	InitData()
	
	local parser = slaxml:parser(builder)
	parser:parse(xml_string, {stripWhitespace=false})
	
	return data:GetAll()
end

return ret