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
	test->clear();
	if (test->empty() == true)
		std::cout << "-> Map after clear is empty." << std::endl;
	else
		std::cout << "-> Map after clear is not empty." << std::endl;
	std::cout << "-> Map size after clear is of : " << test->size() << std::endl;
	std::cout << "-> Map maximum size after clear is of : " << test->max_size() << std::endl;
}

void	testingMapObservers(ft::map<std::string, double> *test) {
	ft::map<std::string, double>::iterator		it;
	ft::map<std::string, double>::key_compare	testComp;
	std::string									resComp;
	ft::pair<std::string, double>				resValue;

	std::cout << "-> Testing key_comp on following map<std::string, double> :" << std::endl;
	testComp = test->key_comp();
	resComp = test->rbegin()->first;
	it = test->begin();
	std::cout << "   [ " << it->first << " ] mesures [ " << it->second << " ] centimeters" << std::endl;
	while (testComp((*it++).first, resComp))
		std::cout << "   [ " << it->first << " ] mesures [ " << it->second << " ] centimeters" << std::endl;
	resValue = *test->rbegin();
	std::cout << "-> Testing key_value :" << std::endl;
	std::cout << "   Tallest patient is [ " << resValue.first << " ] mesuring [ " << resValue.second << " ]" << std::endl;;
}

void	testingMapOperations(ft::map<int, char> *test) {
	ft::map<int, char>::iterator		it = test->find(23);
	ft::pair<ft::map<int, char>::iterator, ft::map<int, char>::iterator>	resEqualRange;

	
	std::cout << "-> Testing on following map<int, char> :" << std::endl;
	for (ft::map<int, char>::iterator it = test->begin(); it != test->end(); it++) //  begin() & end() & tree_iterator
		std::cout << "   [ " << it->first << " ] [ " << it->second << " ]" << std::endl ;
	std::cout << "-> Find pair with first element equal to 13 :" << std::endl;
	std::cout << "   [ " << it->first << " ] [ " << it->second << " ] " << std::endl;
	std::cout << "-> Determin if integer is part of this map with count :" << std::endl;
	for (int idx = 22; idx < 28; idx += 1) {
		(test->count(idx) > 0) ?	std::cout << "   " << idx << " is an element of this map" << std::endl
			: std::cout << "   " << idx << " is NOT an element of this map" << std::endl;
	}
	resEqualRange = test->equal_range(10);
	std::cout << "-> 10th letter of the alphabet equal_range" << std::endl;
	std::cout << "   aka lower_bound : [ " << resEqualRange.first->first << " ] th letter is [ " << resEqualRange.first->second << " ]" << std::endl;
	std::cout << "-> 10th letter of the alphabet equal_range" << std::endl;
	std::cout << "   aka upper_bound : [ " << resEqualRange.second->first << " ] th letter is [ " << resEqualRange.second->second << " ]" << std::endl;
}

void	testingMap(void) {
	ft::map<int, std::string>		test1; //  Default constructor
	ft::map<std::string, double>	test2;
	ft::map<int, char>				test3;
	
	test1[1] = "One"; //  Operator[]
	test1[2] = "Two";
	test1[3] = "Three";
	test2["Patient A"] = 1.70;
	test2["Patient B"] = 1.52;
	test2["Patient C"] = 1.95;
	test2["Patient D"] = 2.01;
	for (int idx = 0; idx < 26; idx += 1)
		test3[idx + 1] = idx + 65;
	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
	testingMapIterator(&test1);
	std::cout << "------------- [ CAPACITY ] --------------" << std::endl;
	testingMapCapacity(&test1);
	std::cout << "------------- [ MODIFIERS ] -------------" << std::endl;
	testingMapModifiers(&test1);
	std::cout << "------------- [ OBSERVERS ] -------------" << std::endl;
	testingMapObservers(&test2);
	std::cout << "------------ [ OPERATIONS ] -------------" << std::endl;
	testingMapOperations(&test3);

}