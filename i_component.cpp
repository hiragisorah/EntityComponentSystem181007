#include "i_component.h"

ECS::IComponent::IComponent(const std::type_index & type)
	: Data(type)
{
}

void ECS::IComponent::set_owner_id(const unsigned int & owner_id)
{
	this->owner_id_ = owner_id;
}

const unsigned int & ECS::IComponent::owner_id(void) const
{
	return this->owner_id_;
}

void ECS::IComponent::Update(void)
{
}
