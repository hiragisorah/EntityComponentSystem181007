#pragma once

#include <typeindex>

namespace ECS
{
	class IData
	{
	public:
		IData(const std::type_index & category, const std::type_index & type)
			: category_(category)
			, type_(type)
			, id_(0)
		{}
		virtual ~IData(void) {}

	public:
		const std::type_index & category(void) { return this->category_; }
		const std::type_index & type(void) { return this->type_; }
		const unsigned int & id(void) { return this->id_; }

		void set_id(const unsigned int & id) { this->id_ = id; }

	private:
		std::type_index category_;
		std::type_index type_;
		unsigned int id_;
	};
}