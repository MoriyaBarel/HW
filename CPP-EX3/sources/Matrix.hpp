#include "vector"
#include <iostream>

namespace zich
{
    class Matrix
    {
    private:
        int rows;
        int cols;
        std::vector<std::vector<double>> vec;
    public:
        Matrix();
        Matrix(const std::vector<double> &other, const int rows, const int cols);
        Matrix(int rows, int cols);
        Matrix(const Matrix &to_copy);

        void static check_constructors_throws(int rows, int cols);
        void static check_size_throws(int rows1, int cols1, int rows2, int cols2);
        void static check_mul_throws(int cols1, int rows2);
        friend void check_input_throws(std::string &input);

        Matrix operator+(const Matrix &other); // c = a+b
        Matrix operator+();                    // unary
        Matrix operator+=(const Matrix &other);  // a = a+b

        Matrix operator-(const Matrix &other); // c = a-b
        Matrix operator-();                    // unary
        Matrix operator-=(const Matrix &other);  // a = a-b

        Matrix operator*(const Matrix &other);                        // c = a*b
        friend Matrix operator*(const double num, const Matrix &to_mul); // b = num*a
        friend Matrix operator*(const Matrix &to_mul, const double num); // b = a*num
        Matrix operator*=(const Matrix &other);                         // a = a*b
        Matrix operator*=(const double num);                            // a = a*num

        Matrix& operator++(); //prefix
        Matrix operator++(int); 
        Matrix& operator--(); //prefix
        Matrix operator--(int);

        bool operator>(const Matrix &other);
        bool operator>=(const Matrix &other);
        bool operator<(const Matrix &other);
        bool operator<=(const Matrix &other);
        bool operator==(const Matrix &other);
        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        bool operator!=(const Matrix &other);

        friend std::ostream &operator<<(std::ostream &s_out, const Matrix &mat); // cout
        friend std::istream &operator>>(std::istream &s_in, Matrix &mat); // cin
    };
}