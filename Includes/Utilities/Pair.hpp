#ifndef PAIR_HPP
# define PAIR_HPP

//  -------------------------PAIR RE-IMPLATATION-------------------------
// |  -> Class Template									                 |
// |  A pair couples together a pair of values, which may be of          |
// |  different types (T1 and T2). The individual values can be accessed |
// |  through its public members first and second.                       |
//  ---------------------------------------------------------------------

namespace Ft 
{
	//  ---------------------------CLASS---------------------------------
	
	template <class T1, class T2>
	struct pair {
		public:
			//  Member types :
			typedef T1	first_type; 
			typedef T2	second_type;

			//  Member variables ;
			first_type	first; 
			second_type	second;
			
			//  Default constructor :
			pair(void) : first(), second() {} 

			//  Copy constructor :
			template<class U, class V>
			pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
			
			//	Initialization constructor :
			pair (const first_type& a, const second_type& b): first(a), second(b) {}
			
			//  Operator= :
			pair&	operator=(pair const& pr) {
				if (*this != pr) {
					this->first(pr.first);
					this->second(pr.second);
				}
				return (*this);
			}

			//   Member function - swap :
			void swap(pair const& pr) {
				this->first = pr.first;
				this->second = pr.second;
			}
	};

	//  -----------------------RATIONAL OPERATORS------------------------
	
	template <class T1, class T2> //Operator==
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}
	template <class T1, class T2> //Operator!=
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs==rhs);
	}
	template <class T1, class T2> //Operator<
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second));
	}
	template <class T1, class T2> //Operator<=
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs<lhs);
	}
	template <class T1, class T2> //Operator>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return rhs<lhs;
	}
	template <class T1, class T2> //Operator>=
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs<rhs);
	}

	//  --------------------------MAKE_PAIR------------------------------
	// |  -> Function Template                                           |
	// |  Constructs a pair object with its first element set to x and   |
	// |  its second element set to y.                                   |
	//  -----------------------------------------------------------------

	template <class T1, class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y) {
		  return (pair<T1, T2>(x, y));
	};
}

#endif