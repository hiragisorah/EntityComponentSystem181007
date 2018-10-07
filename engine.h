#pragma once

#include "macros.h"
#include "manager.h"
#include "system.h"
#include "entity.h"
#include "component.h"

namespace ECS
{
	using SystemManager = Manager<ISystem>;
	using EntityManager = Manager<IEntity>;
	using ComponentManager = Manager<IComponent>;

	class Engine
	{
	private:
		SystemManager system_manager_;
		EntityManager entity_manager_;
		ComponentManager component_manager_;

	private:
		bool is_paused_;
		bool is_running_;
		float delta_time_;

	public:
		Engine(void)
			: delta_time_(1.f)
			, is_paused_(false)
			, is_running_(true)
		{}

	public:
		const bool & Run(void)
		{
			this->RemoveDestroyedDatas(this->system_manager_, this->entity_manager_, this->component_manager_);

			if (is_paused_)
			{
				this->_Pause(this->system_manager_, this->component_manager_);
			}
			else
			{
				this->_Update(this->system_manager_, this->component_manager_);
			}

			this->_Always(this->system_manager_, this->component_manager_);

			return this->is_running_;
		}

	private:
		void RemoveDestroyedDatas(void) {}
		template <class _MANAGER, class... _TAIL>
		void RemoveDestroyedDatas(_MANAGER && manager, _TAIL &&... tail)
		{
			manager.RemoveDestroyedDatas();
			this->RemoveDestroyedDatas(std::forward<_TAIL>(tail)...);
		}

		DO_ALL(Update);
		DO_ALL(Pause);
		DO_ALL(Always);
	};
}