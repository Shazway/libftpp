/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_tester.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:39:28 by tmoragli          #+#    #+#             */
/*   Updated: 2024/10/30 01:27:14 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libftpp.hpp"
#include <iostream>

class TestObject {
public:
	int value;
	TestObject(int val = 0) : value(val) {
		std::cout << "Object constructed with value " << value << std::endl;
	}
	~TestObject() {
		std::cout << "Object with value " << value << " destructed" << std::endl;
	}
};
