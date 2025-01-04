#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    cout << "Date" << endl;
    Date pgt(1, 1, 2000);
    pgt.print();
    pgt.change(1, 1, 2024);

    Date pgt2;
    pgt.print();

    return EXIT_SUCCESS;
}
