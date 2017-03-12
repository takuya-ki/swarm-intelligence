
#include <iostream>
#include <algorithm>
#include <cmath>        // abs() for float, and fabs()
#include <math.h>       // pow()
#include <random>
#include <climits>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp> // row(), column()

using namespace boost::numeric::ublas;

#define print(var) \
  std::cout<<#var" = "<<(var)<<std::endl;
#define printstr(str) \
  std::cout<<str<<std::endl;
#define printLine() \
  std::cout<<"============================"<<std::endl;
