--TEST--
Check RationalNumber class exists
--EXTENSIONS--
rationals
--FILE--
<?php
$o = new RationalNumber(1, 2);
var_dump($o);


$o = new RationalNumber(1, 0);
var_dump($o);
?>
--EXPECT--
object(RationalNumber)#1 (2) {
  ["numerator"]=>
  int(1)
  ["denominator"]=>
  int(2)
}
