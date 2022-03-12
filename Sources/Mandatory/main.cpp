#include "./Testing.hpp"

int		main(void) {
	std::cout << "-------------- [ VECTOR ] ---------------" << std::endl;
	testingVector();
	std::cout << "--------------- [ STACK ] ---------------" << std::endl;
	testingStack();
	std::cout << "---------------- [ MAP ] ----------------" << std::endl;
	testingMap();
	std::cout << std::endl << "--------------- [ ELSE ] ----------------" << std::endl;
	//system("leaks ft");
	return (0);
}

//   ADDD OVERLOAD << ET >>