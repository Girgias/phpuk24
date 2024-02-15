--TEST--
test1() Basic test
--EXTENSIONS--
rationals
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension rationals is loaded and working!
NULL
