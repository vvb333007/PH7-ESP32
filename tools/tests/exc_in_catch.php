<?php



try {
  $b = null;
  $a = $b->attribute;
  echo 'FAILED'.PHP_EOL;
  die();
} catch (Error $a) {
    echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
    try {
      $a = 1 /$zz;
      echo 'FAILED'.PHP_EOL;
      die();
    } catch (Throwable $a) {

      echo 'Caught: '.($a?->getMessage()).PHP_EOL;  // Exception: Attempt to dereference a null var
      //$z = 1/$zz;  
      
    }
    echo 'Still alive after inner try{}'.PHP_EOL;

}

echo 'Still alive!'.PHP_EOL;
?>