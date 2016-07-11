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

    std::vector<std::string> vpluginPath;
    std::vector<std::string> vincludePath;

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
};

} // end of namespace

#endif

