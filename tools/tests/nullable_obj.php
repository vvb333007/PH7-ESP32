<?php
class Test {
  public function p() { echo 'Hello!'.PHP_EOL; }
}

function z( ?Test $t) {
  if ($t !== null)
    $t->p();
  else
    echo 'Null is skipped'.PHP_EOL;
}


$x = new Test();


z($x);
z(null);
z(1);

?>