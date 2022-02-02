#include "iostream"
#include "staff_functions.cpp"
using namespace std;

int main()
{
        int code = -1;
        menu Menu(&code);
        while (code) {
            Menu.echo_menu();
            cin >> code;
            Menu.memu(code);
            cout << '\n';
        }
        return 0;
} 