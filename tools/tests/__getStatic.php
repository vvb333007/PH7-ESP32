<?php

class Proxy {
    public static function __callStatic($name, $args):string {
      return 'Works!';
    }
}


$z = Proxy::opa(1);

var_dump($z);

?>
