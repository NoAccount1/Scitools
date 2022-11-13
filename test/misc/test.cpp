#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <stdarg.h>
#include <math.h>
// #include <optional>

using namespace std;

int extract();

int main() {
  int toto = 12345;
  int len = 5;
  cout << sizeof(toto) << endl;
  for (int i = 0; i < pow(10, len);)
  {
    i = i ? i*10 : 1;
    cout << floor(toto/(i*10))*(i*10) << endl;
  }

  return 0;
}
