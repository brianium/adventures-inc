stdint.h research
=================
Writing out all the possible available size identifiers.

On Mac OS X - located `/usr/include/stdint.h`

List of size identifiers as they appear:

* `if __LP64__ __WORDSIZE` - `64`
* `else __WORDSIZE` - `32`

## Exact-width integer types
* `int8_t` - `__signed char`
* `int16_t` - `short`
* `int32_t` - `int`
* `int64_t` - `long long`
* `uint8_t` - `unsigned char`
* `uint16_t` - `unsigned short`
* `uint32_t` - `unsinged int`
* `uint64_t` - `unsinged long long`

## Minimum-width integer types
* `int_least8_t` - `int8_t`
* `int_least16_t` - `int16_t`
* `int_least32_t` - `int32_t`
* `int_least64_t` - `int64_t`
* `uint8_least8_t` - `uint8_t`
* `uint_least16_t` - `uint16_t`
* `uint_least32_t` - `uint32_t`
* `uint_least64_t` - `uint64_t`

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

## Limits of fastest minimum-width integer types
* `INT_FAST8_MIN` - `INT8_MIN`
* `INT_FAST16_MIN` - `INT16_MIN`
* `INT_FAST32_MIN` - `INT32_MIN`
* `INT_FAST64_MIN` - `INT64_MIN`
* `INT_FAST8_MAX` - `INT8_MAX`
* `INT_FAST16_MAX` - `INT16_MAX`
* `INT_FAST32_MAX` - `INT32_MAX`
* `INT_FAST64_MAX` - `INT64_MAX`
* `UINT_FAST8_MAX` - `UINT8_MAX`
* `UINT_FAST16_MAX` - `UINT16_MAX`
* `UINT_FAST32_MAX` - `UINT32_MAX`
* `UINT_FAST64_MAX` - `UINT64_MAX`

## Limits of integer types capable of holding object pointers
* `if __WORDSIZE == 64 INTPTR_MIN` - `INT64_MIN`
* `if __WORDSIZE == 32 INTPTR_MIN` - `INT32_MIN`
* `if __WORDSIZE == 64 INTPTR_MAX` - `INT64_MAX`
* `if __WORDSIZE == 32 INTPTR_MIN` - `INT32_MAX`
* `if __WORDSIZE == 64 UINTPTR_MAX` - `UINT64_MAX`
* `if __WORDSIZE == 32 UINTPTR_MAX` - `UINT32_MAX`

## Limits of greatest-width integer types
* `INTMAX_MIN` - `INT64_MIN`
* `INTMAX_MAX` - `INT64_MAX`
* `UINTMAX_MAX` - `UINT64_MAX`

## Other
* `if __WORDSIZE == 64 PTRDIFF_MIN` - `INT64_MIN`
* `if __WORDSIZE == 32 PTRDIFF_MIN` - `INT32_MIN`
* `if __WORDSIZE == 64 PTRDIFF_MAX` - `INT64_MAX`
* `if __WORDSIZE == 32 PTRDIFF_MAX` - `INT32_MAX`
* `if __WORDSIZE == 64 SIZE_MAX` - `UINT64_MAX`
* `if __WORDSIZE == 32 SIZE_MAX` - `UINT32_MAX`

* `WCHAR_MAX` - `__WCHAR_MAX__` or `0x7fffffff`
* `WCHAR_MIN` - `0` or `(-WCHAR_MAX-1)`
* `WINT_MIN` - `INT32_MIN`
* `WINT_MAX` - `INT32_MAX`
* `SIG_ATOMIC_MIN` - `INT32_MIN`
* `SIG_ATOMIC_MAX` - `INT32_MAX`
