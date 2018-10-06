#pragma once

#include "data.h"

namespace ECS
{
	class ISystem : public Data<ISystem>
	{
	public:
		ISystem(const std::type_index & type);

	public:
		virtual void Update(void);
	};
}