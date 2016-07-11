<?php

$str = <<<STR

\$font-stack:    Helvetica, sans-serif;
\$primary-color: #333;

body {
      font: 100% \$font-stack;
        color: \$primary-color;
}
STR;

$sass = new Sass();

$ret = $sass->compile($str);

var_dump($ret);
