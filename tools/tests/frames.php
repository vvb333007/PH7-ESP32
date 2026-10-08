<?php

/*
Provoke an exception in a nested calls. Print stack backtrace
 */

class TestClass {

  public function uct() {
    $a = 0;
    $b = 2;
    return $b / $a;
  }
}

function test3() {
  $a = new TestClass();
  $a->uct();
}

function test2($x, $y) {
  test3();
}


function test($x, $y) {

  
  test2(array('a'=>1, 2, 3), null);
}

//test(1,2);

try {
  test(1,2);
  die('STEP 1 of 2: FAILED: this code is unreachable!');
} catch( stdClass $t) {

  echo 'Caught: ['.$t->getFile().':'.$t->getLine().'] '.$t->getMessage().PHP_EOL;
  echo 'STEP 1 OF 1: FAILED, wrong class!'.PHP_EOL;
}


?>