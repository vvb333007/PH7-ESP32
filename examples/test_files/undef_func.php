<?php

try {
hello(10);
} catch(Exception $ex) {
    echo $ex->getMessage() . PHP_EOL;
}

//hello(10);
$a = 'zopa';
$a();

echo 'Not reached';

?>