<?php

class Proxy {
    public function __call($arg1, $arg2, $arg3, $arg4):string {
      var_dump(func_num_args());
      return 'Works from __call!';
    }
    public function __callStatic($arg1, $arg2, $arg3, $arg4):string {
      var_dump(func_num_args());
      return 'Works from __callStatic!';
    }
}

$p = new Proxy();
$z = $p::doSomething(1, 2, 3);
var_dump($z);

?>
