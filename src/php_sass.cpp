/**
 *  Libraries used.
 */
 #include <fstream>

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

    vector<string> vPath = split(plugin_path, ',');
    for(vector<string>::iterator it = vPath.begin(); it != vPath.end(); ++it) {
        sass_option_push_plugin_path(this->options, it->c_str());
    }    

    // read in the "include_path" variable
    std::string include_path = Php::ini_get("sass.include_path");
    vPath = split(include_path, ',');
    for(vector<string>::iterator it = vPath.begin(); it != vPath.end(); ++it) {
        sass_option_push_include_path(this->options, it->c_str());
    }    

    /*
    Php::notice << "sass.include_path:" << include_path << endl;
    Php::notice << "sass.plugin_path" << Php::ini_get("sass.plugin_path") << endl;
    Php::notice << "include_path:" << Php::ini_get("include_path") << endl;
    Php::notice << "session.save_handler:" << Php::ini_get("session.save_handler") << endl;
    */
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
    if (params.size() == 0) 
    {
        throw Php::Exception("Parameters must great than 1. ");
    }

    std::string source_string = params[0];
    
    char * buffer = new char[source_string.size() + 1];
    std::copy(source_string.begin(), source_string.end(), buffer);
    buffer[source_string.size()] = '\0'; // don't forget the terminating 0

    //Php::notice << "input sass string:" << buffer << std::endl << std::flush;

    Sass_Data_Context* ctx = sass_make_data_context(buffer);
    Sass_Context* ctx_out = sass_data_context_get_context(ctx);

    // set option
    sass_data_context_set_options(ctx, this->options);
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
    if (params.size() == 0) 
    {
        throw Php::Exception("Parameters must great than 1. ");
    }

    std::string inputFile = params[0];
    std::string outPath;
    std::string fileName;   // only filename, not include extension.
    
    if (params.size() > 1) {
      outPath = params[1].stringValue();
    }

    //Php::notice << "inputFile :''" << inputFile << "',outPath:'" << outPath << "'" << std::flush;

    Sass_File_Context* ctx = sass_make_file_context(inputFile.c_str());
    Sass_Context* ctx_out = sass_file_context_get_context(ctx);

    if (outPath.length() > 0){
        sass_option_set_output_path(this->options, outPath.c_str());

        // extract filename
        unsigned int idx = inputFile.rfind('.');

        if(idx != std::string::npos) {
            fileName = inputFile.substr(0, idx );
        } else {
            fileName = inputFile;
        }
    }

    sass_option_set_input_path(this->options, inputFile.c_str());
    sass_file_context_set_options(ctx, this->options);

    int status = sass_compile_file_context(ctx);

    // Check the context for any errors...
    if (status != 0)
    {
        std::string errMsg = sass_context_get_error_message(ctx_out);
        sass_delete_file_context(ctx);
        throw Php::Exception("sass context compile error() " + errMsg);
    }   

    std::string outString = sass_context_get_output_string(ctx_out);

    // write compiled css into directory
    if (outPath.length() > 0)
    {
        // write file
        ofstream sassFile(outPath + "/" + fileName + ".css");

        sassFile << outString;
        sassFile.close();
    }

    std::string srcMap;

    // std::string constructor does not accept null parameter 
    const char* tmpStr = sass_option_get_source_map_file(this->options);
    if (tmpStr != NULL) {
        srcMap = tmpStr;
    }

    //Php::notice << "srcMapString: " << srcMap << endl;

    std::string srcMapString = sass_context_get_source_map_string(ctx_out);

    //Php::notice << "sass_context_get_source_map_string:" << srcMapString << std::flush;

    std::string outMapfile = sass_option_get_source_map_file(this->options);

    if (outMapfile.length() > 0)
    {
        // write file
        ofstream mapFile(outMapfile + "/" + fileName + ".map");

        mapFile << srcMapString;
        mapFile.close();
    }
        
    Php::Value ret = outString; 

    sass_delete_file_context(ctx);
        
    return ret;
}

void Lesstif::Sass::setSourceMapPath(Php::Parameters &params)
{
    std::string mapPath = params[0].stringValue();

    sass_option_set_source_map_file(this->options, mapPath.c_str());
}

void Lesstif::Sass::setSourceComment(Php::Parameters &params)
{
    bool val = params[0].boolValue();

    sass_option_set_source_comments(this->options, val);
}

void Lesstif::Sass::setOutputStyle(Php::Parameters &params)
{    
    Sass_Output_Style style = static_cast<Sass_Output_Style>(params[0].numericValue());

    sass_option_set_output_style(this->options, style);
}

void Lesstif::Sass::setOmitSourceMapUrl(Php::Parameters &params)
{
    bool val = params[0].boolValue();

    sass_option_set_omit_source_map_url(this->options, val);
}

void Lesstif::Sass::setPrecision(Php::Parameters &params)
{
    int val = params[0].numericValue();

    sass_option_set_precision(this->options, val);
}

void Lesstif::Sass::setLoadPath(Php::Parameters &params)
{
    string val = params[0].stringValue();

    vector<string> vPath = split(val, ',');
    for(vector<string>::iterator it = vPath.begin(); it != vPath.end(); ++it) {
        //Php::notice << "sass_option_push_include_path:" << *it << endl;
        sass_option_push_include_path(this->options, it->c_str());
    }    
}

void Lesstif::Sass::setPluginPath(Php::Parameters &params)
{
    std::string val = params[0].stringValue();

    vector<string> vPath = split(val, ',');
    for(vector<string>::iterator it = vPath.begin(); it != vPath.end(); ++it) {
        //Php::notice << "sass_option_push_plugin_path:" << *it << endl;
        sass_option_push_plugin_path(this->options, it->c_str());
    }
}