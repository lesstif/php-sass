#!/bin/bash


# Make sure only root can run this script
if [ "$(id -u)" == "0" ]; then
	echo "This script must be run as root" 1>&2
	exit 1
fi

UN=`uname`

## check php-config
type php-config >/dev/null 2>&1

if [ $? != 0 ];then
	echo >&2 "Installer require php-config but it's not installed.  Aborting."; 
	exit 1; 
fi

PHP_VER=`php-config --version`

echo "detecting PHP ${PHP_VER}"

MAJOR=`echo ${PHP_VER} | cut -d'.' -f 1`
MINOR=`echo ${PHP_VER} | cut -d'.' -f 2`
PATCH=`echo ${PHP_VER} | cut -d'.' -f 3`

## find addtional ini directory
INI_DIR=`php --ini|grep "additional .ini"|cut -d ':' -f 2|xargs`


if [ $UN == 'Darwin' ];then
	BIN_DIR="binary/osx"
	echo "OS X";
elif [ $UN == 'Linux' ];then
	## Determine  linux distro
	echo "Linux";
	DISTRO=`lsb_release -i`
	if [[ ${DISTRO} == *"Ubuntu"* ]];then
		BIN_DIR="binary/ubuntu"
		echo "Ubuntu";
	elif [[ ${DISTRO} == *"CentOS"*  || ${DISTRO} == *"RedHat"* ]];then
		BIN_DIR="binary/centos"
		echo "CentOS or RedHat";
	else
		echo "Unsupported Linux distro ${DISTRO}";
	fi
else
	echo "Unsupported OS ${UN}";
fi

## copy pre-compiled binary
cp 

## create module ini
echo -e ";configuration for phpcpp module\n;priority=30\nextension=php-sass.so" > "${INI_DIR}/30-php-sass.ini"
