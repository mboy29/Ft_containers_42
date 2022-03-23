/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FtMain.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:33:08 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:33:12 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./FtTesting.hpp"

int		main(void) {
	std::cout << "-------------- [ TESTING ] --------------" << std::endl << std::endl;
	std::cout << "-------------- [ VECTOR ] ---------------" << std::endl;
	testingVector();
	std::cout << "--------------- [ STACK ] ---------------" << std::endl;
	testingStack();
	std::cout << std::endl << "---------------- [ MAP ] ----------------"  << std::endl;
	testingMap();
	std::cout << std::endl << "--------------- [ LEAKS ] ---------------"  << std::endl;
	system("leaks FT");
	return (0);
}
