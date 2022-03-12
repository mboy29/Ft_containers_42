#include "./Testing.hpp"

using namespace ft;

void	testingStack(void) {
	vector<std::string>		test1(3, "VECTOR");
	stack<std::string>		test2(test1);

	std::cout << "-> Testing stack on following vector<std::string> :" << std::endl << "   ";
	for (vector<std::string>::iterator it = test1.begin(); it != test1.end(); it += 1)
		std::cout << *it << " ";
	if (test2.empty())
		std::cout << std::endl << "-> Stack aka vector is empty" << std::endl;
	else
		std::cout << std::endl << "-> Stack aka vector is not empty" << std::endl;
	std::cout << "-> Stack aka vector size : " << test2.size() << std::endl;
	std::cout << "-> Stack aka vector top element : " << test2.top() << std::endl;
	test2.push("STACK");
	std::cout << "-> Stack aka vector size after push : " << test2.size() << std::endl;
	std::cout << "-> Stack aka vector top element after push : " << test2.top() << std::endl;
	test2.pop();
	std::cout << "-> Stack aka vector size after pop : " << test2.size() << std::endl;
	std::cout << "-> Stack aka vector top element after pop : " << test2.top() << std::endl;
}

void	testingMapIterator(map<int, std::string> *test) {
	std::cout << "-> Testing map on following map<int, std::string> :" << std::endl;
	for (map<int, std::string>::iterator it = test->begin(); it != test->end(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
	std::cout << "-> Reverse :" << std::endl;
	for (map<int, std::string>::reverse_iterator it = test->rbegin(); it != test->rend(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
}

// void	testingMapOperations(map<int, std::string> *test) {

// }

void	testingMap(void) {
	map<int, std::string>	test1; //  Default constructor
	
	test1[1] = "One"; //  Operator[]
	test1[2] = "Two";
	test1[3] = "Three";

	testingMapIterator(&test1);
	// testingMapOperations(&test1);
}

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