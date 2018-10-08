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
		template<class _COMPONENT>
		_COMPONENT * const GetComponent(void)
		{
			auto itr = this->component_list_.find(typeid(_COMPONENT));
			if (itr != this->component_list_.end())
			{
				auto component_id = (*itr).second;
				return this->component_manager_->GetById<_COMPONENT>(component_id);
			}
			else
			{
				return nullptr;
			}
		}

		template<class _COMPONENT, class ... _ARGS>
		_COMPONENT * const AddComponent(const _ARGS &... args)
		{
			auto component = this->component_manager_->Add<_COMPONENT>(args ...);
			auto component_id = component->id();
			this->component_list_[typeid(_COMPONENT)] = component_id;
		}
	};
}