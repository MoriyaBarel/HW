#include <iostream>
#include <stdexcept>
#include "mat.hpp"
#include "vector"

using namespace ariel;

    string ariel::mat(int col, int row, char c1, char c2) {
        const int upper_bound = 126;
        const int lower_bound = 33;
        if (row%2 == 0 || col%2 == 0) {
            throw std::invalid_argument("row/col cant be even");
        }
        if (row <= 0 || col <= 0) {
            throw std::invalid_argument("row/col cant be negative/zero");
        }
        if (c1 < lower_bound || c1 > upper_bound || c2 < lower_bound || c2 > upper_bound) {
            throw std::invalid_argument("invalid argument");
        }
        vector<vector<char>> mat;
        for (int m = 0; m < row; m++) {
            vector<char> temp;
            temp.resize(col);
            mat.push_back(temp);
        }
        string ans;
        char to_fill = c1;
        int up = 0;
        int down = row-1;
        int left =  0;
        int right = col-1;

        while(up <= down && left <= right) {
            for (int i = left; i <= right; i++) {
                mat.at(up).at(i) = to_fill;
                mat.at(down).at(i) = to_fill;
            }
            for (int k = up; k <= down; k++) {
                mat.at(k).at(left) = to_fill;
                mat.at(k).at(right) = to_fill;
            }
            up++;
            down--;
            right--;
            left++;
            if (to_fill == c1) {
                to_fill = c2;
            }
            else {
                to_fill = c1;
            }
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {            
                ans += mat.at(i).at(j);
            }
            if (i != row-1) {
                ans += ('\n'); 
            }
        }
        return ans;
    }

       
