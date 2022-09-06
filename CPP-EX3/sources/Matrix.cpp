#include <iostream>
#include <stdexcept>
#include "Matrix.hpp"

using namespace zich;

//------------------------Matrix implementation------------------------------------

void Matrix::check_constructors_throws(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        std::__throw_invalid_argument("rows/cols must be positive number");
    }
}
Matrix::Matrix() {
    this->cols = 0;
    this->rows = 0;
}

Matrix::Matrix(const std::vector<double> &other, int rows, int cols)
{
    check_constructors_throws(rows, cols);
    if (other.size() != rows * cols)
    {
        std::__throw_invalid_argument("vector size doesn't match to row*cols");
    }
    this->cols = cols;
    this->rows = rows;
    this->vec.resize((unsigned int)rows);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            this->vec[i].push_back(other[(i * (unsigned int)cols) + j]);
        }
    }
}

// row and cols resize constructor
Matrix::Matrix(const int rows, const int cols)
{
    check_constructors_throws(rows, cols);
    this->cols = cols;
    this->rows = rows;
    this->vec.resize((unsigned int)rows, std::vector<double>((unsigned int)cols));
}

// copy constructor
Matrix::Matrix(const Matrix &to_copy)
{
    check_constructors_throws(to_copy.rows, to_copy.cols);
    this->cols = to_copy.cols;
    this->rows = to_copy.rows;
    this->vec.resize((unsigned int)to_copy.rows);
    for (unsigned int i = 0; i < to_copy.rows; i++)
    {
        for (unsigned int j = 0; j < to_copy.cols; j++)
        {
            this->vec[i].push_back(to_copy.vec[i][j]);
        }
    }
}

void Matrix::check_size_throws(int rows1, int cols1, int rows2, int cols2)
{
    if (rows1 != rows2 || cols1 != cols2)
    {
        std::__throw_logic_error("matrices has to be the same size");
    }
}

Matrix Matrix::operator+(const Matrix &other)
{
    check_size_throws(this->rows, this->cols, other.rows, other.cols);
    Matrix ans{this->rows, this->cols};
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            ans.vec[i][j] = this->vec[i][j] + other.vec[i][j];
        }
    }
    return ans;
}

Matrix Matrix::operator+()
{
    return Matrix{*this};
}

Matrix Matrix::operator+=(const Matrix &other)
{
    return *this = *this + other;
}

Matrix Matrix::operator-(const Matrix &other)
{
    check_size_throws(this->rows, this->cols, other.rows, other.cols);
    Matrix ans{this->rows, this->cols};
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            ans.vec[i][j] = this->vec[i][j] - other.vec[i][j];
        }
    }
    return ans;
}
// unary
Matrix Matrix::operator-()
{
    Matrix ans{this->rows, this->cols};
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            if (this->vec[i][j] != 0)
            {
                ans.vec[i][j] = -this->vec[i][j];
            }
        }
    }
    return ans;
}

Matrix Matrix::operator-=(const Matrix &other)
{
    return *this = *this - other;
}

void Matrix::check_mul_throws(int cols1, int rows2)
{
    if (cols1 != rows2)
    {
        std::__throw_invalid_argument("to mul matrices mat1 cols has to be the same size like mat2 rows");
    }
}

Matrix Matrix::operator*(const Matrix &other)
{
    check_mul_throws(this->cols, other.rows);
    Matrix ans{this->rows, other.cols};
    double sum = 0;
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < other.cols; j++)
        {
            sum = 0;
            for (unsigned int k = 0; k < this->cols; k++)
            {
                sum += this->vec[i][k] * other.vec[k][j];
            }
            ans.vec[i][j] = sum;
        }
    }
    return ans;
}

Matrix Matrix::operator*=(const Matrix &other)
{
    check_mul_throws(this->cols, other.rows);
    Matrix ans{this->rows, other.cols};
    double sum = 0;
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < other.cols; j++)
        {
            sum = 0;
            for (unsigned int k = 0; k < this->cols; k++)
            {
                sum += this->vec[i][k] * other.vec[k][j];
            }
            ans.vec[i][j] = sum;
        }
    }
    this->cols = ans.cols;
    this->rows = ans.rows;
    this->vec = ans.vec;
    return *this;
}

Matrix Matrix::operator*=(const double num)
{
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this->vec[i][j] = num * this->vec[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator++()
{
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this->vec[i][j]++;
        }
    }
    return *this;
}

Matrix Matrix::operator++(int num)
{
    Matrix temp = *this;
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this->vec[i][j]++;
        }
    }
    return temp;
}

Matrix &Matrix::operator--()
{
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this->vec[i][j]--;
        }
    }
    return *this;
}

Matrix Matrix::operator--(int num)
{
    Matrix temp = *this;
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this->vec[i][j]--;
        }
    }
    return temp;
}

bool Matrix::operator>(const Matrix &other)
{
    check_size_throws(this->rows, this->cols, other.rows, other.cols);
    double this_sum = 0;
    double other_sum = 0;

    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this_sum += this->vec[i][j];
        }
    }

    for (unsigned int i = 0; i < other.rows; i++)
    {
        for (unsigned int j = 0; j < other.cols; j++)
        {
            other_sum += other.vec[i][j];
        }
    }
    return this_sum > other_sum;
}

bool Matrix::operator>=(const Matrix &other)
{
    check_size_throws(this->rows, this->cols, other.rows, other.cols);
    double this_sum = 0;
    double other_sum = 0;

    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            this_sum += this->vec[i][j];
        }
    }

    for (unsigned int i = 0; i < other.rows; i++)
    {
        for (unsigned int j = 0; j < other.cols; j++)
        {
            other_sum += other.vec[i][j];
        }
    }
    return this_sum >= other_sum;
}

bool Matrix::operator<(const Matrix &other)
{
    return !(*this >= other);
}

bool Matrix::operator<=(const Matrix &other)
{
    return !(*this > other);
}

bool Matrix::operator==(const Matrix &other)
{
    check_size_throws(this->rows, this->cols, other.rows, other.cols);
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->cols; j++)
        {
            if (this->vec[i][j] != other.vec[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other)
{
    return !(*this == other);
}

// --------------------------------------------------------------------

namespace zich
{
    Matrix operator*(const double num, const Matrix &to_mul)
    {
        Matrix ans{to_mul.rows, to_mul.cols};
        for (unsigned int i = 0; i < to_mul.rows; i++)
        {
            for (unsigned int j = 0; j < to_mul.cols; j++)
            {
                ans.vec[i][j] = num * to_mul.vec[i][j];
            }
        }
        return ans;
    }

    Matrix operator*(const Matrix &to_mul, const double num)
    {
        return num * to_mul;
    }

    bool operator==(const Matrix &mat1, const Matrix &mat2)
    {
        Matrix::check_size_throws(mat1.rows, mat1.cols, mat2.rows, mat2.cols);
        for (unsigned int i = 0; i < mat1.rows; i++)
        {
            for (unsigned int j = 0; j < mat1.cols; j++)
            {
                if (mat1.vec[i][j] != mat2.vec[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &s_out, const Matrix &mat)
    {
        for (unsigned int i = 0; i < mat.rows; i++)
        {
            s_out << "[";
            for (unsigned int j = 0; j < mat.cols; j++)
            {
                if ((int)mat.vec[i][j] == mat.vec[i][j])
                {
                    s_out << std::to_string((int)mat.vec[i][j]);
                }
                else
                {
                    s_out << std::to_string(mat.vec[i][j]);
                }
                if (j != mat.cols - 1)
                {
                    s_out << ' ';
                }
            }
            s_out << "]";

            if (i != mat.rows - 1)
            {
                s_out << "\n";
            }
        }
        return s_out;
    }

    void check_input_throws(std::string &input)
    {
        int count_open = 0;
        int count_close = 0;
        int count_coma = 0;
        for (unsigned int i = 0; i < input.size(); i++)
        {
            if (input[i] == '[')
            {
                count_open++;
                if (i + 1 < input.size() && std::isdigit(input[i + 1]) == 0 && input[i+1] != '-')
                {
                    std::__throw_invalid_argument("wrong format");
                }
            }
            if (input[i] == ']')
            {
                count_close++;
                if (i + 1 < input.size() && input[i + 1] != ',')
                {
                    std::__throw_invalid_argument("wrong format");
                }
                if (std::isdigit(input[i - 1]) == 0)
                {
                    std::__throw_invalid_argument("wrong format");
                }
            }
            if (input[i] == ',')
            {
                count_coma++;
                if (i + 1 < input.size() && input[i + 1] != ' ')
                {
                    std::__throw_invalid_argument("wrong format");
                }
            }
        }
        if (count_open != count_close)
        {
            std::__throw_invalid_argument("wrong format");
        }
        if (count_open != count_coma + 1)
        {
            std::__throw_invalid_argument("wrong format");
        }
    }

    std::istream &operator>>(std::istream &s_in, Matrix &mat)
    {
        std::string input;
        std::getline(s_in, input);

        check_input_throws(input);

        std::vector<double> values;
        unsigned int i = 0;
        unsigned int cols = 1;
        unsigned int rows = 1;

        // rows counting
        for (unsigned int i = 0; i < input.size(); i++)
        {
            if (input[i] == ',')
            {
                rows++;
            }
        }

        // cols counting
        i = 0;
        while (input[i] != ']')
        {
            if (input[i] == ' ')
            {
                cols++;
            }
            i++;
        }

        std::string str_num;
        // put values into the vector
        for (unsigned int i = 0; i < input.size(); i++)
        {
            if (isdigit(input[i]) != 0 || input[i] == '-')
            {
                str_num += input[i];
                continue;
            }
            if (input[i] == '.')
            {
                str_num += input[i];
                continue;
            }
            if (!str_num.empty())
            {
                values.push_back(std::stod(str_num));
                str_num = "";
            }
        }
        mat.vec.resize(rows, std::vector<double>(cols));
        mat.rows = (int)rows;
        mat.cols = (int)cols;
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < cols; j++)
            {
                mat.vec[i][j] = values[i * cols + j];
            }
        }

        return s_in;
    }

}
