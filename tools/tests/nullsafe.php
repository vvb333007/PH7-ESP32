<?php


$a = $b?->method();
var_dump($a);  // null

$a = $b?->mzzzz;
var_dump($a); // null

function some() {
  $b = null;
  var_dump(debug_backtrace());
  $a = $b->attribute;
}

try {
//  $b = null;
//  $a = $b->attribute;
  some(1,2,PHP_EOL);
} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var

}

echo 'Still alive!'.PHP_EOL;

try {
  $b = null;
  $a = $b->method();
} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
}

echo 'Still alive!'.PHP_EOL;

$a = $b?->method()?->meth();
$a = $b?->method()?->meth();


//$a = $b?->method()->meth();  // Fatal, must be ?-> everywhere! No NULL propagation!!!
//$a = $b->method();           // Fatal, unsafe dereference
$b->c = 10;                  // Fatal, null dereference



echo 'This code is not reached'.PHP_EOL;


?>