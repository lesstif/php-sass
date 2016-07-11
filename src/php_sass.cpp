/**
 *  Libraries used.
 */
#include <sass.h>

#include "php_sass.h"

#define BUFSIZE 4096

/**
 *  Namespace to use
 */
using namespace std;

/*
Sass::Sass()
{

}


// destructor
Sass::~Sass()
{

}
*/

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
    Sass_Data_Context* ctx = NULL;
    char buffer[BUFSIZE];
    size_t size = 1;

    std::string source_string = params[0];

    ctx = sass_make_data_context(source_string.c_str());
    Sass_Context* ctx_out = sass_data_context_get_context(ctx);
    sass_data_context_set_options(ctx, options);
    sass_compile_data_context(ctx);
    int status = sass_compile_data_context(data_context);

    // Check the context for any errors...
    if (status != 0)
    {
        std:string errMsg = sass_context_get_error_message(data_context);
        sass_delete_data_context(ctx);
        throw Php::Exception("sass context compile error() " + errMsg);
    }
   
    Php::Value ret = sass_context_get_output_string(ctx);

    sass_delete_data_context(ctx);
    return ret;

}

