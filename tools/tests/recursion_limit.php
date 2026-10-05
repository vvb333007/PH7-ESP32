<?php



function recurse($a) {
  recurse($a);
}


$passed = 0;

try {

  recurse(1);  

  echo 'FAILED'.PHP_EOL;
  die();

} catch(Throwable $t) {
  global $passed;
  echo 'Caught: '.$t->getMessage().PHP_EOL;
  
  echo 'PASSED STEP 1 of 2'.PHP_EOL;
  $passed++;

}

$passed++;
echo 'PASSED STEP 2 of 2'.PHP_EOL;

if ($passed == 2)
  echo 'PASSED!'.PHP_EOL;
else
  echo 'FAILED!'.PHP_EOL;
?>