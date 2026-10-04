<?php

try {
  $a = 'jopa';
  $a();

} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
}

echo 'Still alive!'.PHP_EOL;
?>