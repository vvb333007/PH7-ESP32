<?php

function test2(?Throwable $t) {
  echo 'Hello: '.$t->getMessage().PHP_EOL;
}



try {
  test2(new Throwable('Johnny'));
  test2(new TypeError('Billy'));

  test2(new stdClass(1));
//  test2(array(1,2,3));
//  test2(22);
  test2(null);
  echo 'Huh?'.PHP_EOL;

} catch(Throwable $t) {

  echo $t->getMessage().PHP_EOL;

}

echo 'Still alive';
?>