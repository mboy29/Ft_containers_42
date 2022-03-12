#ifndef TESTING_HPP
# define TESTING_HPP
# include <stdlib.h>
# include <iostream>

#if STD
	# include <map>
	# include <stack>
	# include <vector>
	namespace ft = std;
#else
	# include "./../../Includes/Ft.hpp"
#endif

void	testingVector(void);
void	testingVectorCapacity(ft::vector<char> *test);
void	testingVectorIterator(ft::vector<char> *test);
void	testingVetorModifiers(ft::vector<char> *test);
void	testingVectorAllocator(void);

void	testingStack(void);
void	testingMap(void);

void	testingMapIterator(ft::map<int, std::string> *test);
void	testingMapCapacity(ft::map<int, std::string> *test);

#endif