<?php

$str = <<<'SCSS'
$font-stack:    Helvetica, sans-serif;
$primary-color: #333;

body {
  font: 100% $font-stack;
  color: $primary-color;
}
SCSS;

$sass = new Sass();

$css = $sass->compile($str);

var_dump($css);
