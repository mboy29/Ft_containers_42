/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FtTestingStack.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:33:21 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:33:23 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./FtTesting.hpp"

void	testingStack(void) {
	std::vector<std::string>									test1(3, "VECTOR");
	std::stack<std::string, std::vector<std::string> >		test2(test1);

	std::cout << "-> Testing stack on following vector<std::string> :" << std::endl << "   ";
	for (std::vector<std::string>::iterator it = test1.begin(); it != test1.end(); it += 1)
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
