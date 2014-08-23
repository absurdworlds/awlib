
## HDF history
The HDF format was not based on any other document format, although it was inspired by ZenGin Archive format (Gothic and Gothic II format for storing levels and serializing game objects).

It was decided to call the format HNDF (hrengin Native Data Format), and the very first verison looked like this:

	document [
		typeid : HNDF
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
			var1 = float: 0.1
			length = int: 21 25 65
			variable3 = raw:0fff000000ffa00000ffcc00000
		] 
	]

This iteration had not met the design goals, and it was abandoned before it was implemented. The second iteration, HNDF 1.1 was implemented, although not fully.

	!hndf_version "1.1"
	[xyzzy
		[text
			responces = string: "responce1" "responce2" "responce3" "responce4"]
		[data
			dim = float: 0.1 0.8 0.1
			id = int: 21; type = int:1054
		]
	]

Although it was a major improvement from the previous iteration, it still was unsatisfactory: to avoid ambiguity when reading values, 'separators' were introduced, and it is also resulted in a dual purpose of line breaks: readability character and separator. 
This was a redundancy, so the format was revised into it's current form: HDF 1.1.1 (it was renamed, because the 'native' part was misleading). Multiple values were fordibben and separators were removed:

	!hdf_version "1.1.1"
	[xyzzy
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