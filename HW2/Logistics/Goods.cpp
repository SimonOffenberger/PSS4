/*****************************************************************//**
 * \file   Goods.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "Goods.hpp"
#include <stdexcept>

Goods::Goods(const double weight, const double value)
{
	if (weight <= 0 || value <= 0)
	{
		throw std::invalid_argument(Goods::ERROR_INVALID_ARGUMENT);
	}

	m_weight = weight;
	m_value = value;
}

std::ostream& operator<<(std::ostream& os, const Goods& goods)
{
	if (os.fail()) {
		throw std::ios_base::failure(Goods::ERROR_BAD_OSTERAM);
	}

	os << "Goods(weight: " << goods.getWeight() << ", value: " << goods.getValue() << ")" << std::endl;

	return os;
}
