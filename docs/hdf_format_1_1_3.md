HDF version 1.1.3 format description
====================================

***

### Status of this document <a name="sec-status"/>
The purpose of this document is to provide reference for implementation of HDF format.

*NOTE: This document is unfinished*

### Abstract
HDF (formerly HNDF) is a human-readable data serialization format, designed for use within 'hrengin' game engine. This document provides full information necessary to create and read HDF documents.

***

## Table of contents <a name="sec-toc"/>
1. [Introduction](#sec-introduction)  
    1.1. [History](#sec-history)  
    1.2. [Terminology](#sec-terminology)  
    1.3. [Syntax notation](#sec-notation)  
2. [Documents](#sec-documents)  
    2.1. [Character set](#sec-charset)    
    2.2. [Document layout](#sec-layout)  
    2.3. [Objects](#sec-objects)  
        2.3.1. [Node](#sec-node)  
        2.3.2. [Value](#sec-value)  
3. [Values](#sec-values)  
    3.1 [Typing](#sec-typing)  
        3.1.1. [Implicit typing](#sec-implicit)  
        3.1.2. [Valid types](#sec-type-list)  
4. [Commands](#sec-commands)

***

## 1  Introduction <a name="sec-introduction"/>

HDF (hrengin Data Format) is text-based data serialization format. It designed to be used specifically within 'hrengin' game engine.

The design for HDF goals are:
- human-friendliness;
- easy to process;
- no need for intermediate data structures;
- minimalistic and lightweight;

### 1.1  History <a name="sec-history"/>
The HDF format was not based on any other document format, although it was inspired by ZenGin Archive format (Gothic and Gothic II format for storing levels and serializing game objects), INI format, Dwarf Fortress Raws and Lisp.

- HNDF 1.1
    + the first revision
- HDF 1.1.1
    + use of array values (value = v1 v2 v3 v4) no longer allowed
    + removed separator characters
- HDF 1.1.2
    + reintroduced separator characters, which don't serve any syntactic purpose, but are intended to be used as readability characters
- HDF 1.1.3
    + added node-values, alternative form for values: `[node-value = string:"val"]`
    + introduced command `!version`, deprecated `!hdf_version` and `!hndf_version`
    + added `enum` type

### 1.2 Termiology <a name="sec-terminology"/>
*stub*


 <a name="def-depth"/> **depth**: refers to a depth of an object in [`node`](#def-node) tree. Or, in simple terms, it refers to a number of [`nodes`](#def-node) containing given object.

### 1.3 Syntax notation <a name="sec-notation"/>
The notation used in this documents is based on EBNF. Each grammar rule defines a 'symbol' and expressed in form:

	symbol =:: rule

The following expressions are defining rules:

	'string'
or
	"string"
matches a string that is inside quote marks;
	#N
matches a character whose number in ISO/IEC 10646 equal to `N`, where `N` is a hexadecimal integer.
	[abc123]
matches any character inside brackets;
	[A-Z]
matches any character in range;
	^symbol
matches any symbol not matching a symbol;
	A - B
matches a symbol matching A, but not B;
	(symbol)
`symbol` is treated as a single expression;
	symbol?
is a single 'symbol' or nothing;
	symbol*
is zero or more `symbol`s;
	symbol+
is one or more `symbol`s;
	symbol1 symbol2
is a `symbol1` followed by `symbol2`;
	symbol1 | symbol2
is a `symbol1` or a `symbol2`.

One last expression, used only to define `value`. 
	@symbol{A}
form of `symbol` depends on the form of expression A

## 2 Documents <a name="sec-documents"/>

###2.1 Characters <a name="sec-charset"/>
HDF uses ASCII character set. It allows to use UTF-8 in [`strings`](#def-string).

####2.1.1 Names
	[1] name ::= name_first name_char*

	[2] name-begin ::= [A-Z] | [a-z]

	[3] name-char ::= [A-Z] | [a-z] | '-' | '_'

####2.1.2 White space
White space consists of one or more spaces, tabs or line breaks.

	[4] line-break ::= #A | (#A #D)

	[5] ws-char ::= #x9 | #x20

	[6] ws ::= (ws_char | line_break)+

For convenience in describing tokens, which must be written in single line, `inline white space` is introduced. 
Inline white space is white space without line breaks.

	[7] sp ::= ws_char+
	
####2.1.3 Numbers
	[8] number = sign? integer fraction? exponent?

	[9] sign = '+' | '-'

	[10] digit = [0-9]

	[11] integer = digit+

	[12] fraction = '.' digit+

	[13] exponent = [Ee] sign? digit+

####2.1.4 Strings
`string` is a sequence of characters, delimited by quote marks:

	string ::= '"' char* '"'

###2.2 Document layout <a name="sec-layout"/>
HDF document is composed of units referred here as 'objects', separated by white space.
	<a name="sym-document">[14]</a>	document ::= (object - value)+

###2.3 Objects <a name="sec-objects"/>
There are three types of objects: [`node`](#def-node), [`value`](#def-value) and [`command`](#def-command). `command` must have a [depth](#def-depth) of zero, and `value` must have a non-zero depth. `Nodes` may occur at any depth.

	object ::= node | value | command

####2.3.1 Node <a name="sec-node"/>
Node is a main markup unit of a HDF document. Node may contain values or other nodes.

	node	::=	node_start node-object* node_end
	node-object ::= object - command

Node starts with '[' followed by the name of this node, and ends with ']'. Name of a node is not necessary unique, and may repeat indefinitely.

	node-start ::= '[' name ws
	node-end ::= ws? ']' ws?

####2.3.2 Value <a name="sec-value"/>
Values are used to store actual data. As described above, they must be contained within a node.

	value ::= name sp? = sp? type? sp? @data{type}

Unlike nodes, name of a value must be unique. This rule may be neglected when implementing a program, however, it is strongly avised to follow this rule when constructing HDF documents.

##3 Values <a name="sec-values"/>
###3.1 Typing <a name="sec-typing"/>
 <a name="def-type"/> `type` defines representation of variable and set of possible values which it can posess.
 
 <a name="def-type-lable"/> `type label` is used to identify type of value.

In HDF, types are prefixed to data in form of `name` followed by `:` symbol.

	type ::= name sp? ':'

####3.1.1 Implicit typing <a name="sec-implicit"/>
####3.1.2 Valid types <a name="sec-type-list"/>
In HDF there are several defined types:

- `string` represents a sequence of characters

	type labels: `string`, `s`
	data{string} ::= '"' ucs_char+ '"'

- `boolean` represents a true/false boolean value

	type labels: `bool`, `b`
	data{boolean} ::= sign? ('true'|'false')

- `enum` represents a enumerated value

	type labels: `enum`, `e`
	data{enum} ::= name

- `integer` represents an integral value

	type labels: `int`, `i`
	data{integer} ::= sign? integer

- `float` represents a IEEE 754 floating point value

	type labels: `float`, `f`
	data{integer} ::= number

- `vector2` represents a pair of floats

	type labels: `vec2`, `v2`
	data{vector2} ::= number sp number

- `vector3` represents an array of three floats

	type labels: `vec3`, `v3`
	data{vector3} ::= number sp number sp number

- `vector4` represents an array of four floats

	type labels: `vec4`, `v4`
	data{vector4} ::= number sp number sp number sp number

##4 Commands <a name="sec-commands"/>
###4.1 `version`
As the name implies, this command defines which version of HDF the document is written in.

This command is used in the following format:

	!version 113
