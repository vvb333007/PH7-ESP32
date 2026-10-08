<?php
function check(string $name, $got, $expected) {
  echo ($got === $expected ? "PASS" : "FAIL") . ": $name\n";
}

$a = 'abc'; $b = 'abc'; $c = 'abd';

check('eq differ',  ($a eq $c), false);
check('ne equal',   ($a ne $b), false);
check('ne differ',  ($a ne $c), true);


check('eq "1.0" vs "1"',  ('1.0' eq '1'),  false);
check('ne "1.0" vs "1"',  ('1.0' ne '1'),  true);
check('eq "10" vs "1e1"', ('10' eq '1e1'), false);
check('eq empty',         ('' eq ''),      true);
check('eq case',          ('a' eq 'A'),    false);


check('eq int vs string', (10 eq '10'),    true);
check('ne int vs string', (10 ne '10'),    false);


$r = 'no';
if ($a eq $b) $r = 'yes';
check('if eq', $r, 'yes');
$r = 'no';
if ($a ne $c) $r = 'yes';
check('if ne', $r, 'yes');
$r = 'no';
if ($a ne $b) $r = 'yes';
check('if ne equal', $r, 'no');

?>
