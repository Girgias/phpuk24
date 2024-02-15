--TEST--
add method test
--EXTENSIONS--
rationals
--FILE--
<?php

$o1 = new RationalNumber(1, 2);
$o2 = new RationalNumber(2, 4);

var_dump($o1->add($o2));

?>
--EXPECT--
object(RationalNumber)#3 (2) {
  ["numerator"]=>
  int(8)
  ["denominator"]=>
  int(8)
}
