<?php

$file = "var.sass";

$sass = new Sass();

$sass->setSourceMapPath('map');
$sass->setOutputStyle(Sass::STYLE_COMPRESSED);

$sass->setLoadPath('abc,scss,sass/main');
$css = $sass->compileFile($file, 'css');

var_dump($css);
