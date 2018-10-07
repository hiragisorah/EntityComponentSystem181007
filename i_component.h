#pragma once

#include "data.h"

namespace ECS
{
	class IComponent : public Data
	{
	public:
		IComponent(const std::type_index & type)
			: Data(type)
		{}

	private:
		unsigned int owner_id_;

	public:
		void set_owner_id(const unsigned int & owner_id) { this->owner_id_ = owner_id; }
		const unsigned int & owner_id(void) const { return this->owner_id_; }

	public:
		virtual void Update(float & dt) {}
		virtual void Pause(float & dt) {}
		virtual void Always(float & dt) {}
	};
}