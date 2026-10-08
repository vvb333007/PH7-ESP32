<?php

function my_exception_handler(Throwable $e): void
{
    echo "Поймано исключение: " . $e->getMessage() . PHP_EOL;

}

set_exception_handler('my_exception_handler');

//throw new Throwable1("Что-то пошло не так!");
$a = 1/$b;

echo "Эта строка уже не выполнится.";
?>
