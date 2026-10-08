<?php
/* String offset assignment: key type coercion test 
 ZendPHP: pass
 PH8: pass
 PH7 : fails,
*/

function check(string $name, $got, $expected) {
  if ($got === $expected) {
    echo "PASS: $name\n";
  } else {
    echo "FAIL: $name  got=" . var_export($got, true) . "  expected=" . var_export($expected, true) . "\n";
  }
}

/* 1. Baseline: int key (worked before the fix too) */
$s = 'abc';
$s[1] = 'X';
check('int key', $s, 'aXc');

/* 2. Numeric string key */
$s = 'abc';
$s['1'] = 'X';
check('string key "1"', $s, 'aXc');

$s = 'abc';
$s['2'] = 'Y';
check('string key "2"', $s, 'abY');

/* 3. Float key with integral value */
$s = 'abc';
$s[2.0] = 'Y';
check('float key 2.0', $s, 'abY');

$s = 'abc';
$s[0.0] = 'Z';
check('float key 0.0', $s, 'Zbc');

/* 4. Key from a variable, e.g. computed from a numeric string */
$s = 'abcd';
$k = '3';
$s[$k] = 'Q';
check('variable string key', $s, 'abcQ');

/* 5. Reading with non-int keys (LOAD_IDX path, already had the == 0 check) */
$s = 'abc';
check('read string key', $s['1'], 'b');
check('read float key', $s[2.0], 'c');

/* 6. Key must not be modified in place by the store */
$s = 'abc';
$k = '1';
$s[$k] = 'X';
check('key variable untouched', $k, '1');

$s = 'abc';
$s[1.5] = 'X';
check('float key 1.5', $s, 'aXc');

$s = 'abc';
$k = 0.5 + 1;
$s[$k] = 'X';
check('float key runtime 1.5', $s, 'aXc');

/* 7. Behaviour that differs between PH8 and Zend: informational only */
$s = 'abc';
$s[-1] = 'Z';
echo "INFO: negative offset -1 -> '$s'  (Zend: 'abZ', append-on-negative gives 'abcZ')\n";
?>
