
## Version 2.0.3
* Supports OpenGL 4.5 and recent extensions.
* Adds `-geninfo` option, for creating comments in generated files about how it was generated.
* Issue #50 fixed: LFS file loading.
* Issue #29 fixed: Errors in MacOSX compilation.
* Issue #61 fixed: 
* Fixed IsVersionGEQ bug in multiple styles.
* Issued #59 fixed: Working directory can be something other than the glLoadGen directory.
* C-based styles now conform to C expectations in comments and empty parameter lists.

## Version 1.0:
* New Noload loader. Works like GLee.
* -stdext now works relative to the extfiles directory, not just LoadGen. So no need to do -stdext=extfiles/gl_name_of_standard_file.txt.
* A test suite.
* Lua Filesystem is now in use; if it's not available, then you must create the destination directory yourself.

## Version 0.3:
* Replaced the old generation system with a flexible structure system.
* Migrated the styles to the structure system.
 