<?php

$j = 7;

// 7
$a = $v ?? $d ?? $j ?? 99;
var_dump($a);

// Always FALSE: 
// Executed from left to right: $a||$b yields boolean type --> '??' always short circuit (bool is not null)
$z = $aa || $bb ?? $a;   
var_dump($z);

// TRUE: 
// Executed from left to right: $bb ?? $a yields $a which is then ORed with FALSE, yielding TRUE
$z = $aa || ($bb ?? $a);   
var_dump($z);


$arr = array(1,2,3,4,5,6);

// hello
$z = $arr[99] ?? "hello";
var_dump($z);

// 2
$z = $arr[1] ?? "hello";
var_dump($z);



?>