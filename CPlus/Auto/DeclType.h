#pragma once
#include "CPlus/Global.h"
#include <vector>
#include <utility>
#include <iostream>

namespace CPlus
{
	namespace Auto 
	{
		template <typename Container, typename Index>
		auto GetValue(Container&& c, Index i)
			->decltype(std::forward<Container>(c)[i])
		{
			return  std::forward<Container>(c)[i];
		}
	}

}

