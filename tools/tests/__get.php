<?php

class Proxy {

    public static $__gets;
    public $__get;

    public static function __get($arg):array {
      echo '__get('.$arg.') called'.PHP_EOL;
      return array(1,2,3);
    }
}

$cl = new Proxy;

$z = $cl->opa;
var_dump($z);

$z = $cl::opa;
var_dump($z);

?>
