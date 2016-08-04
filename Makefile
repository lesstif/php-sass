CPP             = g++
RM              = rm -f

CPP_FLAGS       = -Wall -c -I. -O2 -std=c++11 -Ilibsass/include -IPHP-CPP

ifeq (${PHPCPP_15},1)
CPP_FLAGS       += -DPHPCPP_15
PHP_ETC_DIR     =   /etc/php5
else
PHP_ETC_DIR     =   /etc/php/7.0
endif

PREFIX			= /usr

PHP_CONFIG      = php-config

#Edit these lines to correspond with your own directories
LIBRARY_DIR		= $(shell ${PHP_CONFIG} --extension-dir)

#PHP_CONFIG_DIR	= $(shell php -r "phpinfo();"|grep "additional .ini file"|awk -F"=>" '{print $2}')

UNAME 				:= 	$(shell uname)

PHP_CLI_CONFIG_DIR	= ${PHP_ETC_DIR}/cli/conf.d
PHP_FPM_CONFIG_DIR	= ${PHP_ETC_DIR}/fpm/conf.d

PHP_MODS_AVAILABLE = ${PHP_ETC_DIR}/mods-available

ifeq (${CENTOS},1)
PHP_ETC_DIR     =   /etc/php-zts.d
PHP_CLI_CONFIG_DIR     = ${PHP_ETC_DIR}
PHP_FPM_CONFIG_DIR     = ${PHP_ETC_DIR}
PHP_MODS_AVAILABLE = /etc/php.d
endif

LD              = g++
LD_FLAGS        = -Wall -shared -O2 
RESULT          = php-sass.so

PHPINIFILE		= php-sass.ini


ifeq (${UNAME}, Darwin)
#CPP_FLAGS       += -undefined dynamic_lookup
LD_FLAGS     += -undefined dynamic_lookup
endif

SOURCES			= $(wildcard src/*.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${RESULT} ${INFO}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lphpcpp -lsass

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

info:
		@echo ${PHP_MODS_AVAILABLE}
		@echo ${PHP_CONFIG_DIR}

${OBJECTS}: ${SOURCES}
		${CPP} ${CPP_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}
		cp -f src/${PHPINIFILE}	${PHP_MODS_AVAILABLE}
		ln -sf ${PHP_MODS_AVAILABLE}/${PHPINIFILE} ${PHP_CLI_CONFIG_DIR}/30-${PHPINIFILE}
		ln -sf ${PHP_MODS_AVAILABLE}/${PHPINIFILE} ${PHP_FPM_CONFIG_DIR}/30-${PHPINIFILE}
