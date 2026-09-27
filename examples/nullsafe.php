<?php


$a = $b?->method();
var_dump($a);  // null

$a = $b?->mzzzz;
var_dump($a); // null

try {
  $b = null;
  $a = $b->method();
} catch (Exception $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
}



try {
  $b = null;
  $a = $b->mzzzz;
} catch (Exception $a) {
    echo 'Caught: '.($a == null ? 'null dereference, class attribute' : $a?->getMessage()).PHP_EOL;
    // Exception: null dereference, class attr
}

$a = $b?->method()?->meth();
$a = $b?->method()?->meth();

echo 'Still alive!'.PHP_EOL;

//$a = $b->method();
$b->c = 10;


echo 'This code is not reached'.PHP_EOL;


?>