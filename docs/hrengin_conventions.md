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

Lines should be limited by 80 columns (that's helpful even on large monitors, yes), and broken into multiple lines when that limit is exceeded. Continuation lines should be indented by at least one tab, however, more tabs might be placed, if it helps to distinguish the lines.

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

Avoid putting excessive mount of empty lines. If body of a control statement consists of a single statement, don't put braces around it. Except for conditional statements, which have more than one branch.

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
