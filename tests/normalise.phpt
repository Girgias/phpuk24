--TEST--
Normalise rational
--EXTENSIONS--
rationals
--FILE--
<?php
function dump(RationalNumber $r) {
    echo $r->numerator, '/', $r->denominator, ' becomes: '; 
    $r->normalise();
    echo $r->numerator, '/', $r->denominator, PHP_EOL; 
}

$o = new RationalNumber(6, 4);
dump($o);


$o = new RationalNumber(2, 4);
dump($o);

$o = new RationalNumber(-2, 4);
dump($o);

$o = new RationalNumber(-6, 4);
dump($o);

$o = new RationalNumber(-6, -4);
dump($o);

?>
--EXPECT--
6/4 becomes: 3/2
2/4 becomes: 1/2
-2/4 becomes: -1/2
-6/4 becomes: -3/2
-6/-4 becomes: 3/2
