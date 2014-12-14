0) Notation
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

hrengin shall use *itd* as it's format for data collections. The name of format comes from a joke, which I will not list in here.

The purpose of *itd* is to provide basic means of tightly packing files together, and also to provide a skeleton for other archive formats.
It stores only minimal amount of data needed to extract a file: only it's offset and size. It doesn't store paths, file names and metadata. Instead, such facilities shall be extensions, and shall be stored as files inside *itd* archive.

Version 5 of this format is not backward-compatible with any of previous versions. Any following version shall be backward-compatible with all previous versions up to version 5.

### 1.1) Layout ###
*itd* has a very simple layout. An *itd* archive begins with a header, which consists of primary and secondary headers.
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

Exact format of secondary header is not specified in *itd* format. It's contents shall be defined by extensions.
There is one mandatory rule: secondary header starts with `u32` identifier, which must be different for each extension.
Secondary header may be up to 48 bytes long (64-byte offset - 16 byte primary header). Any unused field must be '0'.

	u32 id
	u8 [48] implementation-defined

#### 1.3) File table ####

Starts at 64-byte (`0x40`) offset. Each entry has following format:

	u64 offset
Offset from the biginning of archive file.

	u64 size
Size of file in bytes

Number of file entry is called 'file id'. File id are counted starting with 0.

#### 1.4) Files ####

Files are stored immediately after file table. Each file is stored immediately after previous. This, however, is only a guideline and not a technical limitation.

2) hrengin Package/Archive format (version 3)
---------------------------------------------

This is the first extension for *itd* format. It adds facilities to store file names, paths and metadata on top of *itd* format.

### 2.1) Header ###
It's *itd* secondary header has following definition:

	u32 id
Must be equal to `"hpka"`.

	u16 version
	u16 flags
See below, in section 2.1.1

	i64 ptime
Time in seconds since UNIX epoch at the moment of packaging.

#### 2.1.1) Flags ####
Following flags are defined:

	HPKA_HasFileTree 	::	BIT(1)
Defines whether file index is present. It is not necessarily in a form of tree, name is historical.

	HPKA_HasMetadata	::	BIT(2)
Defines, whether file metadata is present.

### 2.2) Special files ##
This extension defines 'special' files. Those are files, which are used to store file metadata and file index.
For the sake of simplicity, `file 0` is always file index, and `file 1` is always metadata. If one of those is not present, it's entry is left as '0'.

#### 2.2.1) File index ###
`file 0`
The purpose of file index is to provide file access by file names. It links file name to file id.

This file starts with `u32` code, specifying which type of index is used in this archive
Possible values (see more in section 2.3):

1. `tree` Directory tree. Each directory stored as a node which has a list of files, and list of child nodes.
2. `htre` Hashed tree. Same as `tree`, however, file names are hashed for faster access.
3. `list` Plain list. Stores file names as full paths.
4. `htbl` Same as list, with hased names.

#### 2.2.2) Metadata ###
`file 1`
The purpose of this file is to store additional metadata, such as file modification time.
Metadata is stored as 128-byte entries, number of which is equal to number of files in *itd* archive (see more in section 2.4).

### 2.3) File index description ##
First goes identifier, which tells the type of file index. After that goes 28-byte padding.

	u32 index_type
	u8 [28] padding

Regardless is type of the file index, each index has an array of strings at the end. This allows to make fixed-size structures, thus simplifying the reading.
Each string is null-terminated and has `u16` field describing it's size, preceding it.


All offsets are counted from the beginning of *index file* (`file 0`). 

#### 2.3.1) File list ###
File list is simplest type of index and consists of following entries:

	u64 path_ptr
Pointer (offset) to path string, containing file's full path.

	u64 file_id
ID of file in the file table

#### 2.3.2) Hash table ###
Hash table looks similar to file list, however, it is more complex.

First comes array of 'buckets', each containing pointer to list of files in that 'bucket'.

	u64 file_list_ptr
	u32 file_list_size

After the array comes the regular file list.

Entries are sorted in such way, that all files in a bucket have same hash value. Hash value computed using MurmurHash.
	
	hash = MurmurHash3(path, seed) % files_num

Seed is randomly-generated and placed inside padding before the index.

	u32 index_type
	u8 [12] padding
	u128 seed

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

List of files in directory has same format as plain file list, except that each file has pointer to it's name, not full path.

List of directories contains child nodes in the same format as the parent node.

File tree begins with nameless `root` node.

#### 2.3.4) Directory tree (hashed) ###
Same as regular directory tree, however, instead of list of files, each directory has a hash table, which works same way as described in 2.3.2.

### 2.4) Metadata entries ##

	i64 mtime
Data modification time

	i64 ctime
File creation time
