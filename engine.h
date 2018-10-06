#pragma once

#include "manager.h"
#include "i_system.h"
#include "i_entity.h"
#include "i_component.h"

namespace ECS
{
	class Engine
	{
	private:
		Manager manager_;

	public:
		void Run(void)
		{
			auto & id_list = this->manager_.GetIdListByCategory<ISystem>();

			for (auto & id : id_list)
				this->manager_.GetById<ISystem>(id)->Update();

			auto & id_list = this->manager_.GetIdListByCategory<IComponent>();

			for (auto & id : id_list)
				this->manager_.GetById<IComponent>(id)->Update();
		}
	};
}