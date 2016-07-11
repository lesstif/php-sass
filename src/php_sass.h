#ifndef PHPSASS_H
#define PHPSASS_H

#include <phpcpp.h>

using namespace std;

namespace Lesstif
{
class Sass : public Php::Base
{
private:
    /**
     *  The initial value
     *  @var    int
     */
    int _value = 0;

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

