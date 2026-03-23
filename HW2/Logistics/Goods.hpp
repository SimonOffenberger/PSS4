/*****************************************************************//**
 * \file   Goods.hpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#ifndef GOODS_HPP
#define GOODS_HPP

#include <string>
#include "Object.hpp"
#include <iostream>

class Goods : public Object
{
public:
	inline static const std::string ERROR_INVALID_ARGUMENT = "weight and value must be non-negative";
	inline static const std::string ERROR_BAD_OSTERAM = "Output stream is in a failed state";

	double getWeight() const { return m_weight; }

	double getValue() const { return m_value; }

protected :
	Goods(const double weight, const double value);

private:
	double m_weight;
	double m_value;
};

std::ostream& operator<<(std::ostream& os, const Goods& goods);

#endif