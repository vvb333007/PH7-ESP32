<?php

class Test {
  public function __construct() {
  }
}

try {
  $a = new Test();
  $a->method(1,2,3);
  echo 'BOOM!!!';
} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;
}

echo 'Still alive!'.PHP_EOL;
?>