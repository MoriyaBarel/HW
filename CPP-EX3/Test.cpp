#include "doctest.h"
#include "sources/Matrix.hpp"
#include "algorithm"
#include <iostream>

using namespace zich;

TEST_CASE("Good Input")
{
    std::vector<double> mat1 = {1, 6, 4.3, 0, 9, 2, 8, -2, 1};
    std::vector<double> mat2 = {3, 0, 4.2, 9, 3, 2, -1, 1, 1.5};
    std::vector<double> mat3 = {4, 6, 8.5, 9, 12, 4, 7, -1, 2.5};
    std::vector<double> mat4 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<double> mat5 = {-3, 0, -4.2, -9, -3, -2, 1, -1, -1.5};
    Matrix a{mat1, 3, 3};
    Matrix b{mat2, 3, 3};
    Matrix c{mat3, 3, 3};
    Matrix d{mat4, 3, 3};
    Matrix e{mat5, 3, 3};

    bool ans = (a+b == c); //check + operator
    CHECK_EQ(ans,true);

    ans = (+a == a); //check unary + operator
    CHECK_EQ(ans,true);

    ans = (c-b == a); //check - operator
    CHECK_EQ(ans, true);

    a+=b; 
    ans = (a == c); // check += operator
    CHECK_EQ(ans, true);

    c-=a;
    ans = (c == d); // check -= operator
    CHECK_EQ(ans, true);

    ans = (-b == e); //check unary - operator
    CHECK_EQ(ans, true);

    ans = (-1*e == b); // check number*matrix operator
    CHECK_EQ(ans, true);

    b*=-1;
    ans = (b == e); //check matrix*=number operator
    CHECK_EQ(ans, true);

    std::vector<double> mat6 = {2, 1, 3, -1, 4, 9, 0, 8, 0, 2, 0, 5};
    std::vector<double> mat7 = {6, 7, 0, 1, 6, 0, 5, 4, -8, 9, 2, 4};
    std::vector<double> mat8 = {-6, 41, 11,	18, -54, 74, 38, 51, 48, 0,	40,	32, -28, 59, 10, 22};
    Matrix f{mat6, 4, 3};
    Matrix g{mat7, 3, 4};
    Matrix fg{mat8, 4, 4};

    ans = (f*g == fg); //check matrix1*matrix2 operator
    CHECK_EQ(ans, true);

    f*=g;
    ans = (f == fg); //check matrix1*=matrix2 operator
    CHECK_EQ(ans, true);

    ans = (f != g); // check != operator
    CHECK_EQ(ans, true);

    ans = (f <= fg); //check <= operator
    CHECK_EQ(ans, true);

    ans = (fg >= fg); //check >= operator
    CHECK_EQ(ans, true);

    ans = (g < fg); //check < operator
    CHECK_EQ(ans, true);

    ans = (fg > g); //check > operator
    CHECK_EQ(ans, true);

    std::vector<double> mat9 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<double> mat10 = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    std::vector<double> mat11 = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    Matrix h{mat9, 3, 3};
    Matrix i{mat10, 3, 3};
    Matrix j{mat11, 3, 3};

    h++;
    ans = (h == i);
    CHECK_EQ(ans, true); //check matrix++ operator

    ++h;
    ans = (h == j);
    CHECK_EQ(ans, true); //check ++matrix operator

    h--;
    --j;
    ans = (h == j);
    CHECK_EQ(ans, true); //check matrix-- ans --matrix operators
}

TEST_CASE("Bad Input")
{
    std::vector<double> mat1 = {2, 1, 3, -1, 4, 9, 0, 8, 0, 2, 0, 5};
    std::vector<double> mat2 = {1, 1, 1, 1, 1, 1};
    Matrix a{mat1, 4, 3};
    Matrix b{mat2, 2, 3};

    //To sum/sub matrices they need to be exactly the same size.
    CHECK_THROWS(a + b); 
    CHECK_THROWS(a - b); 
    CHECK_THROWS(a += b);
    CHECK_THROWS(b - a);
    CHECK_THROWS(b + a);

    CHECK_THROWS(a * b); //Matrix a column and b row amount need to be the same.

    std::vector<double> mat3 = {2, 2, 2, 3, 3, 3};
    std::vector<double> mat4 = {1, 1, 1, 1, 1, 1};
    Matrix c{mat3, 2, 3};
    Matrix d{mat4, 3, 2};
    CHECK_THROWS(c * b); 
    CHECK_THROWS(c -= d); 
    CHECK_THROWS(c += d);
    CHECK_THROWS(c *= a);
}