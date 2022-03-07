#include <iostream>
#include "vector.hpp"
#include <vector>

#include "map.hpp"
#include <map>

#include "stack.hpp"
#include <stack>

#include "set.hpp"
#include <set>

#ifndef NS
#define NS ft
#endif
template <typename T>
void printAttribut(NS::vector<T> vect, std::string str){

	typename NS::vector<T>::iterator it = vect.begin();
	typename NS::vector<T>::iterator ite = vect.end();

	std::cout <<  "\e[032m" << str << ":  " << "\e[0m " << std::endl;
	std::cout << "Size: " << vect.size() << std::endl;
	std::cout << "Max: " << vect.max_size() << std::endl;
	std::cout << "Is empty: " << vect.empty() << std::endl;

	while(it != ite){
		std::cout << *it << std::endl;
		it++;
	}
}

template <typename T>
void	printVal(const T &iterator)
{
	std::cout << "key: " << iterator->first << " | value: " << iterator->second << "\n";
}
template <typename T>
void	printValSet(const T &iterator)
{
	std::cout << "key: " << *iterator  << "\n";
}

template <typename T>
void fill(NS::vector<T> &vect, int nbr){
	for(int i=1; i < nbr; i++){
		vect.push_back(i * 5);
	}
}

int main(void) {
	/*  Vector  */
	NS::vector<int> vect;
	NS::vector<int> vect2;
	
	fill(vect, 10);
	printAttribut(vect, "vect");
	printAttribut(vect2, "vect2");
	vect2 = vect;
	printAttribut(vect2, "vect2 after copying vect");
	vect.resize(15, 42);
	vect2.reserve(25);

	printAttribut(vect, "vect");
	printAttribut(vect2, "vect2");

	vect.erase(vect.begin() + 1, vect.begin() + 5);
	vect2.clear();
	vect.swap(vect2);
	printAttribut(vect, "vect");
	printAttribut(vect2, "vect2");

	vect.insert(vect.begin(), vect2.begin(), vect2.end());
	printAttribut(vect, "vect");

	fill(vect, 12);
	fill (vect2, 12);

	printAttribut(vect, "vect");
	printAttribut(vect2, "vect2");

	/* map */
	{
		NS::map<int, int> mp;
		for(int i=0; i < 10; i++)
			mp.insert(NS::make_pair(i, i));

		NS::map<int, int> mp2;
		mp2.insert(mp.begin(), mp.end());
		NS::map<int, int>::iterator it = mp.begin();
		printVal(it++);
		printVal(it--);
		printVal(++it);
		printVal(it--);
		printVal(it++);
		printVal(it++);
		printVal(it++);
		printVal(it++);
		printVal(it++);
		std::cout << "REVERSE: " << std::endl;
		NS::map<int, int>::reverse_iterator rev = mp.rbegin();
		printVal(rev++);
		printVal(rev++);
		printVal(rev++);
		printVal(rev++);
		printVal(--rev);
		printVal(rev--);
		printVal(rev--);
		printVal(rev--);

		NS::map<int, int>::iterator it_a = mp.begin();
		NS::map<int, int>::iterator it_b = mp2.begin();

		mp2.swap(mp);

		std::cout << (it_a == mp2.begin()) << "\n";
		std::cout << (it_b == mp.begin()) << "\n";
		std::cout << (it_b == mp2.begin()) << "\n";
		mp2.clear();

		std::cout << "is empty:" << mp2.empty() << "\n";
		std::cout << "is empty:" << mp.empty() << "\n";
	}

	/* Stack */
	NS::stack<int> stck;
	for(int i=0; i < 10; i++){
		stck.push(i * 7);
	}
	std::cout << "size: " << stck.size() << "\n";
	while (!stck.empty()){
		std::cout << "top: " << stck.top() << "\n";
		stck.pop();
	}
	std::cout << "size: " << stck.size() << "\n";
	
	/* set */
	NS::set<int> mp;
	for(int i=0; i < 10; i++)
		mp.insert(i);
	
	NS::set<int> mp2;
	mp2.insert(mp.begin(), mp.end());
	NS::set<int>::iterator it = mp.begin();
	printValSet(it++);
	printValSet(it--);
	printValSet(++it);
	printValSet(it--);
	printValSet(it++);
	printValSet(it++);
	printValSet(it++);
	printValSet(it++);
	printValSet(it++);

	std::cout << "probeleme: \n";
	NS::set<int>::reverse_iterator rev = mp.rbegin();
	std::cout << "ITERATOR: " << *rev << std::endl;
	printValSet(rev++);
	printValSet(rev++);
	printValSet(rev++);
	printValSet(rev++);
	printValSet(--rev);
	printValSet(rev--);
	
	NS::set<int>::iterator it_a = mp.begin();
	NS::set<int>::iterator it_b = mp2.begin();

	mp2.swap(mp);

	std::cout << (it_a == mp2.begin()) << "\n";
	std::cout << (it_b == mp.begin()) << "\n";
	std::cout << (it_b == mp2.begin()) << "\n";
	mp2.clear();

	std::cout << "is empty:" << mp2.empty() << "\n";
	std::cout << "is empty:" << mp.empty() << "\n";

	return (0);
}