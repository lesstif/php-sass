<?php

$file = "input/base.scss";

$sass = new Sass();

$sass->setVerboseLevel(Sass::VERBOSE_LEVEL_TRACE);

// Emit source map to 'map' dir
$sass->setSourceMapPath('map');

// STYLE_COMPRESSED, STYLE_COMPACT,STYLE_EXPANDED, STYLE_NESTED
$sass->setOutputStyle(Sass::STYLE_EXPANDED);

// Emit comments showing original line numbers.
$sass->setSourceComment(true);

// Omits the source map url comment.
$sass->setOmitSourceMapUrl(true);

// Set the precision for numbers.
$sass->setPrecision(5);

// Set Sass import path.
$sass->setLoadPath('include');

// Set path to autoload plugins.
$sass->setPluginPath('plugin');

$css = $sass->compileFile($file, 'css');

var_dump($css);
