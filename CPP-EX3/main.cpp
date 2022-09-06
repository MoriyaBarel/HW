#include "sources/Matrix.hpp"
#include <iostream>
#include <string>

using namespace zich;

int main()
{

    Matrix m;
    char input;
    std::string op;
    std::cout << "To create a new Matrix type 'm', to exit type 'e'." << std::endl;
    while (true)
    {
        try
        {
            std::cin >> input;
            if (input == 'e')
            {
                break;
            }

            else if (input == 'm')
            {
                std::cout << "please enter the mat in this format:[a b c], [d e f], [g h i]" << std::endl;
                std::getchar();
                std::cin >> m; // Exception - input not in format

                std::cout << "For arithmetic operations on the matrix type the requested operator.\n"
                          << "All possible options: +/-/*/++mat/>" << std::endl;

                std::getline(std::cin, op);
                if (op == "+")
                {
                    Matrix other;
                    std::cout << "please enter another matrix:";
                    std::cin >> other;
                    std::cout << "the answer:\n"
                              << m + other << std::endl;
                }
                else if (op == "-")
                {
                    Matrix other;
                    std::cout << "please enter another matrix:";
                    std::cin >> other;
                    std::cout << "the answer:\n"
                              << m - other << std::endl;
                }
                else if (op == "*")
                {
                    Matrix other;
                    std::cout << "please enter another matrix:";
                    std::cin >> other;
                    std::cout << "the answer:\n"
                              << m * other << std::endl;
                }
                else if (op == "++mat")
                {
                    std::cout << "the answer:\n"
                              << (++m) << std::endl;
                }
                else if (op == ">")
                {
                    Matrix other;
                    std::cout << "please enter another matrix:";
                    std::cin >> other;
                    std::cout << "the answer:\n"
                              << (m > other) << std::endl;
                }
            }
        }
        catch (std::exception &ex)
        {
            std::cout << "caught exception: " << ex.what() << std::endl;
        }
    }
}
