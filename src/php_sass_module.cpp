/**
 *  Libraries used.
 */
#include <phpcpp.h>

#include "phpsass_version.h"

/**
 *  Namespace to use
 */
using namespace std;

/**
 *  my_return_value_function()
 *  @return Php::Value
 */
Php::Value my_return_value_function()
{
    return "42";
}


// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("PHP-Sass",PHPSASS_VERSION);
        
        // add function to extension
        extension.add<my_return_value_function>("my_return_value_function");
        
        // return the extension module
        return extension.module();
    }
}
