#include "mat.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    char x;
    int row;
    int col;
    char c1;
    char c2;
    cout << "Welcome to the carpet factory!" << endl;
    cout << "To create a new carpet press 'c', to exit press 'e'." << endl;
    while(true) {
        cin >> x;
        if (x == 'c') {
            cout << "Please enter rows number: ";
            cin >> row;
            cout << "Please enter columns number: ";
            cin >> col;
            cout << "Please enter the first character number: ";
            cin >> c1;
            cout << "Please enter the second character: ";
            cin >> c2;
            try {
		        cout << ariel::mat(col, row, c1, c2) << endl; // Exception - not a valid code
	        } catch (exception& ex) {
	 	        cout << "caught exception: " << ex.what() << endl;
	        }
        }
        else if (x == 'e') {
            break;
        }
    }
}