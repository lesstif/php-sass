# PHP binding for libsass

Compile .scss and .sass files using PHP.

libsass-PHP provides a PHP interface to [libsass](https://github.com/sass/libsass), a fairly complete Sass compiler written in C++.


# Usage

```php
use Lesstif\Sass;

$sass = new Sass();

$str = <<<SASS
div { a { color: black}}
div a {\n  color: black; }\n
SASS;

$sass->compile($str);
```


# Installation

## Dependancy

* gcc
* php7.0 or above
* php7.0-devel
* [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
* [libsass](https://github.com/sass/libsass)

### Ubuntu

```bash
sudo apt-get install gcc php7.0-dev
```

## installation

### checkout project

```bash
git clone https://github.com/lesstif/php-sass
cd php-sass
```

### build libsass

```bash
cd libsass
git checkout 3.3.6
BUILD="shared" make
sudo BUILD="shared" make install
```

### build PHP-CPP

```bash
cd ../PHP-CPP
git checkout v1.5.3
make
sudo make install
```

### build php-sass

```bash
cd ../
make
sudo make install
```

### add environment variable

```basg
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

# Compatibility

Tested with PHP 7.0 on ubuntu 16LTS



