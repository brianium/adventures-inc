stdint.h research
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

## Limits of exact-width integer types
* `INT8_MAX` - `127`
* `INT16_MAX` - `32767`
* `INT32_MAX` - `2147483647`
* `INT64_MAX` - `9223372036854775807LL`
* `INT8_MIN` - `-128`
* `INT16_MIN` - `-32768`
* `INT32_MIN` - `(-INT32_MAX-1)`
* `INT64_MIN` - `(-INT64_MAX-1)`
* `UINT8_MAX` - `255`
* `UINT16_MAX` - `65535`
* `UINT32_MAX` - `4294967295U`
* `UINT64_MAX` - `18446744073709551615ULL`

## Limits of minimum-width integer types
* `INT_LEAST8_MIN` - `INT8_MIN`
* `INT_LEAST16_MIN` - `INT16_MIN`
* `INT_LEAST32_MIN` - `INT32_MIN`
* `INT_LEAST64_MIN` - `INT64_MIN`
* `INT_LEAST8_MAX` - `INT8_MAX`
* `INT_LEAST16_MAX` - `INT16_MAX`
* `INT_LEAST32_MAX` - `INT32_MAX`
* `INT_LEAST64_MAX` - `INT64_MAX`
* `UINT_LEAST8_MAX` - `UINT8_MAX`
* `UINT_LEAST16_MAX` - `UINT16_MAX`
* `UINT_LEAST32_MAX` - `UINT32_MAX`
* `UINT_LEAST64_MAX` - `UINT64_MAX`
