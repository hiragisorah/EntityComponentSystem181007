#pragma once

#include "i_component.h"

namespace ECS
{
	template<class _TYPE>
	class Component : public IComponent
	{
	public:
		Component(void)
			: IComponent(typeid(_TYPE))
		{}
	};
}