<?php

class Test {
  public function __construct() {
  }
}

try {
  $a = new x2();
  echo 'BOOM!!!';
} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;
}

echo 'Still alive!'.PHP_EOL;
?>