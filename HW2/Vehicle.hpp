#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Object.hpp"
#include <vector>
#include "Goods.hpp"

class Vehicle : public Object
{
public:
	using TGoodsCont = std::vector<Goods>;

	const TGoodsCont& getGoods() const { return m_goods; }

protected:
	Vehicle() = default;

private:
	TGoodsCont m_goods;
};

#endif