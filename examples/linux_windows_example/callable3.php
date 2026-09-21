<?php


function test(mixed $b) {
  return (callable)$b; // force typecast
}

echo "1\n";
$a = test('test'); //OK

echo "2\n";
$a = test('strlen'); //OK

echo "3\n";
$a = test('1test'); // Abort

echo 'This will not be printed';


?>