<?php
class Test {
  public $calls = 0;
  public function __toBool() { $this->calls++; return false; }
}

$a = new Test();
$passed = 0;

if ($a) die('FAILED if'); $passed++;
if (!$a) $passed++; else die('FAILED !');
if ($a && true) die('FAILED &&'); $passed++;
if ($a || false) die('FAILED ||'); $passed++;
if ((bool)$a) die('FAILED cast'); $passed++;
if ($a ? true : false) die('FAILED ternary'); $passed++;
//if ($a ?: false) die('FAILED elvis'); $passed++;   // когда добавишь ?:
while ($a) die('FAILED while');  $passed++;

if ($a->calls != 7) die('FAILED: __toBool call count');   // каждый раз ровно один вызов
echo 'PASSED!'.PHP_EOL;
?>