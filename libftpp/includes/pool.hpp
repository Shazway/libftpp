/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:36:40 by tmoragli          #+#    #+#             */
/*   Updated: 2024/11/05 19:32:05 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <vector>
#include <memory>
#include <stdexcept>

template <typename TType>
class Pool
{
	public:
		class Object {
			public:
				Object(Pool& pool, TType *ptr);
				~Object();

				TType *operator->();
				TType *operator*();
				Object(const Object&) = delete;
				Object &operator=(const Object&) = delete;

				Object(Object&& other) noexcept;
				Object& operator=(Object && other) noexcept;
			private:
				Pool& pool;
				TType *data;
		};

		void resize(const size_t &numberOfObjectStored);
		template <typename... TArgs>
		Object acquire(TArgs&&... args);
	private:
		std::vector<std::unique_ptr<TType>> pool;
		void release(TType *ptr);
};

//-------------------Pool methods implementations-------------------//
template <typename TType>
void Pool<TType>::resize(const size_t &numberOfObjectStored) {
	pool.resize(numberOfObjectStored);
	for (size_t i = 0; i < numberOfObjectStored; i++)
	{
		pool[i] = std::make_unique<TType>();
	}
}

template <typename TType>
template <typename... TArgs>
typename Pool<TType>::Object Pool<TType>::acquire(TArgs&&... args) {
	for (auto &item : pool)
	{
		if (item)
		{
			TType *newItem = item.release();
			new (newItem) TType(std::forward<TArgs>(args)...);
			return Object(*this, newItem);
		}
	}
	throw std::runtime_error("No available objects in pool.");
}

template <typename TType>
void Pool<TType>::release(TType *ptr) {
	ptr->~TType();
	for (auto &item : pool)
	{
		if (!item)
		{
			item.reset(ptr);
			break ;
		}
	}
}
//------------------------------------------------------------------//

//-------------------Object methods implementations-------------------//
template <typename TType>
Pool<TType>::Object::Object(Pool &pool, TType *ptr) : pool(pool), data(ptr) {
	return ;
}

template <typename TType>
Pool<TType>::Object::~Object() {
	if (data)
		pool.release(data);
}

template <typename TType>
TType *Pool<TType>::Object::operator->() {
	return data;
}

template <typename TType>
TType *Pool<TType>::Object::operator*() {
	return *data;
}

template <typename TType>
Pool<TType>::Object::Object(Object &&other) noexcept : pool(other.pool), data(other.data) {
	other.data = nullptr;
}

template <typename TType>
typename Pool<TType>::Object &Pool<TType>::Object::operator=(Object&& other) noexcept {
	if (this != &other)
	{
		if (data)
			pool.release(data);
		data = other.data;
		other.data = nullptr;
	}
	return *this;
}

//------------------------------------------------------------------//
