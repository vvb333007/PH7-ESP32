<?php
class Test {
  public function __construct() {
    $a = 0;
    $b = 1/$a;
    echo $b;
  }
}

$passed = 0;

try {

  $c = new Test();
  echo 'FAILED'.PHP_EOL;
  die();
} catch(Throwable $t) {
  global $passed;
  echo $t->getMessage().PHP_EOL;
  echo 'PASSED STEP 1 of 2'.PHP_EOL;
  $passed++;

}

$passed++;

echo 'PASSED STEP 2 of 2'.PHP_EOL;
if ($passed == 2)
  echo 'PASSED!'.PHP_EOL;
else
  echo 'FAILED!'.$passed.PHP_EOL;
?>