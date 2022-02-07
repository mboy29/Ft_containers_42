#include "./../Includes/Ft.hpp"

using namespace Ft;

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
	std::cout << "----- [ PAIR RELATIONAL OPERATORS ] -----" << std::endl;
	pair<int,char> foo (10,'z');
	pair<int,char> bar (90,'a');
	
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
	std::cout << "------------ [ IS ITEGRAL ] -------------" << std::endl;
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

	std::cout << "------------- [ ITERATOR ] --------------" << std::endl;
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
	vector<int>  			test2(4, 100);
	vector<int>				test3 = test2;
	vector<int>				test4(test3.begin(), test3.end());
	vector<int>::iterator			start = test4.begin();
	vector<int>::iterator			end = test4.end();


	std::cout << "-------------- [ VECTOR ] ---------------" << std::endl;
	std::cout << "-> Vector size : " << test4.size() << std::endl;
	std::cout << "-> Vector max_size : " << test4.max_size() << std::endl;
	std::cout << "-> Vector capacity : " << test4.capacity() << std::endl;
	std::cout << "-> First element iterator : " << *start << std::endl;
	std::cout << "-> Last element iterator : " << *end << std::endl;
	std::cout << "-> Vector elements with iterator : ";
	while (start != end)
		std::cout << *start++ << " ";
	std::cout << std::endl;
	
}

int		main(void) {
	pair<std::string, int> testInit1("Mehdi", 23); // Initialization constructor
	pair<std::string, int> testInit2("Melody", 12); // Initialization constructor
	pair<std::string, int> testCopy(testInit1); // Constructor by copy
	
	std::cout << "--------------- [ PAIR ] ----------------" << std::endl;
	testingPairSwap();
	testingPairRationalOperators();
	testingIsIntegral();
	testingIteratorTraits();
	testingVector();
	return (0);
}