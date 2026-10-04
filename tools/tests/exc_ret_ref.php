<?php


const A = 0;

function &test2() {
  return A;
  $a = 1;
  return  $a;
}

function &test() {
  return test2();
}



try {

  $a = &test();
  $a = 1;
  echo 'FAILED!'.PHP_EOL;

} catch(Throwable $t) {

  echo 'FAILED!'.PHP_EOL;
  echo $t->getMessage().PHP_EOL;

}

echo 'FAILED';
?>