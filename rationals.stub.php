<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

function test1(): void {}

function test2(string $str = ""): string {}

class RationalNumber {
    public int $numerator;
    public int $denominator;

    public function __construct(int $numerator, int $denominator) {}

    public function add(RationalNumber $o): RationalNumber {}

    public function normalise(): void {}

    public function cmp(RationalNumber $o): int {}
}
