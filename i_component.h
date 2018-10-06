#pragma once

#include "data.h"

namespace ECS
{
	class IComponent : public Data<IComponent>
	{
	public:
		IComponent(const std::type_index & type);

	private:
		unsigned int owner_id_;

	public:
		void set_owner_id(const unsigned int & owner_id);
		const unsigned int & owner_id(void) const;

	public:
		virtual void Update(void);
	};
}