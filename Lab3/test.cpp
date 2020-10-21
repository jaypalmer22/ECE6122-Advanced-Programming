// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

using namespace std;
 
void foo() 
{
  // do stuff...
}

void bar(int x)
{
  // do stuff...
}

int main() 
{
  int a = 5;

  int b = a++;

  cout << b << endl;
}