#pragma once

#include <typeindex>

namespace ECS
{
	class Data
	{
	public:
		Data(const std::type_index & type)
			: type_(type)
			, id_(0)
			, is_alive_(true)
		{}
		virtual ~Data(void) {}

	public:
		const std::type_index & type(void) { return this->type_; }
		const unsigned int & id(void) { return this->id_; }

		void set_id(const unsigned int & id) { this->id_ = id; }

	private:
		std::type_index type_;
		unsigned int id_;

	private:
		bool is_alive_;

	public:
		void Destroy(void)
		{
			this->is_alive_ = false;
		}

		const bool & IsAlive(void)
		{
			return this->is_alive_;
		}
	};
}