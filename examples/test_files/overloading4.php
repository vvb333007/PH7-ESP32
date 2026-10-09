<?
/* Constructor overloading
 * Refer to http://ph7.symisc.net/features.html#overloading for additional information.
 */
class a {
  function __construct($a) {
    echo $a.PHP_EOL;
  }
  function __construct(float $a) {
    echo 'A float:'.$a.PHP_EOL;
  }
  function __construct($a, $b) {
    echo $a + $b + 100;
  }
}
$c = new a(60,200); /* You should see: 360 */
/* Here you'll see a 'notice' from the VM. May be this notice should be removed*/
$c = new a(150); /* You should see: 150 */
$c = new a(1.1);

?>