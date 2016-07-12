# PHP binding for libsass

Compile .scss and .sass files using PHP.

[php-sass](https://github.com/lesstif/php-sass) provides a PHP interface to [libsass](https://github.com/sass/libsass), a fairly complete Sass compiler written in C++.


# Usage

[See sass guide.](http://sass-lang.com/guide)

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

# Installation

## Dependancy

* gcc/g++
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

## installation

1. checkout project

    ```bash
    git clone https://github.com/lesstif/php-sass
    cd php-sass
    git submodule init
    git submodule update
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

1. install php-sass to PHP modules directory.
    
    ```bash
    sudo make install
    ```

### check installation

```bash
php -r "phpinfo(INFO_MODULES);"|grep -i sass
```

# Compatibility

* Tested with PHP 7.0 on ubuntu 16LTS
* Tested with PHP 5.6 on ubuntu 14LTS



