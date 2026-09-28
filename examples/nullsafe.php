<?php


$a = $b?->method();
var_dump($a);  // null

$a = $b?->mzzzz;
var_dump($a); // null


try {
  $b = null;
  $a = $b->attribute;
} catch (Exception $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
}

echo 'Still alive!'.PHP_EOL;

try {
  $b = null;
  $a = $b->method();
} catch (Exception $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
}

echo 'Still alive!'.PHP_EOL;

$a = $b?->method()?->meth();
$a = $b?->method()?->meth();


$a = $b?->method()->meth();  // Fatal, must be ?-> everywhere! No NULL propagation!!!
//$a = $b->method();           // Fatal, unsafe dereference
//$b->c = 10;                    // Fatal, null dereference


echo 'This code is not reached'.PHP_EOL;


?>