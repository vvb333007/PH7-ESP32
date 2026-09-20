<?php

$col = 10;

$g = function () use($col) :int {

  return $col;
};

var_dump($g);

$col = 11;
echo $g(); // must output "10"

?>