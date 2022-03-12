#ifndef TESTING_HPP
# define TESTING_HPP

#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "./../../Includes/Ft.hpp"

using namespace ft;

void	testingVector(void);
void	testingVectorCapacity(vector<char> *test);
void	testingVectorIterator(vector<char> *test);
void	testingVetorModifiers(vector<char> *test);
void	testingVectorAllocator(void);

void	testingStack(void);
void	testingMap(void);

void	testingMapIterator(map<int, std::string> *test);
void	testingMapCapacity(map<int, std::string> *test);
#endif