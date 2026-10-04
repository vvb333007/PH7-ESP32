<?php
/* This test is PH8-specific: Zend PHP requires $a to be a 'const'
 * PH8 allows class::member access for both constants and static attributes as well.
 *
 */
class Test {
  public $a = 1;
}

class Test2 {
  public static $a = "PASSED STEP 3 of 3\n";
}

$passed = 0;

try {

  $c = new Test();
  echo $c::a;          // exception: member is not a const and not static

  echo 'FAILED'.PHP_EOL;
  die();
} catch(Throwable $t) {
  global $passed;
  echo $t->getMessage().PHP_EOL;
  
  echo 'PASSED STEP 1 of 3'.PHP_EOL;
  $passed++;

}

$passed++;
echo 'PASSED STEP 2 of 3'.PHP_EOL;

$c = new Test2();
echo $c::a;
$passed++;


if ($passed == 3)
  echo 'PASSED!'.PHP_EOL;
else
  echo 'FAILED!'.PHP_EOL;
?>