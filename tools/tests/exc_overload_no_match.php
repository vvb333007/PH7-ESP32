<?
/* Test the powerful overloading mechanism introduced by the PH7 engine
 * Refer to http://ph7.symisc.net/features.html#overloading for additional information.
 */
$passed = 1;

//foo() accepts only a single argument
function foo($a) {
  global $passed;
  $passed <<= 1;
  return $a.PHP_EOL;
}

// foo() accepts two arguments, one of which is float
function foo($a, float $b) {
  global $passed;
  $passed <<= 1;
  return 'float called';
}

// foo() accepts two arguments
function foo($a, $b) {
  global $passed;
  $passed <<= 1;
  return ($a + $b)."\n";
}

echo foo(5); // Prints "5"
echo foo(10, 2); // Prints "12"
echo foo(10, 2.2); // float called

if ($passed != 8)
  die("STEP 1 of 3: FAILED");
else
  echo "STEP 1 of 3: PASSED\n";
try {
  echo foo(10, 2.2, 'hello'); // float called
  die('STEP 2 of 3: FAILED');
} catch(Throwable $t) {
  global $passed;
  $passed <<= 1;
  echo "STEP 2 of 3: PASSED\n";
}
echo "STEP 3 of 3: PASSED\n";

if ($passed != 16)
  die("FAILED!");
else
  echo "PASSED!\n";


?>