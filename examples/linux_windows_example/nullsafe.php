<?php

$a = $b?->method();
var_dump($a);

$a = $b?->mzzzz;
var_dump($a);

try {
  $b = null;
  //$a = $b->mzzzz;
  $a = $b->method();
} catch (Exception $a) {
  if (is_null($a)) {
    echo 'Looks like null dereference happened';
  } else 
    echo $a->getMessage();
}

$a = $b->method();
echo 'This code is not reached'."\n";


?>