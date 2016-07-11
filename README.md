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

```bash
git clone 
cd libsass-php
git submodule
make
sudo make install
```   

# Compatibility

Tested with PHP 7.0 on ubuntu 16LTS



