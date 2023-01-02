# Printf

A personal implementation of the printf function in C. Because why not, it's fun.

## Usage

To use the printf function, include the printf.h header file in your source code and call the function with a format string and any additional arguments for the format specifiers:

``` c
#include "printf.h"

int main(void) {
    int count = ft_printf("%d bottles of beer on the wall.\n", 99);
    return 0;
}
```

The printf function returns the number of characters printed.

## Supported format specifiers

The following format specifiers are supported:

- %c: character
- %s: string
- %p: pointer address
- %d and %i: signed integer
- %u: unsigned integer
- %x: unsigned integer as a hexadecimal number (using lowercase letters)
- %X: unsigned integer as a hexadecimal number (using uppercase letters)

## Flags

The following flags are supported:

- -: left justify the output within the specified field width
- 0: pad with leading zeros rather than spaces
- +: include a plus sign for positive numbers
- (space): include a space for positive numbers
- #: include a leading 0 for octal numbers (%p, %x, %X) or a leading 0x for hexadecimal numbers (%p, %x, %X)
Field width and precision can also be specified for the output.

**Example**

``` c
#include "printf.h"

int main(void) {
    ft_printf("%d bottles of beer on the wall.\n", 99);
    ft_printf("%05d bottles of beer on the wall.\n", 99);
    ft_printf("%-5d bottles of beer on the wall.\n", 99);
    ft_printf("%+d bottles of beer on the wall.\n", 99);
    ft_printf("% d bottles of beer on the wall.\n", 99);
    ft_printf("%#x bottles of beer on the wall.\n", 99);
    return 0;
}
```

**Output**:

``` c
Copy code
99 bottles of beer on the wall.
00099 bottles of beer on the wall.
99    bottles of beer on the wall.
+99 bottles of beer on the wall.
 99 bottles of beer on the wall.
0x63 bottles of beer on the wall.
```
