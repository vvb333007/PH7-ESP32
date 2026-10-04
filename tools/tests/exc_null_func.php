<?php

echo 'Hello!';

try {

  $a = null;
  $a(1,2,3);

  echo 'BOOM!!!';
} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;
}

echo 'Still alive!'.PHP_EOL;
?>