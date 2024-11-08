/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_buffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:30:59 by tmoragli          #+#    #+#             */
/*   Updated: 2024/11/06 00:51:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_buffer.hpp"

const std::vector<uint8_t> &DataBuffer::getBuffer() const {
	return buffer;
}

void DataBuffer::clear() {
	buffer.clear();
}
