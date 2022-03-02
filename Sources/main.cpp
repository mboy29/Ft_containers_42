#include "./../Includes/Ft.hpp"

using namespace ft;


void	testingPairSwap(void) {
	pair<std::string, int> testInit1("Mehdi", 23); // Initialization constructor
	pair<std::string, int> testInit2("Melody", 12); // Initialization constructor
	
	std::cout << "------------- [ PAIR SWAP ] -------------" << std::endl;
	std::cout << "-> Before Swap Pairs 1: " << testInit1.first << " - " << testInit1.second << std::endl;
	std::cout << "-> Before Swap Pairs 2: " << testInit2.first << " - " << testInit2.second << std::endl;
	std::cout << "-> After Swap Pairs 1: " << testInit1.first << " - " << testInit1.second << std::endl;
	std::cout << "-> After Swap Pairs 2: " << testInit2.first << " - " << testInit2.second << std::endl;
}

void	testingPairRationalOperators(void) {
	pair<int,char> foo (10,'z');
	pair<int,char> bar (90,'a');

	std::cout << "----- [ PAIR RELATIONAL OPERATORS ] -----" << std::endl;
	std::cout << "-> Comparing pair<int, char>:" << std::endl;
	// std::cout << "   Foo: " << get<0>(foo) << " / " << get<1>(foo);
	// std::cout << " - Bar: " << get<0>(bar) << " / " << get<0>(bar) << std::endl;
	(foo == bar) ? std::cout << "-> Foo and bar are equal" << std::endl : 0;
	(foo != bar) ? std::cout << "-> Foo and bar are not equal" << std::endl : 0;
	(foo < bar) ? std::cout << "-> Foo is less than bar" << std::endl : 0;
	(foo > bar) ? std::cout << "-> Foo is greater than bar" << std::endl : 0;
	(foo <= bar) ? std::cout << "-> Foo is less than or equal to bar" << std::endl : 0;
	(foo >= bar) ? std::cout << "-> Foo is greater than or equal to bar" << std::endl : 0;
	std::cout << std::endl;
}

void	testingPair(void) {
	pair<std::string, int> testInit1("Mehdi", 23); // Initialization constructor
	pair<std::string, int> testInit2("Melody", 12); // Initialization constructor
	pair<std::string, int> testCopy(testInit1); // Constructor by copy

	testingPairSwap();
	testingPairRationalOperators();
}

void	testingIsIntegral(void)
{
  	std::cout << std::boolalpha;
	std::cout << "-> Char: " <<  is_integral<char>::value << std::endl;
  	std::cout << "-> Int: " << is_integral<int>::value << std::endl;
  	std::cout << "-> Float: " << is_integral<float>::value << std::endl << std::endl;
}

class MyIterator : public iterator<input_iterator_tag, int>
{
	private:
  		int* _ptr;
	public:
		MyIterator(int* x) :_ptr(x) {}
		MyIterator(const MyIterator& mit) : _ptr(mit._ptr) {}
		MyIterator& operator++(void) { ++_ptr; return *this; }
		MyIterator operator++(int) { MyIterator tmp(*this); operator++(); return tmp; }
		bool operator==(const MyIterator& rhs) const { return _ptr == rhs._ptr; }
		bool operator!=(const MyIterator& rhs) const { return _ptr != rhs._ptr; }
		int& operator*(void) { return *_ptr;}
};

void	testingIteratorTraits(void) {
	int numbers[] = { 10, 20, 30, 40, 50};
	MyIterator from(numbers);
	MyIterator until(numbers + 5);
	std::cout << "-> Iterate on int[] : ";
	for (MyIterator it = from; it != until; it++)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void	testingVectorCapacity(vector<char> *test) {
	std::cout << "------------- [ CAPACITY ] --------------" << std::endl;
	std::cout << "-> Vector size : " << test->size() << std::endl;
	std::cout << "-> Vector max_size : " << test->max_size() << std::endl;
	std::cout << "-> Vector capacity : " << test->capacity() << std::endl;
	test->resize(2);
	std::cout << "-> After resize (from 4 to 2) : ";
	for (ft::vector<char>::iterator it = test->begin(); it != test->end(); it += 1)
		std::cout << *it << " ";
	std::cout << std::endl << "-> Vector size after resize : " << test->size() << std::endl;
	std::cout << "-> Vector max_size after resize : " << test->max_size() << std::endl;
	std::cout << "-> Vector capacity after resize : " << test->capacity() << std::endl;
	test->resize(6, 'b');
	std::cout << "-> After resize (from 2 to 6, val = 'b') : ";
	for (ft::vector<char>::iterator it = test->begin(); it != test->end(); it += 1)
		std::cout << *it << " ";
	std::cout << std::endl << "-> Vector size after resize : " << test->size() << std::endl;
	std::cout << "-> Vector max_size after resize : " << test->max_size() << std::endl;
	std::cout << "-> Vector capacity after resize : " << test->capacity() << std::endl;
	try {
		test->reserve(8);
		std::cout << "-> Vector size after reserve : " << test->size() << std::endl;
		std::cout << "-> Vector max_size after reserve : " << test->max_size() << std::endl;
		std::cout << "-> Vector capacity after reserve : " << test->capacity() << std::endl;
	}
	catch (std::length_error &exc) {
		std::cout << std::endl << "-> " <<  exc.what() << std::endl;
	}
}

void	testingVectorIterator(vector<char> *test) {
	vector<char>::iterator	start = test->begin();
	vector<char>::iterator	end = test->end();
	vector<char>::reverse_iterator rstart(test->rbegin());
	vector<char>::reverse_iterator rend(test->rend());

	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
	std::cout << "-> First element iterator : " << *start << std::endl;
	std::cout << "-> Last element iterator - 1 : " << *end << std::endl;
	std::cout << "-> Vector elements with iterator : ";
	while (start != end)
		std::cout << *start++ << " ";
	std::cout << std::endl;
	std::cout << "-> Vector elements with reverse iterator : ";
	while (rstart != rend)
		std::cout << *rstart++ << " ";
	std::cout << std::endl;
	try {
		std::cout << "-> At of 3 : " << test->at(3) << std::endl;
		std::cout << "-> At of 6 : " << test->at(6) << std::endl;
	}
	catch (std::out_of_range &exc) {
		std::cout << "error " << exc.what() << std::endl;
	}
	std::cout << "-> Front element : " << test->front() << std::endl;
	std::cout << "-> Back element : " << test->back() << std::endl;
}

void	testingVetorModifiers(vector<char> *test) {

	std::cout << "------------- [ MODIFIERS ] -------------" << std::endl;

	test->assign(10, 'c');
	std::cout << "-> Vector size after assign : " << test->size() << std::endl;
	std::cout << "-> Vector max_size after assign : " << test->max_size() << std::endl;
	std::cout << "-> Vector capacity after assign : " << test->capacity() << std::endl;
	std::cout << "-> Vector elements after assign : " << std::endl << "   ";
	for (vector<char>::iterator it = test->begin(); it != test->end(); it += 1)
		std::cout << *it << " ";
	std::cout << std::endl;
	test->push_back('d');
	std::cout << "-> Vector size after push_back : " << test->size() << std::endl;
	std::cout << "-> Vector max_size after push_back : " << test->max_size() << std::endl;
	std::cout << "-> Vector capacity after push_back : " << test->capacity() << std::endl;
	std::cout << "-> Vector elements after push_back : " << std::endl << "   ";
	for (vector<char>::iterator it = test->begin(); it != test->end(); it += 1)
		std::cout << *it << " ";
	test->pop_back();
	std::cout << std::endl << "-> Vector size after pop_back : " << test->size() << std::endl;
	std::cout << "-> Vector max_size after pop_back : " << test->max_size() << std::endl;
	std::cout << "-> Vector capacity after pop_back : " << test->capacity() << std::endl;
	std::cout << "-> Vector elements after pop_back : " << std::endl << "   ";
	for (vector<char>::iterator it = test->begin(); it != test->end(); it += 1)
		std::cout << *it << " ";
	vector<char>::iterator it1 = test->begin();
	test->insert(it1, 'd');
	std::cout << std::endl << "-> Vector elements after insert 'd' at beginning : " << std::endl << "   ";
	for (it1 = test->begin(); it1 < test->end(); it1 += 1)
		std::cout << *it1 << " ";
	it1 = test->begin();
	it1 = test->insert(it1 + 10 , 'e');
	std::cout << std::endl << "-> Vector elements after insert 'e' at position 10 : " << std::endl << "   ";
	for (it1 = test->begin(); it1 < test->end(); it1 += 1)
		std::cout << *it1 << " ";
	vector<char> it2 (5, 'f');
  	test->insert (it1 ,it2.begin(),it2.end());
	std::cout << std::endl << "-> Vector elements after insert 5 types 'f' at end : " << std::endl << "   ";
	for (it1 = test->begin(); it1 < test->end(); it1 += 1)
		std::cout << *it1 << " ";
	test->erase(test->begin() + 10);
	it1 = test->begin();
	std::cout << std::endl << "-> Vector elements after erasing 5th element ('e') : " << std::endl << "   ";
	for (it1 = test->begin(); it1 < test->end(); it1 += 1)
		std::cout << *it1 << " ";
	test->erase(test->begin() + 1, test->begin() + 11);
	it1 = test->begin();
	std::cout << std::endl << "-> Vector elements after erasing all 'c' : " << std::endl << "   ";
	for (it1 = test->begin(); it1 < test->end(); it1 += 1)
		std::cout << *it1 << " ";
	std::cout << std::endl;
}

void	testingVectorAllocator(void) {
	vector<int> test;
	int	*new_test = NULL;

	std::cout << "------------- [ ALLOCATOR ] -------------" << std::endl;

	new_test = test.get_allocator().allocate(5);
	for (int idx = 0; idx < 5; idx += 1)
		test.get_allocator().construct(&new_test[idx], idx);
	std::cout << "-> Vector after creation with get_allocator :" << std::endl << "   ";
	for (int idx = 0; idx < 5; idx += 1)
		std::cout << ' ' << new_test[idx];
	std::cout  << std::endl << std::endl;
	for (int idx = 0; idx < 5; idx += 1)
		test.get_allocator().destroy(&new_test[idx]);
	test.get_allocator().deallocate(new_test, 5);
}

void	testingVector(void) {
	vector<char>	test1;
	vector<char> 	test2(4, 'a');
	vector<char>	test3 = test2;
	vector<char>	test4(test3.begin(), test3.end());

	testingVectorCapacity(&test4);
	testingVectorIterator(&test4);
	testingVetorModifiers(&test4);
	testingVectorAllocator();
}

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

void	testingMapOperations(map<int, std::string> *test) {

}

void	testingMap(void) {
	map<int, std::string>	test1; //  Default constructor
	
	test1[1] = "One"; //  Operator[]
	test1[2] = "Two";
	test1[3] = "Three";

	testingMapIterator(&test1);
	// testingMapOperations(&test1);
}

int		main(void) {
	std::cout << "--------------- [ PAIR ] ----------------" << std::endl;
	testingPair();
	std::cout << "------------ [ IS ITEGRAL ] -------------" << std::endl;
	testingIsIntegral();
	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
	testingIteratorTraits();
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