#pragma once

#include "i_entity.h"

namespace ECS
{
	template<class _TYPE>
	class Entity : public IEntity
	{
	public:
		Entity(void)
			: IEntity(typeid(_TYPE))
		{}

	};
}