<?php


function test(callable $b) : callable {
  return $b;
}


$a = test('test');
var_dump($a);

$a = test(null);
echo 'This will not be printed';


?>