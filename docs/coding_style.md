This file is work in progress.


## Naming conventions

`snake_case` is preferred for all identifiers, except for template parameters: use `PascalCase` in that case.

There might be older code, which uses typical OO conventions (`PascalCase` for classes, `camelCase` for everything else, `camelCase` or `snake_case` for local variables). I still haven't decided if I want to convert it (although there is some partially converted code).

Any name beginning with `aw_` prefix is reserved for macros.

Hungarian notation is forbidden. This also applies to class prefixes: 'ISomeInterface', 'CImplementation', 'EAnEnumeration'.

### Class members

Any prefix/suffix denoting that a variable is a member is forbidden. I.e. `m_size` `data_m` are forbidden names, unless `m` here means something different than `member`, for example "map size" or "data №M" (although such names are discouraged in favor of more informative ones).

The only allowed prefix is underscore: `_size`. Underscore suffix is not allowed.


## Braces

Braces are placed on the same line with corresponding statement.
Except: for functions, braces are placed on the *next* line (with exception of lambdas):

Opening brace is preceded by a space, when it is not at the beginning of the line.

```

int func()
{
	if (block) {
		auto x = [] {
			return 0;
		};
		return x();
	}
	return 0;
}

```

## Whitespace

There are few rules regarding whitespace.

### Indentation

*Only* tabulation is used for indentation. (*Rationale:* allows reader to configure indentation width)

(I use 8-space-wide tabs, because I find such code easier to read and because it discourages deeply nested code.)

### Alignment

As opposed to indentation, only *spaces* are used for alignment. Aligning things on different indentation levels is forbidden. (*Rationale:* keeps code alignment independent of tab size).

Tabs are allowed **only** at the beginning of the line, and there must be no spaces touching any tabulation character.

### Examples

```

// valid
	memory        = nullptr;
	cache_size    = 10000;
	ptr_to_memory = &memory;

// invalid
        int var1;
	int var2;

// invalid
        if (x) {
                int y = *x;

// invalid
	if (auto x    = func()) {
		int y = *x;

// invalid
	int x		= 0;
	int cache_size	= 10;

```

### Things that are indented

All blocks are indented by one tab (unless they are inline), except namespace blocks. Namespace blocks are *never* indented.


```
namespace aw {
namespace example {
struct X {
	int x;
};
struct Y { int y };

enum class Z {
	A,
	B,
	C
};

void func()
{
	if (something) {
		whatever();
	}
}
} // namespace example
} // namespace aw

```

Class access modifiers and switch labels are *not* indented:

```
	switch (x) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	};
	class x {
		static int x;
	public:
		int y;
	protected:
		int z;
	private:
		int w;
	};

```

Class initializer lists are also indented by a single tab:


```

aclass::aclass(istream& stream)
	: stream{stream}
{
}

```

### Spaces inside statements


There should be no space between `(` and function name. Function should never be torn apart from it's parenthesis.

On the other hand, parenthesis in control flow statements should always be separated from keyword.


```

func(x);
if (x) { }
while (y) { }

```

That's the only rule. For everthing else — whatever looks better and more readable.

## Include guards
Names of public header include guards are constructed as follows:

`aw_` `path_to_header` `_` `header_name` `_h`

Names of guards for internal (module-specific) headers are constructed same way, except that path is replaced by "internal":

`aw_internal_` `header_name` `_h`

## Include order
Header corresponding to source (.c++) file must be the first header included in said source file. (*Rationale:* allows to prove that header does not have any unknown dependencies)

Other headers are included in following order:

1. System headers
2. Standard library headers
3. External library headers
4. Headers belonging to other modules
5. Other headers of same module

This rule, however is not enforced. Reverse order (5,4,3,2,1) is also acceptable.

Headers belonging to same library/module should be grouped together.

For tests, `aw/utility/test.h` should be always the last header.

## Namespaces
Line with namespace's closing brace should end with a comment containing name of the namespace:
```
} // namespace aw
```
