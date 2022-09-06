#include <iostream>
#include <stdexcept>
#include "Notebook.hpp"
#include "Direction.hpp"

using namespace std;
using namespace ariel;
const int MAX_ROW_SIZE = 100;
const int CHAR_UPPER_BOUND = 126;
const int CHAR_LOWER_BOUND = 32;

// ------------------------------Row implemetation--------------------------------------
Row::Row(){
    for (int i = 0; i < MAX_ROW_SIZE; i++) {
        row.push_back('_');
    }
}

void Row::write(const unsigned long column, const char to_write) {
    row[column] = to_write;
}

void Row::write(const unsigned long column, const string& to_write) {
    for (unsigned int i = 0; i < to_write.size(); i++) {
        row[column+i] = to_write[i];
    }
}

string Row::read(const unsigned long column, const unsigned long length) {
    string ans;
    for (unsigned int i = 0; i < length; i++) {
        ans += row[column+i];
    }
    return ans;
}

char Row::read(const unsigned long column) {
    return row[column];
}

void Row::erase(const unsigned long column, const unsigned long length) {
    for (unsigned long i = 0; i < length; i++) {
        row[column+i] = '~';
    }
}

void Row::erase(const unsigned long column) {
    row[column] = '~';
}

void Row::show() {
    for (unsigned int i = 0; i < row.size(); i++) {
        cout << row[i];
    }
    cout << endl;  
}
// --------------------------------------------------------------------------------------

// ------------------------------Page implemetation--------------------------------------
void Page::write(const unsigned long row, const unsigned long column, Direction direction, const string& to_write) {
    resize_page(row, direction, to_write.size());
    if (direction == Direction::Horizontal) {
        page[row].write(column, to_write);
    } else {
        for (unsigned int i = 0; i < to_write.size(); i++) {
            page[row+i].write(column, to_write.at(i));
        }
    }
}

string Page::read(const unsigned long row, const unsigned long column, Direction direction, const unsigned long length) {
    resize_page(row, direction, length);
    string ans;
    if (direction == Direction::Horizontal) {
        ans = page[row].read(column, length);
    } else {
        for (unsigned int i = 0; i < length; i++) {
            ans += page[row+i].read(column);
        }
    }
    return ans;
}

void Page::erase(const unsigned long row, const unsigned long column, Direction direction, const unsigned long length) {
    resize_page(row, direction, length);
    if (direction == Direction::Horizontal) {
        page[row].erase(column, length);
    } else {
        for (unsigned int i = 0; i < length; i++) {
            page[row+i].erase(column);
        }
    }
}

void Page::show() {
    for (unsigned int i = 0; i < page.size(); i++) {
        page[i].show();
    } 
}

void Page::resize_page(const unsigned long row, Direction direction, const unsigned long length) {
    if (direction == Direction::Horizontal) {
        if (page.size() <= row) {
            page.resize(row + 1);
        }
    }
    if (direction == Direction::Vertical) {
        if (page.size() < row + length) {
            page.resize(row + length);
        }
    }
}
// --------------------------------------------------------------------------------------

// ------------------------------Notebook implemetation---------------------------------
void Notebook::write(const int page, const int row, const int column, Direction direction, const string& to_write) {
    
    check_throw_write(page,row,column,direction,to_write);
    if (notebook.size() <= page) {
        notebook.resize((unsigned long)page+1);
    }
    notebook[(unsigned long)page].write((unsigned long)row, (unsigned long)column, direction, to_write);
}

string Notebook::read(const int page, const int row, const int column, Direction direction, const int length) {
    
    check_throw_read(page,row,column,direction,length);
    if (notebook.size() <= page) {
        notebook.resize((unsigned long)page+1);
    }
    return notebook[(unsigned long)page].read((unsigned long)row, (unsigned long)column, direction, (unsigned long)length);
}

void Notebook::erase(const int page, const int row, const int column, Direction direction, const int length) {
    
    check_throw_erase(page,row,column,direction,length);
    if (notebook.size() <= page) {
        notebook.resize((unsigned long)page+1);
    }
    notebook[(unsigned long)page].erase((unsigned long)row, (unsigned long)column, direction, (unsigned long)length);
}

void Notebook::show(const int page) {
    if (page < 0) {
        throw invalid_argument("page/row/column can't be a negative number.");
    }
    if (notebook.size() <= page) {
        cout << "empty page" << endl;
    }
    notebook[(unsigned long)page].show();       

}

void Notebook::check_throw_write(const int page, const int row, const int column, Direction direction, const string& to_write) {
    if (page < 0 || row < 0 || column < 0) {
        throw invalid_argument("page/row/column can't be a negative number.");
    }
    if (column >= MAX_ROW_SIZE) {
        throw invalid_argument("Max row length is limited to 100.");
    }
    if (direction == Direction::Horizontal) {
        if ((unsigned long)column + to_write.size()-1 >= MAX_ROW_SIZE) {
            throw out_of_range("You are trying write over the row range, which is limited to 100.");
        }
    }
    string read = this->read(page, row, column,direction, to_write.size());
    for (unsigned long i = 0; i < to_write.size(); i++) {
        if (read[i] != '_') {
            throw logic_error("OOPS can't write over non empty space.");
        }
        if (to_write[i] < CHAR_LOWER_BOUND || to_write[i] > CHAR_UPPER_BOUND || to_write[i] == '~') {
            throw invalid_argument("Invalid character");
        }
    }
}

void ariel::check_throw_erase(const int page, const int row, const int column, Direction direction, const int length) {
    if (page < 0 || row < 0 || column < 0 || length < 0) {
        throw invalid_argument("page/row/column can't be a negative number.");
    }
    if (column >= MAX_ROW_SIZE) {
        throw invalid_argument("Max row length is limited to 100.");
    }
    if (direction == Direction::Horizontal) {
        if (column + length-1 >= MAX_ROW_SIZE) {
            throw out_of_range("You are trying read over the row range, which is limited to 100.");
        }
    }
}

void ariel::check_throw_read(const int page, const int row, const int column, Direction direction, const int length) {
    if (page < 0 || row < 0 || column < 0 || length < 0) {
        throw invalid_argument("page/row/column can't be a negative number.");
    }
    if (column >= MAX_ROW_SIZE) {
        throw invalid_argument("Max row length is limited to 100.");
    }
    if (direction == Direction::Horizontal) {
        if (column + length - 1 >= MAX_ROW_SIZE) {
            throw out_of_range("You are trying erase over the row range, which is limited to 100.");
        }
    }    
}

// --------------------------------------------------------------------------------------
