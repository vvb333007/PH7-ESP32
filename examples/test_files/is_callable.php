<?php
/*
Expected output:

Testing un-typed callback
Hello World!
Hello, guest
Expecting a callable type
Testing typed callback
Hello World!
Hello, guest
is_callable.php Error: Function 'test', a callable is expected*/

/* 'callable' as an argument type enforces strict argument check: VM stops if argument is not callable
 *
 */
function test(callable $callback = function() { echo "Hello World!\n";}) {

  $callback();
}

/* 'mixed' type (or no-type) allows anything to be passed without checking. 
 *  Type is checked later by 'is_callable()'
 */
function test2($callback = function() { echo "Hello World!\n";}) {

  if (!is_callable($callback)) {
    echo "Expecting a callable type\n";
    return ;
  }
  $callback();
}

echo "Testing un-typed callback\n";

test2();
test2(  ($z = function () { echo "Hello, guest\n"; })  );
test2(11);

echo "Testing typed callback\n";

test();
test($z);
test(11);

echo 'This text should not be printed, because test(11) caused VM stop';

?>
