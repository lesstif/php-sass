#ifndef PHPSASS_H
#define PHPSASS_H

#include <phpcpp.h>
#include <sass.h>

using namespace std;

namespace Lesstif
{
class Sass : public Php::Base
{
private:
    /**
     *  Sass_Option initial value
     *  @var    Sass_Options
     */
    Sass_Options* options;

public:
    /**
     *  C++ constructor and destructor
     */
    Sass() ;
    virtual ~Sass();

    Php::Value compile(Php::Parameters &params);
    Php::Value compileFile(Php::Parameters &params);

    // return php-sass & 3rd party library Version
    Php::Value version();

    // setter method
    void setSourceMapPath(Php::Parameters &params);
    void setSourceComment(Php::Parameters &params);

    void setOutputStyle(Php::Parameters &params);
    void setOmitSourceMapUrl(Php::Parameters &params);
    void setPrecision(Php::Parameters &params);
    void setLoadPath(Php::Parameters &params);
    void setPluginPath(Php::Parameters &params);
};

} // end of namespace

#endif

