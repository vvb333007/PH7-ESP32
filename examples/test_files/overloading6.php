<?
/* Test the powerful overloading mechanism introduced by the PH7 engine
 * Refer to http://ph7.symisc.net/features.html#overloading for additional information.
 */
function foo($a, $b) {
   // foo() accepts two arguments and perform their addition.
     return ($a + $b)."\n";

}

function foo($a) {
    //foo() accepts only a single argument
   return $a.PHP_EOL;
}

function foo($a, float $b) {
   // foo() accepts two arguments and perform their addition.
  return 'A float:' . ($a + $b) . "\n";

}



echo foo(5);
echo foo(5,100);
echo foo(5,100.1); // PH7 BUG#12 -->   100.0 is not a float, 100.1 is

?>