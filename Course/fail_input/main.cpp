#include <iostream>

using std::endl;
using std::cout;
using std::cin;

bool checkInput();

int main()
{
  float grade1{0}, grade2{0}, avg{0};

  cout << "Enter your first grade: ";
  cin >> grade1;
  if (!checkInput()) {
    return EXIT_FAILURE;
  }
  cout << "Enter your second grade: ";
  cin >> grade2;
  if (!checkInput()) {
    return EXIT_FAILURE;
  }

  avg = (grade1+grade2)/2;
  cout << "Average: " << avg << endl;
}

bool checkInput()
{
  if (cin.fail()) {
    cin.clear(); // Clean error flags
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clean buffer
    cout << "Invalid input\n";
    return false;
  }

  return true;
}
