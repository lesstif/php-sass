/**
 *  Libraries used.
 */
#include <sass.h>

#include "php_sass.h"
#include "phpsass_version.h"

#define BUFSIZE 4096

/**
 *  Namespace to use
 */
using namespace std;

Lesstif::Sass::Sass()
{

}


// destructor
Lesstif::Sass::~Sass()
{

}


/**
 *  compile sass/scss string
 *
 *  @param  Php::Parameters     the given parameters
 *  @return Php::Value
 */
Php::Value Lesstif::Sass::compile(Php::Parameters &params)
{
    /*
    for (unsigned int i = 0; i < params.size(); i++)
    {
        cout << params[i] << endl;
    }
    */
    //size_t size = 1;

    std::string source_string = params[0];
    
    char * buffer = new char[source_string.size() + 1];
    std::copy(source_string.begin(), source_string.end(), buffer);
    buffer[source_string.size()] = '\0'; // don't forget the terminating 0

    Php::notice << "input sass string:" << buffer << std::endl << std::flush;

    Sass_Data_Context* ctx = sass_make_data_context(buffer);
    Sass_Context* ctx_out = sass_data_context_get_context(ctx);

    // default option
    Sass_Options* options = sass_make_options();
    sass_option_set_output_style(options, SASS_STYLE_NESTED);
    sass_option_set_precision(options, 5);

    sass_data_context_set_options(ctx, options);
    sass_compile_data_context(ctx);
    int status = sass_compile_data_context(ctx);

    // Check the context for any errors...
    if (status != 0)
    {
        std::string errMsg = sass_context_get_error_message(ctx_out);
        sass_delete_data_context(ctx);
        throw Php::Exception("sass context compile error() " + errMsg);
    }
   
    Php::Value ret = sass_context_get_output_string(ctx_out);

    sass_delete_data_context(ctx);
    return ret;

}

Php::Value Lesstif::Sass::version()
{
    std::ostringstream stringStream;

    stringStream << "PHP-Sass Version:" << PHPSASS_VERSION << std::endl;
    stringStream << "libsass Version:" << libsass_version() << std::endl;
    stringStream << "sass Version:" << libsass_language_version() << std::endl;
    stringStream << "sass2scss Version:" << sass2scss_version() << std::endl;

    stringStream << "PHP-CPP Version:" << PHPCPP_API_VERSION << std::endl;

    std::string ver = stringStream.str();

    return ver;
}