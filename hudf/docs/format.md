# Version history
## 1.0
Had completely different syntax:
```
document [
	typeid : HDF
	version_major = 1
	version_minor = 0
	author = "USERNAME"
]:[ 
	chunk1 [
		typeid : TEXT
		]:[
		responces = string: "responce1" "responce2" "responce3" "responce4"
	] 
	
	chunk2 [ 
		typeid : DATA
	] : [ 
		var1 = float: 0.1 0.8 0.1
		length = int: 21
		type = int: 1054
		variable3 = raw:0fff000000ffa00000ffcc00000
	] 
]
```

It was never implemented, because it was too weird and cumbersome.

## 1.1
Cleaned-up version, looks a lot like modern versions, but has several major differences.

Firstly, it had different syntax for arrays: no `{}`, space-separated instead of comma-separated.
Secondly, because this syntax could make things ambiguous, values could be separated by `;` to disambiguate things.
```
!version "1.1"
[document
	[text
		responces = string: "responce1" "responce2" "responce3" "responce4"]
	[data
		dim = float: 0.1 0.8 0.1
		id = int: 21; type = int:1054
	]
]
```

### 1.1.1
Ditched the array syntax, left only fixed-size `vecX` arrays:
```
!version "1.1.1"
[document
	[text
		responce1 = string: "responce1"
		responce2 = string: "responce2"
		responce3 = string: "responce3"
		responce4 = string: "responce4"]
	[data
		dim = vec3: 0.1 0.8 0.1
		id = int: 21	 type = int:1054
	]
]
```
Also ditched semicolons.

### 1.1.2
Reintroduced semicolons which didn't serve any purpose (didn't affect parsing where they were allowed), but were kept for backward-compatibility and readability purposes.
```
!version "1.1.2"
[document
	[text
		responce1 = string: "responce1";
		responce2 = string: "responce2";
		responce3 = string: "responce3";
		responce4 = string: "responce4"]
	[data
		dim = vec3: 0.1 0.8 0.1
		id = int: 21	type = int:1054
	]
]
```
### 1.1.3
Added "node-values":
```
!version "1.1.3"
[document = "hdf"]
```

And then `enum` type:

```
!version "1.1.3"
[document
	type = hdf
	// or
	type = enum:hdf
]
```

## 1.2
Arrays were reintroduced with a new syntax. "Node-values" were ditched, `enum` type was ditched too (merged with `string`, now string supports both syntaxes).
```
!version "1.2"
[document
	[text
		responces = string: {"responce1", "responce2", "responce3", "responce4"}
	[data
		dim = float: {0.1, 0.8, 0.1}
		id = 21
		type = int:1054
	]
]
```

## 1.3
"Node-values" were reintroduced. An extra `,` is now allowed at the end of a vector.
```
!version "1.3"
[document
	[text
		responces = string: {"responce1", "responce2", "responce3", "responce4"}
	[data
		dim = float: {0.1, 0.8, 0.1, }
		id = 21
		type = int:1054
	]
	[node = value]
]
```
