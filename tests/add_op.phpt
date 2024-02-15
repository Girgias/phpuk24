--TEST--
Add via binop
--EXTENSIONS--
rationals
--FILE--
<?php
$o1 = new RationalNumber(1, 2);
$o2 = new RationalNumber(2, 4);
$o3 = $o1 + $o2;

var_dump($o3);

$o1 += $o3;
var_dump($o1);

try {
    //$r = $o2 + new stdClass();
} catch (\Throwable $e) {
    echo $e::class, $e->getMessage(), PHP_EOL;
}
try {
    //$r = $o2 + [];
} catch (\Throwable $e) {
    echo $e::class, $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
object(RationalNumber)#3 (2) {
  ["numerator"]=>
  int(8)
  ["denominator"]=>
  int(8)
}
object(RationalNumber)#4 (2) {
  ["numerator"]=>
  int(24)
  ["denominator"]=>
  int(16)
}

