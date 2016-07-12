/**
 *  Libraries used.
 */
#include "php_sass.h"
#include "phpsass_version.h"

#define BUFSIZE 4096

/**
 *  Namespace to use
 */
using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

Lesstif::Sass::Sass()
{
    this->options = sass_make_options();

    // deault options
    sass_option_set_output_style(this->options, SASS_STYLE_NESTED);
    sass_option_set_precision(this->options, 5);

    // read in the "sass.plugin path" variable from the php.ini file
    std::string plugin_path = Php::ini_get("sass.plugin_path");

    this->vpluginPath = split(plugin_path, ',');

    // read in the "variables_order" variable
    std::string include_path = Php::ini_get("sass.include_path");
    Php::notice << "sass.include_path:" << include_path << endl;

    this->vincludePath = split(include_path, ',');

    for (std::vector<std::string>::const_iterator i = this->vincludePath.begin(); i != this->vincludePath.end(); ++i) {
        Php::notice << *i << ' ';
    }
}


// destructor
Lesstif::Sass::~Sass()
{

}


/**
 *  compile sass/scss string
 *
 *  @param  Php::Parameters     sass/scss string
 *  @return Php::Value          compiled string
 */
Php::Value Lesstif::Sass::compile(Php::Parameters &params)
{
    std::string source_string = params[0];
    
    char * buffer = new char[source_string.size() + 1];
    std::copy(source_string.begin(), source_string.end(), buffer);
    buffer[source_string.size()] = '\0'; // don't forget the terminating 0

    //Php::notice << "input sass string:" << buffer << std::endl << std::flush;

    Sass_Data_Context* ctx = sass_make_data_context(buffer);
    Sass_Context* ctx_out = sass_data_context_get_context(ctx);

    // default option
    Sass_Options* options = sass_make_options();

    sass_data_context_set_options(ctx, options);
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

Php::Value Lesstif::Sass::compileFile(Php::Parameters &params)
{
    return "not implmentated, yet";
}
