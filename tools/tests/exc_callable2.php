<?php


function test(?callable $arg): callable {

  return 1;
}

$passed = 0;
  $a = test(null);
  $a(1,2,3);


try {

  $a = test(null);
  $a(1,2,3);
  echo 'FAILED!'.PHP_EOL;
  die();

} catch(Throwable $t) {
  global $passed;
  echo $t->getMessage().PHP_EOL;
  $passed++;
  echo 'PASSED STEP 1 of 2'.PHP_EOL;
}
$passed++;
echo 'PASSED STEP 2 of 2'.PHP_EOL;
if ($passed == 2)
  echo 'PASSED!'.PHP_EOL;
else
  echo 'FAILED!'.$passed.PHP_EOL;

?>