<?php

//(((echo 'A'),0) || (echo 'B')); // Prints B
//((echo 'A') || (echo 'B')); // Prints A

$j = 7;
$a = $v ?? $d ?? $j ?? 99;

var_dump($a);
?>