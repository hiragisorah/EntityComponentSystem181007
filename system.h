#pragma once

#include "i_system.h"

namespace ECS
{
	template<class _TYPE>
	class System : public ISystem
	{
	public:
		System(void)
			: ISystem(typeid(_TYPE))
		{}
	};
}