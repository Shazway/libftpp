/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:48:38 by tmoragli          #+#    #+#             */
/*   Updated: 2024/11/08 21:05:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool_tester.hpp"

void testPool() {
	Pool<TestObject> pool;

	// Resize the pool and pre-allocate objects
	size_t initialSize = 5;
	pool.resize(initialSize);

	std::cout << "\nPool resized to " << initialSize << " objects." << std::endl;
	// Acquire objects from the pool
	{
		auto obj1 = pool.acquire(10);
		std::cout << "Acquired object with value: " << obj1->value << std::endl;

		auto obj2 = pool.acquire(20);
		std::cout << "Acquired object with value: " << obj2->value << std::endl;

		auto obj3 = pool.acquire(30);
		std::cout << "Acquired object with value: " << obj3->value << std::endl;
	}  // Destructors of objects should be called
	std::cout << "\nObjects released back to the pool." << std::endl;

	// Acquire again to check reusability
	{
		auto obj4 = pool.acquire(40);
		std::cout << "Re-acquired object with value: " << obj4->value << std::endl;

		auto obj5 = pool.acquire(50);
		std::cout << "Re-acquired object with value: " << obj5->value << std::endl;
	}

	// Resizing the pool after usage
	size_t newSize = 3;
	pool.resize(newSize);
	std::cout << "\nPool resized to " << newSize << " objects." << std::endl;
	{
		auto obj6 = pool.acquire(60);
		std::cout << "Acquired object with value: " << obj6->value << std::endl;
	}

	// Resizing the pool with 0 objects and testing the exception throw
	newSize = 0;
	pool.resize(newSize);
	std::cout << "\nPool resized to " << newSize << " objects." << std::endl;
	{
		try
		{
			auto obj6 = pool.acquire(5);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

void testDb()
{
	DataBuffer db;
	std::cout << "Initialising i with value 50" << std::endl;
	int i = 50;

	std::cout << "Serializing i with value 50 into the data buffer" << std::endl;
	db << i;
	std::cout << "Changing i with value 0" << std::endl;
	i = 0;
	std::cout << "Deserializing the contents of the data buffer into i" << std::endl;
	db >> i;
	std::cout << "Result of i value " << i << std::endl;

	std::cout << "Initialising j with value 42.42" << std::endl;
	double j = 42.42;

	std::cout << "Serializing j with value 42.42 into the data buffer" << std::endl;
	db << j;
	std::cout << "Changing j with value 0.0" << std::endl;
	j = 0.0;
	std::cout << "Deserializing the contents of the data buffer into j" << std::endl;
	db >> j;
	std::cout << "Result of j value " << j << std::endl;
}

int main()
{
	//Pool tests
	std::cout << "Testing pool" << std::endl;
	std::cout << "-----------------" << std::endl;
	testPool();
	std::cout << "End of pool tests" << std::endl;
	std::cout << "-----------------" << std::endl;

	//DataBuffer tests
	std::cout << "Testing data buffer" << std::endl;
	std::cout << "-----------------" << std::endl;
	testDb();
	std::cout << "End of data buffer tests" << std::endl;
	std::cout << "-----------------" << std::endl;

	return 0;
}
