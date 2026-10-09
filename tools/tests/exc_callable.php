<?php

function test(callable $arg): callable {

  return 1;
}

function test2(?callable $arg) {

}
aaa:

$passed = 0;

test2('test');
echo 'PASSED STEP 1 of 3'.PHP_EOL;
$passed++;

try {

  $z = test('test');
  $z();
  echo 'FAILED STEP 2 of 3'.PHP_EOL;

} catch(Error $t) {

  global $passed;

  echo $t->getMessage().PHP_EOL;

  echo 'PASSED STEP 2 of 3'.PHP_EOL;
  $passed++;
}

echo 'PASSED STEP 3 of 3'.PHP_EOL;
$passed++;


if ($passed == 3)
  echo 'PASSED ALL TESTS!'.PHP_EOL;
else
  echo 'FAILED!'.$passed.PHP_EOL;

goto aaa;

?>