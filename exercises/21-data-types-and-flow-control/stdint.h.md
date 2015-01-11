stdint.h search
===============
Writing out all the possible available size identifiers.

On Mac OS X - located `/usr/include/stdint.h`

List of size identifiers as they appear:

* `if __LP64__ __WORDSIZE` - `64`
* `else __WORDSIZE` - `32`

## Minimum-width integer types
* `int_least8_t` - `__signed char` or `int8_t`
* `int_least16_t` - `short` or `int16_t`
* `int_least32_t` - `int` or `int32_t`
* `int_least64_t` - `long long` or `int64_t`
* `uint8_least8_t` - `unsigned char` or `uint8_t`
* `uint_least16_t` - `unsigned short` or `uint16_t`
* `uint_least32_t` - `unsigned int` or `uint32_t`
* `uint_least64_t` - `unsinged long long` or `uint64_t`

## Fastest-width integer types
* `int_fast8_t` - `int8_t`
* `int_fast16_t` - `int16_t`
* `int_fast32_t` - `int32_t`
* `int_fast64_t` - `int64_t`
* `uint_fast8_t` - `uint8_t`
* `uint_fast16_t` - `uint16_t`
* `uint_fast32_t` - `uint32_t`
* `uint_fast64_t` - `uint64_t`

## Greatest-width integer types
* `intmax_t` - `__INTMAX_TYPE__` or `long int` or `long long int`
* `uintmax_t` - `__UINTMAX_TYPE__` or `long unsigned int` or `long long unsigned int`
