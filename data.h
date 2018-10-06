#pragma once

#include "i_data.h"

namespace ECS
{
	template<class _CATEGORY>
	class Data : public IData
	{
	public:
		Data(const std::type_index & type)
			: IData(typeid(_CATEGORY), type)
		{}
	};
}