<?php


const A = 0;

function &test2(Throwable $t) {
  return 1;
}



try {

  $a = &test2(new Throwable());
  $a = 1;
  echo 'Huh?'.PHP_EOL;

} catch(Throwable $t) {

  echo $t->getMessage().PHP_EOL;

}

echo 'Still alive';
?>