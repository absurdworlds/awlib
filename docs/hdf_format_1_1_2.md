HDF version 1.1.2 format description
====================================

***

### Status of this document <a id="sec-status"/>
The purpose of this document is to provide reference for implementation of HDF format.

### Abstract
HDF (formerly HNDF) is a human-readable data serialization format, designed for use within 'hrengin' game engine. This document provides full information necessary to create and read HDF documents.

***

## Table of contents <a id="sec-toc"/>
1 [Introduction](#sec-introduction)
    1.1 [History](#sec-history)
    1.2 [Terminology](#sec-terminology)
    1.3 [Syntax notation](#sec-notation)
2 [Documents](#sec-documents)
    2.1 [Character set](#sec-charset)
    2.2 [Document layout](#sec-layout)
    2.3 [Objects](#sec-objects)
        2.3.1 [Node](#sec-node)
        2.3.2 [Value](#sec-value)
3 [Values](#sec-values)
    3.1 [Typing](#sec-typing)
        3.1.1 [Implicit typing](#sec-implicit)
        3.1.2 [Valid types](#sec-type-list)
3 [Commands](#sec-commands)

***

## 1  Introduction <a id="sec-introduction"/>

HDF (hrengin Data Format) is text-based data serialization format. It designed to be used specifically within 'hrengin' game engine.

The design for HDF goals are:
- human-friendliness;
- easy to process;
- no need for intermediate data structures;
- minimalistic and lightweight;

### 1.1  History <a id="sec-history"/>
The HDF format was not based on any other document format, although it was inspired by ZenGin Archive format (Gothic and Gothic II format for storing levels and serializing game objects).

- HNDF 1.1
    + the first revision
- HDF 1.1.1
    + use of array values (value = v1 v2 v3 v4) no longer allowed
    + removed separator characters
- HDF 1.1.2
    + reintroduced separator characters, which don't serve any syntactic purpose, but are intended to be used as readability characters

### 1.2 Termiology <a id="sec-terminology"/>
* stub *


 <a id="def-depth"/> **depth**: refers to a depth of an object in [`node`](#def-node) tree. Or, in simple terms, it refers to a number of [`nodes`](#def-node) containing given object.

### 1.3 Syntax notation <a id="sec-notation"/>
The notation used in this documents is based on EBNF. Each grammar rule defines a 'symbol' and expressed in form:

	symbol =:: rule

The following expressions are defining rules:

	'string'
or
	"string"
matches a string that is inside quote marks;
	[abc123]
matches any character inside brackets;
	[A-Z]
matches any character in range;
	^symbol
matches any symbol not matching a symbol;
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
	#symbol
form of `symbol` depends on the form of previous expression

## 2 Documents <a id="sec-documents"/>

###2.1 Character set <a id="sec-charset"/>
###2.2 Document layout <a id="sec-layout"/>
HDF document is composed of units referred here as 'objects', separated by white space.
	<a id="sym-document">[1]</a>	document ::= object+

###2.3 Objects <a id="sec-objects"/>
There are three types of objects: [`node`](#def-node), [`value`](#def-value) and [`command`](#def-command). `command` must have a [depth](#def-depth) of zero, and `value` must have a non-zero depth. `Nodes` may occur at any depth.
####2.3.1 Node <a id="sec-node"/>
####2.3.2 Value <a id="sec-value"/>
##3 Values <a id="sec-values"/>
###3.1 Typing <a id="sec-typing"/>
####3.1.1 Implicit typing <a id="sec-implicit"/>
####3.1.2 Valid types <a id="sec-type-list"/>
##4 Commands <a id="sec-commands"/>

