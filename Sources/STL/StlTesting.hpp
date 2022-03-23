/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StlTesting.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:33:37 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:33:38 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_TESTING_HPP
# define STL_TESTING_HPP
# include <stdlib.h>
# include <iostream>

# include "./../../Includes/Containers/Vector.hpp"
# include "./../../Includes/Containers/Stack.hpp"
# include "./../../Includes/Containers/Map.hpp"

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
