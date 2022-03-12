#include "./Testing.hpp"

void	testingMapIterator(ft::map<int, std::string> *test) {
	std::cout << "-> Testing map on following map<int, std::string> :" << std::endl;
	for (ft::map<int, std::string>::iterator it = test->begin(); it != test->end(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
	std::cout << "-> Reverse :" << std::endl;
	for (ft::map<int, std::string>::reverse_iterator it = test->rbegin(); it != test->rend(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
}

void	testingMapCapacity(ft::map<int, std::string> *test) {
	if (test->empty() == true)
		std::cout << "-> Map is empty." << std::endl;
	else
		std::cout << "-> Map is not empty." << std::endl;
	std::cout << "-> Map size is of : " << test->size() << std::endl;
	std::cout << "-> Map maximum size if of : " << test->max_size() << std::endl;
}

void	testingMapModifiers(ft::map<int, std::string> *test) {
	ft::map<int, std::string>::iterator it = test->begin();

	test->insert(ft::pair<int, std::string>(10, "Ten"));
  	test->insert (it, ft::pair<int, std::string>(8,"Eight"));  // max efficiency inserting
  	test->insert (it, ft::pair<int, std::string>(-1, "Minus One")); 
	std::cout << "->  Map after insert :" << std::endl;
	for (ft::map<int, std::string>::iterator it = test->begin(); it != test->end(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
	test->erase(8);
	test->erase(it);
	std::cout << "->  Map after erase :" << std::endl;
	for (ft::map<int, std::string>::iterator it = test->begin(); it != test->end(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
}

void	testingMap(void) {
	ft::map<int, std::string>	test1; //  Default constructor
	
	test1[1] = "One"; //  Operator[]
	test1[2] = "Two";
	test1[3] = "Three";

	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
	testingMapIterator(&test1);
	std::cout << "------------- [ CAPACITY ] --------------" << std::endl;
	testingMapCapacity(&test1);
	std::cout << "------------- [ MODIFIERS ] -------------" << std::endl;
	testingMapModifiers(&test1);
	// testingMapOperations(&test1);
}