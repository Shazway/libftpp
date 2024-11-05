/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:48:38 by tmoragli          #+#    #+#             */
/*   Updated: 2024/11/05 02:21:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool_tester.hpp"

void testPool() {
	Pool<TestObject> pool;

	// Resize the pool and pre-allocate objects
	size_t initialSize = 5;
	pool.resize(initialSize);

	std::cout << "\nPool resized to " << initialSize << " objects.\n" << std::endl;
	// Acquire objects from the pool
	{
		auto obj1 = pool.acquire(10);
		std::cout << "Acquired object with value: " << obj1->value << std::endl;

		auto obj2 = pool.acquire(20);
		std::cout << "Acquired object with value: " << obj2->value << std::endl;

		auto obj3 = pool.acquire(30);
		std::cout << "Acquired object with value: " << obj3->value << std::endl;
	}  // Destructors of objects should be called
	std::cout << "\nObjects released back to the pool.\n" << std::endl;

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
	std::cout << "\nPool resized to " << newSize << " objects.\n" << std::endl;
	{
		auto obj6 = pool.acquire(60);
		std::cout << "Acquired object with value: " << obj6->value << std::endl;
	}

	// Resizing the pool with 0 objects and testing the exception throw
	newSize = 0;
	pool.resize(newSize);
	std::cout << "\nPool resized to " << newSize << " objects.\n" << std::endl;
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

int main()
{
	testPool();
	return 0;
}
