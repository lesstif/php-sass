<?php

$sass = new Sass();
print($sass->version());

print ("print style constant" . "\n\n");

print ("STYLE_COMPRESSED : " . Sass::STYLE_COMPRESSED . "\n");
print ("STYLE_COMPACT : " . Sass::STYLE_COMPACT . "\n");
print ("STYLE_EXPANDED : " . Sass::STYLE_EXPANDED . "\n");
print ("STYLE_NESTED : " . Sass::STYLE_NESTED . "\n");