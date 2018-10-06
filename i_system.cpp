#include "i_system.h"

ECS::ISystem::ISystem(const std::type_index & type)
	: Data(type)
{
}

void ECS::ISystem::Update(void)
{
}
