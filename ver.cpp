#include <iostream>
#include <boost/version.hpp>
#include <Eigen/Dense>

using namespace Eigen;
// Macro for display:
#define print(var)  \
  std::cout<<#var"= "<<std::endl<<(var)<<std::endl

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

    Matrix<float, 4, 3> m;
    std::cout << "Rows:" << m.rows() << " Cols:" << m.cols() << std::endl;

    return 0;
}
