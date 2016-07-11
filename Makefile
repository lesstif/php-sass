CPP             = g++
RM              = rm -f
CPP_FLAGS       = -Wall -c -I. -O2 -std=c++11

PREFIX			= /usr

PHP_CONFIG      = php-config
#Edit these lines to correspond with your own directories
LIBRARY_DIR		= $(shell ${PHP_CONFIG} --extension-dir)

#PHP_CONFIG_DIR	= $(shell php -r "phpinfo();"|grep "additional .ini file"|awk -F"=>" '{print $2}')

## hard coding
PHP_CONFIG_DIR	= /etc/php/7.0/cli/conf.d
PHP_MODS_AVAILABLE = /etc/php/mods-available

LD              = g++
LD_FLAGS        = -Wall -shared -O2 
RESULT          = php-sass.so

PHPINIFILE		= php-sass.ini

SOURCES			= $(wildcard src/*.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${RESULT} ${INFO}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lphpcpp

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

info:
		@echo ${PHP_MODS_AVAILABLE}
		@echo ${PHP_CONFIG_DIR}

${OBJECTS}: 
		${CPP} ${CPP_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}
		cp -f src/${PHPINIFILE}	${PHP_MODS_AVAILABLE}
		ln -sf ${PHP_MODS_AVAILABLE}/${PHPINIFILE} ${PHP_CONFIG_DIR}/30-${PHPINIFILE}
