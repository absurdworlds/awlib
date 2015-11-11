0. Notation
-----------
Following notation is used for specifying data types:

	uXX

XX-bit sized unsigned integer.

	iXX

XX-bit signed integer.

	yY[N]
N values of type *yY*.

All values are little-endian.
	
	BIT(X)
Value has bit X (counting from lest significant bit, starting from 1) toggled on, with rest of bits toggled off.

1) itd archive format (version 5)
---------------------------------

*itd* is a very simple format, which supports a very small amount of fetures. The name “itd” comes from a joke, which I am not going to tell here.

The purpose of *itd* is to provide basic means of tightly packing files together, and also to provide a skeleton for other archive formats.

It stores only minimal amount of data needed to extract a file: only file offset and size. It does not store paths, file names and metadata.
Instead, such facilities shall be provided by extended formats built on top of *itd*, and additional data shall be stored as regular files inside *itd* archive.

Version 5 of this format is not backward-compatible with any of previous versions. Any following version shall be backward-compatible with all previous versions up to version 5.

### 1.1) Layout ###
*itd* has a very simple layout. An *itd* archive begins with a header, which consists of primary header and secondary header.
At 64 byte offset begins the file list. Each entry in the list is 16 bytes long and stores offset and size of each file.
Immediately following the file table are files themselves, each written one right after another.

#### 1.2) Header ####
Header is split into two headers: main (primary) header and optional secondary header.

**1.2.1) Primary header**:

	u32 id
File identifier. Must always be equal to `".itd"`, stored as an little-endian integer, where firstmost character corresponds to the least significant byte.

	u16 version
Format version.

	u16 flags
Reserved, must be 0.

	u64 numFiles
Number of file entries in the file table

**1.2.2) Secondary header:**

Exact format of secondary header is not specified in *itd* format. Its contents shall be defined by extensions.
There is one mandatory rule: secondary header starts with `u32` identifier, which must be different for each extension.
Secondary header may be up to 48 bytes long (64-byte offset - 16 byte primary header). Any unused field must be '0'.

	u32 id
	u8 [44] implementation-defined

#### 1.3) File table ####

Starts at 64-byte (`0x40`) offset. Each entry has following format:

	u64 offset
Offset from the biginning of archive file.

	u64 size
Size of file in bytes

Number of file entry is called 'file id'. File id are counted starting with 0.

#### 1.4) Files ####

Files are stored immediately after file table. Each file is stored immediately after previous. This, however, is only a guideline and not a technical limitation.

2) hrengin Package/Archive format (version 5)
---------------------------------------------

This is the first extension for *itd* format. It adds facilities to store file names, paths and metadata on top of *itd* format.

### 2.1) Header ###
Its *itd* secondary header has following definition:

	u32 id
Must be equal to `"hpka"`.

	u16 version
	u16 flags
See below, in section 2.1.1

	i64 ptime
Time in seconds since UNIX epoch at the moment of packaging.

#### 2.1.1) Flags ####
Following flags are defined:

	HPKA::HashedFileNames	:=	BIT(1)
Defines whether files accessed by hash, or just by iterating through file names.

### 2.2) Special files ##
This extension defines 'special' files. Those are files, which are used to store file metadata and file index.

`file 0` and `file 1` are always used to store file index. They may index different sets of files.

`file 2` is reserved for metadata. 

If one of those is not present, corresponding entry has size and offset of “0”.

#### 2.2.1) File index ###
`file 0` and `file 1`
The purpose of file index to provide a way to retrieve file indices by file names. In other words links file name to file index.

**`file 0`** is a plain file list. It stores file names as full paths.

If `HPKA::HashedFileNames` flag is on, file names are hashed.

**`file 1`** is a directory tree. Each directory stored as a node which has a list of files, and list of child nodes.

If `HPKA::HashedFileNames` flag is on, file names are hashed, but directory names aren't.

#### 2.2.2) Metadata ###
`file 2`
The purpose of this file is to store additional metadata, such as file modification time.
Metadata is stored as 128-byte entries, number of which is equal to number of files in *itd* archive (see more in section 2.4).

### 2.3) File index description ##
All offsets are counted from the beginning of *index file* (`file 0` or `file 1`).

#### 2.3.1) File list ###
File list is simplest type of index. It starts with a number of files in the list:

	u64 files_num

And the rest file table consists of entries in the following format

	u64 path_ptr
Pointer (offset) to path string, containing file's full path.

	u64 file_id
ID of file in the file table.


In order to find a file, user has to iterate through the list, comparing path of each file. 

#### 2.3.2) File list (hashed) ###
If `HPKA::HashedFileNames` flag is on, then file list has a bit different format:

In addition to `file_num`, it includes a hash seed:

	u64 files_num
	u128 seed

Seed is used for computing the hash. Generated randomly at time of packaging.

Next comes array of “buckets”. Each bucket has a pointer to the list of files in that “bucket”.

	u64 file_list_ptr
	u64 file_list_size

After the array comes the regular file list.

Entries are sorted in such way, that all files in a bucket have same hash value.

In order to find a file in index, hash value is computed using MurmurHash.
	
	hash = MurmurHash3(path, seed) % files_num

Afterwards, user must iterate through entries in a bucket, like through regular file list.

#### 2.3.3) Directory tree ###
Directory tree consists of directory nodes

	u64 name_ptr
Pointer to string, containing directory name.

	u64 files_ptr
Pointer to list of files in directory

	u32 files_size
Number of files in directory

	u64 subtree_ptr
Pointer to list child nodes

	u32 subtree_size
Number of children

List of files in directory has same format as plain file list, except that each file has a `name_ptr` instead of pointer to full path `path_ptr`.

	u64 name_ptr
	u64 file_id

List of directories consists of child nodes, which have same format as the parent node.

Directory tree begins with a nameless `root` node.

	u64 files_ptr
	u32 files_num
	u64 subtree_ptr
	u32 subtree_num

#### 2.3.4) Directory tree (hashed) ###
Same as regular directory tree, however, instead of list of files, each directory points to a hash table, which works same way as described in 2.3.2.

Directory tree begins with a root node, and also contains `seed` for computing the hash.

	u64 files_ptr
	u64 files_num
	u64 subtree_ptr
	u32 subtree_num
	u128 seed

#### 2.3.5) Strings ####
Both `file 0` and `file 1` have an array of string at the end. Those are the strings referred by `name_ptr` and `path_ptr`.

Each string is null-terminated and has `u16` “size” field preceding it. This allows to make fixed-size structures, making it much easier to iterate through lists.


### 2.4) Metadata entries ##

	i64 mtime
Data modification time

	i64 ctime
File creation time
