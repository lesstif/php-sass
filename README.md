# PHP binding for libsass

You don't have to install ruby/Node.JS stack no more.

You need only to install the PHP and Compile .scss and .sass files using PHP.

[php-sass](https://github.com/lesstif/php-sass) provides a PHP interface to [libsass](https://github.com/sass/libsass), a fairly complete Sass compiler written in C++.


# Usage


## compile sass string.

```php
<?php

$sass = new Sass();

$str = <<<'SASS'
div { 
    a { 
        color: black
      }
    }
div a {  
    color: black; 
    }
SASS;

$str = $sass->compile($str);
var_dump($str);
```

## compile sass file and returing string.

```php
<?php

$file = 'input.sass';

$sass = new Sass();

$css = $sass->compileFile($file);

var_dump($css);
```

## compile sass file to css file.

```php
<?php

$file = 'input.sass';

$sass = new Sass();

// saved 'css-output-dir/input.css'
$css = $sass->compileFile($file, 'css-output-dir');

var_dump($css);
```

## set style

```php
<?php

$file = 'input.sass';

$sass = new Sass();

$sass->setOutputStyle(Sass::STYLE_COMPRESSED);

// saved 'css-output-dir/input.css'
$css = $sass->compileFile($file, 'css-output-dir');

var_dump($css);
```

## full features example.

```php
<?php

$file = "input/base.scss";

$sass = new Sass();

//$sass->setVerboseLevel(Sass::VERBOSE_LEVEL_TRACE);

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

// saved to 'css/base.css' and 'map/base.css.map'
$css = $sass->compileFile($file, 'css');

var_dump($css);

```

# Installation

## Dependancy

* gcc/g++ 4.8 or above(libsass requires gcc 4.8)
* php 5.5 or above
* php devel package(The package name is different for each distro.)
* [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
* [libsass](https://github.com/sass/libsass)

### installation Pre-Requisite packages.

#### Ubuntu 16 LTS

```bash
sudo apt-get install gcc g++ php7.0-dev
```

#### Ubuntu 14 LTS

```bash
sudo apt-get install gcc g++ php5-dev
```

#### CentOS 7 with Webtatic package

```bash
yum install gcc gcc-c++ php70w-cli php70w-devel
```

## installation

1. checkout project

    ```bash
    git clone --recurse-submodules https://github.com/lesstif/php-sass
    cd php-sass
    ```

1. build libsass

    ```bash
    cd libsass
    git checkout 3.3.6
    BUILD="shared" make
    sudo BUILD="shared" make install
```

1. build PHP-CPP

    ```bash
    cd ../PHP-CPP
    ```

    1. PHP 5.6 or below

    ```bash
    git checkout v1.5.3
    make PHPCPP_15=1
    ```
    1. PHP 7.0 or above

    ```bash
    make
    ```

1. install PHP-CPP library

    ```bash
    sudo make install
    ```

1. appending below line to the file '.profile' in your home directory; then log out and log in again.

    ```basg
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
    ```

1. build php-sass module.

    ```bash
    cd ../
    make
    ```
    
    if you are using RHEL derived distro, make with custom option.

    ```bash
    make CENTOS=1
    ```

1. install php-sass to PHP modules directory.
    
    ```bash
    sudo make install
    ```

### check installation

```bash
php -r "phpinfo(INFO_MODULES);"|grep -i sass
```

# Compatibility

* Tested with below environments.
  * PHP 7.0 on ubuntu 16LTS
  * PHP 5.6 on ubuntu 14LTS
  * PHP 7.0( [WebTatic Resository](https://webtatic.com/)) on CentOS 7



