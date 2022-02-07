#include "./../Includes/Ft.hpp"
#include "vector"

using namespace Ft;

void	testingPairSwap(void) {
	pair<std::string, int> testInit1("Mehdi", 23); // Initialization constructor
	pair<std::string, int> testInit2("Melody", 12); // Initialization constructor
	pair<int,char> foo (10,'z');
	pair<int,char> bar (90,'a');
	
	std::cout << "------------- [ PAIR SWAP ] -------------" << std::endl;
	std::cout << "-> Before Swap Pairs 1: " << testInit1.first << " - " << testInit1.second << std::endl;
	std::cout << "-> Before Swap Pairs 2: " << testInit2.first << " - " << testInit2.second << std::endl;
	std::cout << "-> After Swap Pairs 1: " << testInit1.first << " - " << testInit1.second << std::endl;
	std::cout << "-> After Swap Pairs 2: " << testInit2.first << " - " << testInit2.second << std::endl;
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
	reverse_iterator<MyIterator>	rev_until(from);
	reverse_iterator<MyIterator>	rev_from(until);
	std::cout << "-> Reverse iterate on int[] : ";
	for (reverse_iterator<MyIterator> rev_it = rev_from; rev_it != rev_until; rev_it++)
		std::cout << *rev_it << ' ';
	std::cout << std::endl << std::endl;
}

void	testingVector(void) {
	vector<int>				test1;
	vector<int>  			test2(4, 1);
	vector<int>				test3 = test2;
	vector<int>				test4(test3.begin(), test3.end());
	vector<int>::iterator	start = test4.begin();
	vector<int>::iterator	end = test4.end();
	//vector<int>::reverse_iterator	rstart = test4.rbegin();


	std::cout << "------------- [ CAPACITY ] --------------" << std::endl;
	std::cout << "-> Vector size : " << test4.size() << std::endl;
	std::cout << "-> Vector max_size : " << test4.max_size() << std::endl;
	std::cout << "-> Vector capacity : " << test4.capacity() << std::endl;
	test4.resize(2);
	std::cout << "-> After resize (from 4 to 2) : ";
	for (Ft::vector<int>::iterator it = test4.begin(); it != test4.end(); it += 1)
		std::cout << *it << " ";
	test4.resize(6, 2);
	std::cout << std::endl << "-> After resize (from 2 to 6) : ";
	for (Ft::vector<int>::iterator it = test4.begin(); it != test4.end(); it += 1)
		std::cout << *it << " ";
	try {
		test4.reserve(8);
		std::cout << std::endl << "-> Vector size after reserve : " << test4.size() << std::endl;
		std::cout << "-> Vector max_size after reserve : " << test4.max_size() << std::endl;
		std::cout << "-> Vector capacity after reserve : " << test4.capacity() << std::endl;
	}
	catch (std::length_error exc) {
		std::cout << std::endl <<  exc.what() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
	std::cout << "-> First element iterator : " << *start << std::endl;
	std::cout << "-> Last element iterator : " << *end << std::endl;
	std::cout << "-> Vector elements with iterator : ";
	while (start != end)
		std::cout << *start++ << " ";
}

int		main(void) {
	pair<std::string, int> testInit1("Mehdi", 23); // Initialization constructor
	pair<std::string, int> testInit2("Melody", 12); // Initialization constructor
	pair<std::string, int> testCopy(testInit1); // Constructor by copy
	
	std::cout << "--------------- [ PAIR ] ----------------" << std::endl;
	testingPairSwap();
	std::cout << "------------ [ IS ITEGRAL ] -------------" << std::endl;
	testingIsIntegral();
	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
	testingIteratorTraits();
	std::cout << "-------------- [ VECTOR ] ---------------" << std::endl;
	testingVector();
	return (0);
}