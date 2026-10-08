<?php

function my_exception_handler(Throwable $e): void
{
    echo "Поймано исключение: " . $e->getMessage() . PHP_EOL;

}

set_exception_handler('my_exception_handler');


$a = 0;
try {
throw new Throwable("jopa");
echo "Эта не выполнится.";
} catch(DivisionByZeroError $t) {
  echo "Поймано исключение: " . $t->getMessage() . PHP_EOL;
}
//$b =  1/$a;

echo "Эта выполнится.";
?>
