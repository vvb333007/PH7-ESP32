<?php

class Proxy {

    public function __invoke():string {
      echo '__invoke() called'.PHP_EOL;
      return 'Works!';
    }
}

$cl = new Proxy;

$z = $cl();
var_dump($z);

?>
