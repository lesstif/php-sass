/**
 *  Libraries used.
 */
#include <phpcpp.h>

#include "phpsass_version.h"
#include "php_sass.h"

/**
 *  Namespace to use
 */
using namespace std;

// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("PHP-Sass",PHPSASS_VERSION);

        Php::Class<Lesstif::Sass> sass("Sass");

        // add methods to it
        sass.method<&Lesstif::Sass::compile>("compile", Php::Final, {});
        sass.method<&Lesstif::Sass::compileFile>("compileFile", Php::Final, {});

        sass.method<&Lesstif::Sass::version>("version");

        // add the class to the extension
        extension.add(sass);

        // return the extension module
        return extension.module();
    }
}
