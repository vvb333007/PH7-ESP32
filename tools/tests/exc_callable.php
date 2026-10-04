<?php

function test(callable $arg): ?callable {
  $arg();
  return $arg;
}

function test2(?callable $arg): callable {

  return 1;
}

$passed = 0;

try {

  test(null);
  echo 'Huh?'.PHP_EOL;

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