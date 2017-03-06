#include <iostream>
#include <string>
#include <functional>

#include "Functor.hpp"

struct DividerByThree
{
  int operator()(int x) { return x / 3; }
};

struct DividerByFive
{  
  int divider(int x) { return x / 5 ; }
};

bool function1()
{
  std::cout << "No param" << std::endl;
  return true;
}

bool function2(const std::string& param)
{
  std::cout << param << std::endl;
  return true;
}

bool function3(const std::string& param, int param2)
{
  std::cout << param << ", " << param2 << std::endl;
  return true;
}

bool function4(const std::string& param, int param2, char param3)
{
  std::cout << param << ", " << param2 << ", " << param3 << std::endl;
  return true;
}

bool function5(const std::string& param, int param2, char param3, bool param4)
{
  std::cout << param
	    << ", "
	    << param2
	    << ", "
	    << param3
	    << ", "
	    << std::boolalpha
	    << param4
	    << std::noboolalpha
	    << std::endl;
  return true;
}

int main()
{
  Functor<bool ()> functor = function1;

  std::cout << "( ( ( ( Functor with zero param ) ) ) " << std::endl;
  functor();
  std::cout << std::endl;
  
  
  Functor<bool (const std::string&)> functor2 = &function2;

  std::cout << "( ( ( ( Functor with one param ) ) ) )" << std::endl;
  functor2("Hello World");
  std::cout << std::endl;
  
  
  Functor<bool (const std::string&, int)> functor3 = &function3;

  std::cout << "( ( ( ( Functor with two params ) ) ) )" << std::endl;
  functor3("Hello World", 42);
  std::cout << std::endl;


  Functor<bool (const std::string&, int, char)> functor4 = &function4;

  std::cout << "( ( ( ( Functor with three params ) ) ) )" << std::endl;
  functor4("Hello World", 42, 'c');
  std::cout << std::endl;


  Functor<bool (const std::string&, int, char, bool)> functor5 = &function5;

  std::cout << "( ( ( ( Functor with four params ) ) ) )" << std::endl;
  functor5("Hello World", 42, 'c', true);
  std::cout << std::endl;


  /*Functor<int (int)> functor6 = DividerByThree();

  std::cout << "( ( ( ( Functor with DividerByThree struct ) ) ) )"
	    << std::endl;
  std::cout << "[Operation : 9 / 3] Value is " << functor6(9) << std::endl;
  std::cout << std::endl;


  DividerByFive dividerByFive;
  Functor<int ()> functor7 =
    std::bind(&DividerByFive::divider, dividerByFive, 25);
				       
  std::cout << "( ( ( ( Functor with DividerByFive struct ) ) ) )"
	    << std::endl;
  std::cout << "[Operation : 25 / 5] Value is "
	    << functor7()
	    << std::endl;*/


  Functor<void (void)> functor8 = nullptr;

  std::cout << "( ( ( ( Null functor ) ) ) )" << std::endl;
  
  try
    {
      functor8();
    }
  catch (const std::invalid_argument& e)
    {
      std::cerr << "Exception : " << e.what() << std::endl;
    }
  
  return 1;
}
