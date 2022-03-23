/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FtTesting.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:33:14 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:33:15 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TESTING_HPP
# define FT_TESTING_HPP
# include <stdlib.h>
# include <iostream>

# include <map>
# include <stack>
# include <vector>

void	testingVector(void);
void	testingVectorCapacity(std::vector<char> *test);
void	testingVectorIterator(std::vector<char> *test);
void	testingVetorModifiers(std::vector<char> *test);
void	testingVectorAllocator(void);

void	testingStack(void);
void	testingMap(void);

void	testingMapIterator(std::map<int, std::string> *test);
void	testingMapCapacity(std::map<int, std::string> *test);

#endif
