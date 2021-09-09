# AW coding guidelines

## Naming & Formatting
### Namespaces
1. Namespaces are not indented.
2. It is recommended to use single-word names for namespaces.

## Coding guidelines
### Implicit type conversions
#### Conversion to bool

It is not allowed to use implicit conversion to bool for integer and floating point types (or any "number" type for that matter).

    	int i = calculate();
    	if (i) { // NOT ALLOWED, use i != 0 instead
    		...
    	}

Not required, but recommended to use `!= nullptr` for checking pointers.
