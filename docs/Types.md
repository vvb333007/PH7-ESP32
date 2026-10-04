## In short:

In PH8, a declared type is not a restriction on a value, but a request for a particular representation. The VM always converts a value to the declared type when possible, both for function arguments and return values; mixed leaves the value untouched, while nullable types allow null to pass through unchanged. Type errors therefore occur not simply because a value originally had the “wrong” type, but when the resulting value cannot be meaningfully used as required.


## Details:

Just like PHP 8, PH8 allows you to specify argument types and return types for functions.

The philosophy, however, is different.

In PHP 8, a type mismatch is considered an error. In PH8, a declared type is more like a hint to the compiler: it tells the virtual machine **what the value should be converted to**.

The same rules apply to both function arguments and return values, so the declared type is guaranteed both when entering and leaving a function.

### Scalar Types

Suppose we have a function declared like this:

```php
function test(int $a, ?string $b) { /* ... */ }
```

Then calling `test('66', 12)` is perfectly valid. The virtual machine converts the string `'66'` to the integer `66` because the first argument is declared as `int`. Likewise, the number `12` is converted to the string `'12'` because the second argument is declared as `?string`.

Return values work the same way. If a function declared with `: int` returns `'66'`, the calling code receives `66`.

### Untyped and Nullable Types

If no type is specified, no automatic conversion is performed. The value is treated as `mixed` and passed through unchanged.

If a type is nullable (for example, `?string`), conversion is only applied to values other than `null`. A `null` value is passed through unchanged.

### The `object` Type

If an object is passed as an argument or returned from a function, it is left untouched. If the value is not an object, it is automatically wrapped in `stdClass($scalar_value)`.

This means the original value is not lost, while code expecting an object always gets one.

The same applies to the `null`. If a parameter or return value is declared as `object` (without `?`) and receives `null`, it is wrapped in `stdClass(null)` as well. If `null` should pass through unchanged, the type must be declared as `?object`.

### The `callable` Type

A value is considered a valid `callable` if it is a string or an array referring to an actual function or method that can be called. For example, `'strlen'` or `[$obj, 'method']`.

If a value cannot be converted to a `callable`, it is replaced with a call to the special `__badcallable` function from the system library. As far as the rest of the code is concerned, this is a perfectly valid `callable` — `is_callable()` will return `true` — but the first attempt to call it throws a `TypeError`, which can be caught with `try/catch`.

So the error is not lost. It shows up when the invalid value is actually used, rather than going unnoticed.

### Summary

With the same rules applied to both function arguments and return values, PH8 always guarantees the declared types.

It does this not by rejecting mismatched values, but by sensibly converting them to the declared types: scalars are converted, non-objects (including `null`) are wrapped in `stdClass`, and an invalid `callable` is replaced with a stub that throws a `TypeError` when called.
