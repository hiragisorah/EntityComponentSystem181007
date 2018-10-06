#pragma once

#include "data.h"

namespace ECS
{
	class IEntity : public Data<IEntity>
	{
	public:
		IEntity(const std::type_index & type)
			: Data(type)
		{}

	private:
		
	};
}