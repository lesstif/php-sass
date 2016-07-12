<?php


$file = "Qq";

$sass = new Sass();

$ret = $sass->compileFile($file);

var_dump($ret);
