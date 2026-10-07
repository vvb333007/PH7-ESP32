## In short

In PH8, declared types are guarantees, not restrictions. The runtime automatically converts values when necessary to preserve those guarantees.

### PH8 Type Guarantees

 * **Input Guarantee** — the callee trusts its inputs
  Code inside a function or method can rely on the declared types of its arguments, regardless of what the caller actually passes.

 * **Output Guarantee** — the caller trusts the result
Code calling a function or method can rely on the declared return type, regardless of what the function actually produces.

 * **Encapsulated Data-Type Guarantee** — class members trust their sibling properties
Methods and other members of a class can rely on the declared types of the object's properties. A typed property always contains a value of its declared type, regardless of how the value was assigned.



## More details

As in PHP 8, in PH8 it is possible to specify types of function arguments and return values.

But the philosophy here is different.

In PHP 8 a type mismatch **is considered an error**, while in PH8 the declared type serves as a **hint for the compiler**: it tells the virtual machine, **into what the value should be converted**.

The rules are the same for arguments and return values, so the type is guaranteed both on entering the function and on leaving it.

### Scalar types

Suppose a function is declared like this:

```php
function test(int $a, ?string $b) { /* ... */ }
```

Then the call `test('66', 12)` is completely valid. The virtual machine will convert the string `'66'` to the number `66`, because the first argument is declared as `int`, and the number `12` will be converted to the string `'12'`, because the second argument has type `?string`.

The same happens with return values: if a function with return type `: int` returns `'66'`, the calling code will receive `66`.

### No type and nullable types

If no type is specified, automatic conversion is not performed: the type is assumed to be `mixed`, and the value is passed as it is.

If the type is declared as nullable (for example, `?string`), conversion is applied only to values different from `null`. The `null` itself passes without changes.

### `object` type

If an object is passed (or returned), it passes as it is. If the value is not an object, it is automatically wrapped into `stdClass($scalar_value)`. So the original value is not lost, and code which expects an object always receives an object.

This also applies to `null`: if a `null` is received for a parameter or return value with type `object` (without `?`), it will also be wrapped into `stdClass(null)`. To let `null` pass without changes, the type must be declared as `?object`.

### `callable` type

A value is considered a valid `callable`, if it is a string or an array pointing to a really existing function or method which can be called. For example, the string `'strlen'` or the array `[$obj, 'method']`.

If the value cannot be converted to `callable`, it is replaced with a call to the special `__badcallable` function from the system library. For the code it is a full `callable` (`is_callable()` will return `true`), but at the first attempt to call it, a `TypeError` exception will be thrown, which can be catched using `try/catch`.

The error is therefore not lost: it appears at the moment when the incorrect value is used, instead of staying unnoticed.

PH8 always guarantees type correspondence: scalars are converted, non-objects (including `null`) are wrapped into `stdClass`, and an invalid `callable` is converted into a stub which will throw a `TypeError` exception when called.

### Typed class attributes

Class attributes can also have a declared type:

```php
class Test {
  public static int $z = 0;
  public ?string $a = 'hello';
}
```

The declared type of an attribute is **persistent** - it cannot be changed by assigning a value of another type.

When a value is assigned to a typed attribute, PH8 automatically converts the value to the declared type, whenever possible. So the attribute always keeps its declared type throughout its lifetime.

For example:

```php
$a = new Test();

$a->a = 123;
```

The value will be automatically converted to the string `'123'`, because `$a->a` is declared as `?string`.

The same conversion rule are used for class attributes - as for function arguments and return values.
