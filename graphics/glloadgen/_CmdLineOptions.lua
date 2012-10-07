--[[ The function CmdLineOptions takes the command-line options and processes them according to a series of functions it is given. It can handle any options of the standard forms, such as:

- "-optName param"
- "--optName option1 option2 option3"
- "-optName=param"

It takes the following parameters:
- An array of command-line options as strings.
- A table of functions, where the key name matches the options. Note that the match will be case-sensitive.
- A value to be passed to the functions. This allows them to be a bit more independent without having to use upvalue tricks.

The return value is a list of any positional arguments, in order.

The option processor functions take the following parameters:
- The value to be passed to the processor. A candidate for a `self` parameter.
- The first parameter string of the option, if any.
- A nullary iterator function to iterate over all of the options associated with the command. It can have 0 iterations. It is OK to iterate multiple times. The iterator returns two values: the parameter and the parameter's 1-base index.

The return value from the processing function is the number of options processed. If `nil` is returned, then it is assumed that *all* available options were processed.

The processor functions are called within a `pcall`, so any errors will be assumed to be processing errors related to that option. Appropriate error messages will be emitted mentioning the option name, so it doesn't need to keep its own name. It is up to each processor to decide if it has enough or too many parameters and error out if it does. Processing of command line options will error if there is a failure.

The processor assumes that strings that begin with a `-` character is an option. If a parameter is specified with the `-option=param` syntax, then it is assumed to have exactly one parameter. Thus the next value is assumed to be an option. For all other option formats, the number of processed arguments is decided upon by the processing function. If it returns `nil`, then it assumes all arguments were processed.

Any "options" that do not conform to option syntax are assumed to be positional arguments. They are stored in an array and returned by the function.
]]

--Returns nil if not an option. Otherwise returns the option and a possible
--parameter name if it is of the form "--option=foo".
local function GetOptionName(option)
	local option, param = string.match(option, "^%-%-?([^%-%=][^%=]*)%=?(.*)")
	if(param and #param == 0) then
		param = nil
	end
	
	return option, param
end

--Returns a nullary function that iterates over a single parameter. Namely, this one.
local function GetParamIterator(param)
	return function()
		return function(s, var)
			if(var) then
				return nil, nil
			else
				return param, 1
			end
		end, nil, nil
	end
end

--Returns a nullary function that iterates over all parameters from the given
--index to the next option.
local function GetParamListIterator(params, startIx)
	return function()
		local state = {startIx}
		return function(state, var)
			--Stop if out of parameters
			if(state[1] > #params) then
				return nil
			end
			
			--Stop if the parameter is an option name.
			if(GetOptionName(params[state[1]])) then
				return nil
			end
			
			state[1] = state[1] + 1
			return params[state[1] - 1], state[1] - startIx
		end, state, nil
	end
end

local function CountNumOptions(iter)
	local numOpts = 0
	for _ in iter() do
		numOpts = numOpts + 1
	end
	return numOpts
end

local function CallProcessor(func, option, value, param, iter)
	local status, nargs = pcall(func, value, param, iter)
	if(not status) then
		error("The option " .. option .. "' had an error:\n" .. nargs)
	end
	
	return nargs or CountNumOptions(iter)
end

function CmdLineOptions(cmd_line, processors, value)
	local posArgs = {}
	local optIx = 1
	local numOpts = #cmd_line
	while(optIx <= numOpts) do
		local option, param = GetOptionName(cmd_line[optIx])
		
		if(not option) then
			posArgs[#posArgs + 1] = cmd_line[optIx]
			optIx = optIx + 1
		else
			assert(processors[option], "The option '" .. option .. "' is not a valid option for this program.")
			
			if(param) then
				CallProcessor(processors[option], option, value,
					param, GetParamIterator(param))
			else
				local paramIter = GetParamListIterator(cmd_line, optIx + 1)
				local numOpts = CountNumOptions(paramIter)
				if(numOpts > 0) then
					param = cmd_line[optIx + 1]
				end
				local nargs = CallProcessor(processors[option], option, value,
					param, paramIter)
				
				optIx = optIx + nargs
				
			end
			optIx = optIx + 1
		end
	end
	
	return posArgs
end




