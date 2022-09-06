#include <string>
#include "Direction.hpp"
#include "vector"

using namespace std;

namespace ariel
{
    void check_throw_erase(const int page, const int row, const int column, Direction direction, const int length);
    void check_throw_read(const int page, const int row, const int column, Direction direction, const int length);

    class Row
    {
        vector<char> row;

    public:
        Row();
        void write(const unsigned long column, const char to_write);
        void write(const unsigned long column, const string &to_write);
        string read(const unsigned long column, const unsigned long length);
        char read(const unsigned long column);
        void erase(const unsigned long column, const unsigned long length);
        void erase(const unsigned long column);
        void show();
    };
    class Page
    {
        vector<Row> page;
        void resize_page(const unsigned long row, Direction direction, const unsigned long length);

    public:
        void write(const unsigned long row, const unsigned long column, Direction direction, const string &to_write);
        string read(const unsigned long row, const unsigned long column, Direction direction, const unsigned long length);
        void erase(const unsigned long row, const unsigned long column, Direction direction, const unsigned long length);
        void show();
    };
    class Notebook
    {
        vector<Page> notebook;

    public:
        void write(const int page, const int row, const int column, Direction direction, const string &to_write);
        string read(const int page, const int row, const int column, Direction direction, const int length);
        void erase(const int page, const int row, const int column, Direction direction, const int length);
        void show(const int page);
        void check_throw_write(const int page, const int row, const int column, Direction direction, const string &to_write);
    };

}
