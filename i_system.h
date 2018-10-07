#pragma once

#include "data.h"

namespace ECS
{
	class ISystem : public Data
	{
	public:
		ISystem(const std::type_index & type)
			: Data(type)
		{}

	public:
		virtual void Update(float & dt) {}
		virtual void Pause(float & dt) {}
		virtual void Always(float & dt) {}
	};
}