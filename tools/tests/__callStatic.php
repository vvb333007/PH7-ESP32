<?php

class Proxy {
    public $__get;
    public static function __callStatic($a):string {
      var_dump(func_num_args());
      return 'Works! '.$a;
    }
}


$z = Proxy::opa(1);

var_dump($z);

?>
