# printf
//


This is a 42 school project.
The task was to recreate the printf function.

https://www.cplusplus.com/reference/cstdio/printf/


// Format Specifiers

A format specifier follows this prototype: `%[flags][width][.precision][length]type`
The following format specifiers are supported:

// Supported Types

| Type   | Output |
|--------|--------|
| d or i | Signed decimal integer |
| u      | Unsigned decimal integer	|
| o      | Unsigned octal |
| x      | Unsigned hexadecimal integer (lowercase) |
| X      | Unsigned hexadecimal integer (uppercase) |
| f      | Decimal floating point |
| c      | Single character |
| s      | String of characters |
| p      | Pointer address |
| %      | A % followed by another % character will write a single % |

// Supported Flags

| Flags | Description |
|-------|-------------|
| '-'        | Left-justify within the given field width; Right justification is the default (see width sub-specifier). |
| '+'        | Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.|
|' ' (space) | If no sign is going to be written, a blank space is inserted before the value by a signed conversion (__d__, __f__, or __i__). |
| '#'     | Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero. Used with  f or F it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written.
| '0'     | Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier). |

// Supported Width

| Width    | Description |
|----------|-------------|
| (number) | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger. |
| *        | The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. |

// Supported Precision

| Precision	| Description |
|-----------|-------------|
| .number   | For integer specifiers (__d__, __i__, __o__, __u__, __x__, __X__): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For __f__ specifier: this is the number of digits to be printed after the decimal point. By default, this is 6. For __s__: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. If the period is specified without an explicit value for precision, 0 is assumed. |
| .*        | The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. |


### Supported Length

The length sub-specifier modifies the length of the data type.

| Modifier | d i  | u o x X |
|----------|------|---------|
| hh       | signed char | unsigned char |
| h        | short | unsigned short |
| l        | long | unsigned long |
| ll       | long long | unsigned long long |

| Modifier | f |
|----------|---|
|l         |double|
|L         |long double |
