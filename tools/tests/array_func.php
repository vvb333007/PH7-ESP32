<?php
function ffn() {
  echo 'fn()';
  return array(1,2,3);
}


$a = array( ffn());

var_dump($a);

?>