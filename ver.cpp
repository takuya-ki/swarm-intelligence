#include <iostream>
#include <boost/version.hpp>

int main()
{
    int major = BOOST_VERSION / 100000;
    int minor = BOOST_VERSION / 100 % 1000;
    int patch = BOOST_VERSION % 100;
    std::cout << "boost version " << major << "." << minor << "." << patch
        << " or " << BOOST_LIB_VERSION << std::endl;

    if( __cplusplus == 201103L ) std::cout << "C++11\n" ;
    else if( __cplusplus == 199711L ) std::cout << "C++98\n" ;
    else std::cout << "pre-standard C++\n" ;
    return 0;
}
