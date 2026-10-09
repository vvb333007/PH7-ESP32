<?php


function test(?callable $arg): callable {

  return 1;
}

$passed = 0;

try {

//  test(null);
  $a = (callable)1;
  $a(1,2,3);
  echo 'FAILED STEP 1 of 4'.PHP_EOL;
  die();

} catch(Throwable $t) {
  global $passed;
  echo $t->getMessage().PHP_EOL;
  $passed++;
  echo 'PASSED STEP 1 of 4'.PHP_EOL;
}
$passed++;
echo 'PASSED STEP 2 of 4'.PHP_EOL;

try {

  $a = test(null);
  $a(1,2,3);
  echo 'FAILED STEP 3 of 4'.PHP_EOL;
  die();

} catch(Throwable $t) {
  global $passed;
  echo $t->getMessage().PHP_EOL;
  $passed++;
  echo 'PASSED STEP 3 of 4'.PHP_EOL;
}
$passed++;
echo 'PASSED STEP 4 of 4'.PHP_EOL;
if ($passed == 4)
  echo 'PASSED ALL TESTS!'.PHP_EOL;
else
  echo 'FAILED!'.$passed.PHP_EOL;


?>