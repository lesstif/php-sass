<?php

$str = <<<'STR'
nav
ul
margin: 0
padding: 0
list-style: none

li
display: inline-block

a
display: block
padding: 6px 12px
text-decoration: none
STR;

var_dump($str);

$sass = new Sass();

$ret = $sass->compile($str);

var_dump($ret);
