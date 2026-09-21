<?php


function test(?callable $b) {
  $b = 1;
  return (callable)$b;
}

$a = test(null);
echo 'This will not be printed';


?>