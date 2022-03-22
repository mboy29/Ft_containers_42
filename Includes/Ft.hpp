#ifndef FT_HPP
# define FT_HPP
# include <iostream> //std::cout

//  ----------------------------UTILITIES--------------------------------
//    -> Iterator bass class, iterator category tags, iterator_traits,
//       input / output / forward / bidirectional / random access /
//       reverse iterator ;
//    -> Enable_if ;
//    -> Pair class, make_pair function ;
//    -> Lexicographical_compare ;
//    -> Integral constant class, is integral class ;
//    -> Binary search trees (for map container);
//  ---------------------------------------------------------------------

# include "./Utilities/Enable_if.hpp"
# include "./Utilities/Algorithm.hpp"
# include "./Utilities/Pair.hpp"
# include "./Utilities/Compare.hpp"
# include "./Utilities/Integral.hpp"
# include "./Utilities/Trees/Map_node.hpp"
# include "./Utilities/Trees/Map_tree.hpp"
# include "./Utilities/Trees/Set_node.hpp"
# include "./Utilities/Trees/Set_tree.hpp"
# include "./Utilities/Iterators/Iterator.hpp"
# include "./Utilities/Iterators/Bidirectional_iterator.hpp"
# include "./Utilities/Iterators/Random_access_iterator.hpp"
# include "./Utilities/Iterators/Reverse_iterator.hpp"
# include "./Utilities/Iterators/Map_iterator.hpp"
# include "./Utilities/Iterators/Set_iterator.hpp"


//  ----------------------------CONTAINERS-------------------------------
//    -> Vector ;
//    -> Map ;
//    -> Stack.
//  ---------------------------------------------------------------------

# include "./Containers/Vector.hpp"
# include "./Containers/Stack.hpp"
# include "./Containers/Map.hpp"
# include "./Containers/Set.hpp"

#endif