/**
 *  Libraries used.
 */
#include <phpcpp.h>

#include "phpsass_version.h"
#include "php_sass.h"

#include <sass.h>

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

#ifdef  PHPCPP_15
        sass.method("compile", &Lesstif::Sass::compile, Php::Final, {
                Php::ByVal("sassString", Php::Type::String, true),
        });
        sass.method("compileFile", &Lesstif::Sass::compileFile, Php::Final, {
                Php::ByVal("sassFile", Php::Type::String, true),
                Php::ByVal("sassOutFile", Php::Type::String, false),
        });
        sass.method("version", &Lesstif::Sass::version);

        sass.method("setSourceMapPath", &Lesstif::Sass::setSourceMapPath, Php::Final, {
                Php::ByVal("sourceMapPath", Php::Type::String, true),
        });

        sass.method("setSourceComment", &Lesstif::Sass::setSourceComment, Php::Final, {
                Php::ByVal("sourceComment", Php::Type::String, true),
        });

        sass.method("setOutputStyle", &Lesstif::Sass::setOutputStyle, Php::Final, {
                Php::ByVal("outputStyle", Php::Type::String, true),
        });
        
        sass.method("setOmitSourceMapUrl", &Lesstif::Sass::setOmitSourceMapUrl, Php::Final, {
                Php::ByVal("omitSourceMapUrl", Php::Type::String, true),
        });

        sass.method("setPrecision", &Lesstif::Sass::setPrecision, Php::Final, {
                Php::ByVal("precision", Php::Type::String, true),
        });

        sass.method("setLoadPath", &Lesstif::Sass::setLoadPath, Php::Final, {
                Php::ByVal("loadPath", Php::Type::String, true),
        });

        sass.method("setPluginPath", &Lesstif::Sass::setPluginPath, Php::Final, {
                Php::ByVal("pluginPath", Php::Type::String, true),
        });
#else
        sass.method<&Lesstif::Sass::compile>("compile", Php::Final, {
                Php::ByVal("sassString", Php::Type::String),
        });
        sass.method<&Lesstif::Sass::compileFile>("compileFile", Php::Final, {
                Php::ByVal("sassFile", Php::Type::String, true),
                Php::ByVal("sassOutFile", Php::Type::String, false),
        });
        
        sass.method<&Lesstif::Sass::version>("version");
        
        sass.method<&Lesstif::Sass::setSourceMapPath>("setSourceMapPath", Php::Final, {
                Php::ByVal("sourceMapPath", Php::Type::String, true),
        });

        sass.method<&Lesstif::Sass::setSourceComment>("setSourceComment", Php::Final, {
                Php::ByVal("sourceComment", Php::Type::Bool, true),
        });

        sass.method<&Lesstif::Sass::setOutputStyle>("setOutputStyle", Php::Final, {
                Php::ByVal("outputStyle", Php::Type::Constant, true),
        });

        sass.method<&Lesstif::Sass::setOmitSourceMapUrl>("setOmitSourceMapUrl", Php::Final, {
                Php::ByVal("omitSourceMapUrl", Php::Type::Bool, true),
        });
        
        sass.method<&Lesstif::Sass::setPrecision>("setPrecision", Php::Final, {
                Php::ByVal("precision", Php::Type::Numeric, true),
        });
        
        // Set Sass import path.
        sass.method<&Lesstif::Sass::setLoadPath>("setLoadPath", Php::Final, {
                Php::ByVal("loadPath", Php::Type::String, true),
        });

        // Set path to autoload plugins.
        sass.method<&Lesstif::Sass::setPluginPath>("setPluginPath", Php::Final, {
                Php::ByVal("pluginPath", Php::Type::String, true),
        });
#endif
        // add style constants
        sass.add(Php::Constant("STYLE_COMPRESSED", SASS_STYLE_COMPRESSED));
        sass.add(Php::Constant("STYLE_COMPACT", SASS_STYLE_COMPACT));
        sass.add(Php::Constant("STYLE_EXPANDED", SASS_STYLE_EXPANDED));
        sass.add(Php::Constant("STYLE_NESTED", SASS_STYLE_NESTED));

        // add the class to the extension
        extension.add(sass);

        // return the extension module
        return extension.module();
    }
}
