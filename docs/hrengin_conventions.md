hrengin Coding Conventions
==========================

## 1. Indentation style ##

Only tabulation characters should be used for indentation. One is 8 characters wide.

(Rationale: 8-character tabs make code easier to read)

Tabs should *never* be used for code alignment. Code should be aligned only by spaces, and *only on the same indentation level*. Spaces can follow indentation tabs, as long as two previous rules are properly met.

(Note: if followed properly, this will result in tabs not being mixed with spaces, and also will make code look alright if tabs are set to different width)

Now, with that cleared up, let's talk about indenting things.

Things that are indented: every block is indented by exactly one tab, except for namespace blocks (indenting namespaces will offset the code too far); class initializer lists are indented by one tab (relative to constructor declaration).

Things that are not indented: case labels are put on the same level with the `switch` statement; same for class access modifiers: `private`, `public` and `protected`.

Also, one should *never* put multiple statements on the same line. Same goes for variable declarations and variable assignments.

Lines should be limited by 80 columns (that's helpful even on large monitors, yes), and broken into multiple lines when that limit is exceeded (although it is OK to have slightly longer lines). Continuation lines should be indented by at least one tab, however, more tabs might be placed, if it helps to distinguish the lines.

If more then four levels of indentation are present, it means that function is too deply nested and should be split.

## 2. Braces placement ##

The K&R style is preferred. I.e. opening braces are put on the same line as their respective control statements, and closing braces are put on their own line, except when they are followed by a continuation of their control statement. In that case, keyword is put on the same line, after the closing brace.

Exception to that rule are functions: the opening braces are placed on the next line after function declaration, on the same indentation level.

E.g.

```
void functon (...)
{
	if (...) {
		...
	} else {
		...
	}
	...
}
```

Avoid putting excessive amount of empty lines. If body of a control statement consists of a single statement, don't put braces around it. Except for conditional statements, which have more than one branch.

```
	if (...)
		something();

	if (...) {
		...
		...
	} else {
		...
	}
```

## 3. Spaces ##

There are few rules about placing spaces. First, there should no space before ‘(’ in function calls and declarations (previously, I had spaces between name and ‘(’ in function declarations, but wise people convinced me that it is a dumb idea).

There should be no spaces inside parentheses, e.g. this is wrong:

```
	a = ( func( b ) + func( c, d ) );
```

Binary (and ternary) operators are written with one space to either side around them. Here's the list of them:

```
	=  +  -  *  /  %  <  >  <=  >=  ==  !=  |  &  ^  ?  :
```

Unary operators are written without space between them and their operand.

```
	&  *  +  -  ~  !
```

Same goes for keyword operators, and also they are written with parenthesized operands:

```
	sizeof(something)
```

But control statement keywords are written with a space after them:

```
	while  for  case  do  while
```

These member access operators, and namespace resolution operator are written with no spaces around operands:

```
	[]  .  ->  ::
```

Commas (and semicolons) are written with space after them, but not before them (just as in regular typography):

```
	for (int a, b; condition; ++a, ++b);
```

Also, there should be space between statement and opening curly brace:

```
	while (...) {
```

Lastly, always make sure that there is no trailing whitespace on the end of lines, including empty lines.

## 4. Naming ##

Names always should be descriptive, e.g. if a variable holds offset of current node, it should be called `cur_node`, not something like `b`. Also, short names are preferred over long names: `x` is enough to describe what it is, so `x_axis_coordinate` is not necessary.

Most names are written in mixed-case. Function (and method) names, local and member variable names all begin with lower-case letters. Class global variable and constant names begin with upper-case letters.

Also, private member variabes end with underscore:

	int private_;

Local variables aso can be written in lowercase, with words split by underscores.

### 4.1. Header guards ###

All header guards should have following format:

`_project_fileName_`

Where `project` refers to a whole product, not to a module or a IDE project file.


## 5. Types ##

Use types defined in include/common/types.h instead of `int`, `unsigned int`, `long` etc. Use `u8` (or `i8`) for 8-bit integer types and `char` for string types.

Last one is important: use *only* UTF-8 for handling strings (and UCS-4 when needed). *Never* use UTF-16, because it doesn't give any benefits and easy to misuse. So, again, use `char`, not `wchar_t`. Use `std::string`, not `std::wstring`.

## 6. Commenting ##

"/* ... */" style is preferred, although "//..." is OK to use for short single-line comments. Example of preferred style:

```
	/*
	 * Long comments should be written like this.
	 *
	 * Description:  A column of asterisks on the left side,
	 * with beginning and ending almost-blank lines.
	 *
	 * (I borrowed this description from Linux Kernel coding
	 * style guide :D)
	 */
```

