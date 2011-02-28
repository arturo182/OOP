#include <iostream>
#include <string>

#include "AssocArray.h"

using namespace std;

template<typename T>
void my_swap(T &a, T &b) 
{
  T tmp = a;
  a = b;
  b = tmp;
}

int main()
{
  AssocArray<string, int> strXint(5);

  strXint.dodajWartosc("jeden", 1);
  strXint["dwa"] = 2;

  cout << strXint["jeden"] << " " << strXint.znajdzWartosc("dwa") << endl;

  AssocArray<float, string> floatXint(3);
  floatXint.dodajWartosc(3.14f, "pi");
  floatXint.dodajWartosc(1.41f, "sqrt2");
  floatXint.dodajWartosc(2.71f, "e");

  AssocArray<float, string> floatXint2(2);
  my_swap<AssocArray<float, string> >(floatXint, floatXint2);

  cout << "3.14 to stala \"" << floatXint2.znajdzWartosc(3.14f) << "\"" << endl;

  cin.get();
  return 0;
}