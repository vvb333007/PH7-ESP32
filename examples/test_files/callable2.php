<?php


function test(?callable $b) : ?callable {
  return $b;
}


$a = test(null);
var_dump($a);

$a = test('test');
var_dump($a);

$a = test('random junk');
var_dump($a);


?>