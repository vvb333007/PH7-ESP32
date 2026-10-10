<?php

class Proxy {
    public function __call($name, $args):string {
      return 'Works!';
    }
}

$p = new Proxy();
$z = $p->doSomething(1, 2, 3);
var_dump($z);

?>
