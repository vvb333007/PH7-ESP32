<?php

function test1(mixed $arg): string {
  return $arg === null ? null : $arg;
}

function test2(mixed $arg): ?string {   // nullable return value
  return $arg === null ? null : $arg;
}

function test3(?string $x, int $y){ // nullable argument
  var_dump($x);
  var_dump($y);
}


var_dump(test1('hello'));   // 'hello'
var_dump(test1(11));        // '11'  number converted to a string
var_dump(test1(null));      // ''    null is converted to an empty string (string)

var_dump(test2('hello'));   // 'hello'
var_dump(test2(11));        // '11'
var_dump(test2(null));      // null    null is NOT converted and left intact (?string) 

test3('hello', null); // 'hello', 0  --> null is converted to int(0)
test3(null, '666'); // null, 666  --> '666' is converted to int(666)

?>
