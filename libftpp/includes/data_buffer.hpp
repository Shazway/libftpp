/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_buffer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:30:51 by tmoragli          #+#    #+#             */
/*   Updated: 2024/11/06 00:51:54 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <cstdint>
#include <sstream>
#include <type_traits>

class DataBuffer {
	public:
		template <typename T>
		DataBuffer &operator<<(const T &data);
		template <typename T>
		DataBuffer &operator>>(T& data);

		const std::vector<uint8_t> &getBuffer() const;
		void clear();
	private:
		std::vector<uint8_t> buffer;
};

template <typename T>
DataBuffer &DataBuffer::operator<<(const T &data) {
	static_assert(std::is_trivially_copyable<T>::value, "Data must be trivially copyable");

	std::ostringstream oss;
	oss.write(reinterpret_cast<const char *>(&data), sizeof(T));

	const std::string &str = oss.str();
	buffer.insert(buffer.end(), str.begin(), str.end());

	return *this;
}

template <typename T>
DataBuffer &DataBuffer::operator>>(T &data) {
	static_assert(std::is_trivially_copyable<T>::value, "Data must be trivially copyable");
	size_t typeSize = sizeof(T);

	if (buffer.size() < typeSize)
		throw std::runtime_error("Not enough data in buffer for deserialize");

	std::istringstream iss(std::string(buffer.begin(), buffer.begin() + typeSize));
	iss.read(reinterpret_cast<char *>(&data), typeSize);
	buffer.erase(buffer.begin(), buffer.begin() + typeSize);

	return *this;
}