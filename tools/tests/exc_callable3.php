<?php

function test($arg) : ?callable {
  return $arg;
}

$passed = 0;

test(null);
echo 'PASSED STEP 1 of 4'.PHP_EOL;
$passed++;

test('test');
echo 'PASSED STEP 3 of 4'.PHP_EOL;
$passed++;

try {

  test(1);
  echo 'FAILED STEP 3 of 4'.PHP_EOL;

} catch(Error $t) {

  global $passed;

  echo $t->getMessage().PHP_EOL;

  echo 'PASSED STEP 3 of 4'.PHP_EOL;
  $passed++;
}

echo 'PASSED STEP 4 of 4'.PHP_EOL;
$passed++;


if ($passed == 4)
  echo 'PASSED ALL TESTS!'.PHP_EOL;
else
  echo 'FAILED!'.$passed.PHP_EOL;

?>