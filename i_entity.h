#pragma once

#include "data.h"
#include "manager.h"

#include "component.h"

namespace ECS
{
	class IEntity;
	using EntityManager = Manager<IEntity>;
	using ComponentManager = Manager<IComponent>;

	class IEntity : public Data
	{
	public:
		IEntity(const std::type_index & type)
			: Data(type)
		{}

	private:
		std::unordered_map<std::type_index, unsigned int> component_list_;

	private:
		ComponentManager * component_manager_;
		EntityManager * entity_manager_;

	public:
		template<class _Component>
		_Component * const GetComponent(void)
		{
			if (this->component_list_.find(typeid(_Component)) != this->component_list_.end())
			{
				
			}
			else
			{
				return nullptr;
			}
		}
	};
}