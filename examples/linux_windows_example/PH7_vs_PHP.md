# PH7 vs PHP - Language Differences

| PH7                                                                                                                                                                  | PHP                                                                                                                                                 |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| 64-bit integer arithmetic for all platforms.                                               | 32 bit on 32bit platforms, 64 bit on 64bit platforms                                                                                                                                                                          |
| Static properties can be accessed and modified through the object using the arrow operator | PHP can not access static variables this way, syntax error                                                                                                                                                                    |


```php
class MyClass {
  public static $a = 5*5;  //
}

$n = new MyClass;
$n->a <<= 1;

echo MyClass::$a; /* Will output 50 */
```

| PH7                                                                                                                                                                  | PHP                                                                                                                                                 |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Constructors and Destructors are candidate for overloading exactly like any other class methods. If no constructor is available, attributes will keep their initialization values (any complex expressions) and will not be nullified. | No overloading, No support for comlex expressions |
| Function default arg values can be complex expressions. Same goes for the `const`, `static` and `enum` cases                                                                                 | PHP does not support complex expressions as default params |


```php

const Hello = 'Hello' . rand_str(15); // Initialized once 

function test($callback = function(){ echo "Hello World!\n";})
{
   /* Check if we are dealing with a callback */
  if( !is_callable($callback) ){
     die("Expecting a callback");
  }
  /* Invoke the callback */
  $callback();
}

/* Call without arguments */
test(); /* You should see: Hello World */

/* Call with a single argument */
test(function(){ echo "Welcome guest\n";}); /* You should see: Welcome guest */

test(10); /* You should see: Expecting a callback */

```

| PH7                                                                                                                                                                  | PHP                                                                                                                                                 |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Function overloading and method overloading (by argument numbers and argument types)                                                                                 | PHP does not support function overloading |

```
$a = 25,$b = $a << 1 ,test();

/* Output the value of $a and $b */
function test(){
  global $a,$b;
  echo "\$a = $a \$b= $b\n"; /* You should see: $a = 25 $b = 50*/
}
```
| PH7                                                                                                                                                                  | PHP                                                                                                                                                 |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| `function foo(string $x): int { ... }` - parameter type **automatically converts the argument** to `string`; (return type automatically converts the returned value  | `function foo(int $x): int { ... }` - parameter and return types are used to check type compatibility according to PHP's type system.               |
| `function foo(int $x) { ... }` - `foo("66.6")` receives `66`.                                                                                                        | `function foo(int $x) { ... }` - **type compatibility is checked** according to PHP rules, no conversion is performed                               |
| `function foo(): int { return "666"; }` - returns `int(666)`.                                                                                                        | `function foo(): int { return "666"; }` - Error                                                                                                     |
| `function(int $x):mixed { ... }` - anonymous function (closure). Parameter and return types use automatic conversion                                                 | `function(int $x):mixed { ... }` - anonymous function (closure). Parameter and return types are used for type checking only                         |
| `fn($x): int use ($factor) => $x * $factor` - arrow function **requires explicit variable capture**; return value is converted to `int`.                             | `fn($x): int => $x * $factor` - variables are automatically captured from the outer scope; return type must match closure's return type             |

```
function test(string $x) {
  var_dump($x);            
}

function test2(int $x) {
  var_dump($x);
}

function test3($x) {
  var_dump($x);
}

test(10);       // <-- Displays "string(2, '10')"
test2("10.56"); // <-- Displays "int(10)"
test3("10.56"); // <-- Displays "string(5,'10.56')" , i.e. no conversion

function test4() :int {
  return '42';
}

var_dump(test4()); // <-- Displays "int(42)", i.e. return value was auto cast to function's return type (int)

```

| PH7                                                                                                                                                                  | PHP                                                                                                                                                 |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Normal enum:** `enum Color { case RED; case GREEN; }` - cases are **constants and automatically generated**.                                                       | **Normal enum:** `enum Color { case RED; case GREEN; }` - **cases are enum cases without associated scalar values.**                            |
| **Backed enum:** `enum Color : int { ... }` - cases may be of any type and value (not matching declared enum type), including complex expressions and function calls; enum has a declared type **used for automatic conversion when a case value is consumed** as that enum type.                                           | **Backed enum:** `enum Color : int { ... }` - every case must conform to the declared `int` backing type.|
| **String backed enum:** `enum Color : string { ... }` - enum values are converted to `string` when consumed as the enum type.                                        | **String backed enum:** `enum Color : string { ... }` - every case must conform to the declared `string` backing type.                              |
| **Mixed enum:** case values may have different types. No type check is performed when the cases are declared.                                                        | **Mixed enum:** no equivalent backed-enum construct; a backed enum has one declared backing type.                                                   |
| `enum E : int { case A = "66.6"; }` - the case itself retains `"66.6"`; the value is converted when used where `E` is expected (e.g. in call of `function func(E $x), the $x will be auto cast to `int` (enum type is `int`)                                   | `enum E : int { case A = "66.6"; }` - invalid backed-enum case declaration.                                                                         |
| `function foo(E $x) { ... }` - `E` is treated as the enum's declared type; the argument is automatically converted to that type.                                     | `function foo(E $x) { ... }` - the argument must satisfy the enum type; PHP does not treat the enum type as its backing scalar type.                |
| **Auto-counting:** `case A; case B; case C;` - implicit values are generated automatically.                                                                          | No equivalent general auto-counting enum case values.                                                                                               |
| **Auto-counting with explicit values:** `case A; case B = 10; case C;` - implicit values continue independently; `A` and `C` receive automatically generated values. | No equivalent mechanism.                                                                                                                            |
| Enum case values may use the existing PH7 class-constant expression machinery.                                                                                       | Enum case values are subject to PHP's enum constant-expression restrictions.                                                                        |


```
// No-autoconversion enum (mixed):
//
enum Loo :mixed {
  case Name1 = 10;
  case Name2 = 10.2;
  case Name3 = 'Hello'.rand_str(4);
}

// When used as `Suit $x` in function arguments, will be autoconverted to string
//
enum Suit :string {
  case Name1 = 10;
  case Name2 = 10.2;
  case Name3 = 'Hello'.rand_str(4);
}

function test(Suit $x) {   // Equivalent test(string $x)
  var_dump($x);            // <-- Displays "string(...)"
}

function test(Loo $x) {       // Equivalent test(mixed $x)
  var_dump($x);               // <-- Displays real type of $x
}
```





hate .md tables >:-(
