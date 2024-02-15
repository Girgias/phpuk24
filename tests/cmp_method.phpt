--TEST--
Check cmp of rationals
--EXTENSIONS--
rationals
--FILE--
<?php
$o1 = new RationalNumber(1, 2);
$o2 = new RationalNumber(2, 4);

var_dump($o1->cmp($o2));
var_dump($o2->cmp($o1));


$o1 = new RationalNumber(4, 5);
$o2 = new RationalNumber(2, 3);

var_dump($o1->cmp($o2));
var_dump($o2->cmp($o1));
?>
--EXPECT--
int(0)
int(0)
int(2)
int(-2)
