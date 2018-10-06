#pragma once

#include "i_data.h"

#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ECS
{
	class Manager final
	{
	public:
		using IdList = std::vector<unsigned int>;

	public:
		Manager(void)
			: current_id_(static_cast<unsigned int>(0))
		{

		}

		~Manager(void)
		{
			for (auto&[key, value] : this->data_list_by_id_)
				if (value != nullptr)
					delete value;
		}

	private:
		unsigned int current_id_;
		IdList unused_id_list_;
		std::unordered_map<unsigned int, IData*> data_list_by_id_;
		std::unordered_map<std::type_index, IdList> id_list_by_type_;
		std::unordered_map<std::type_index, IdList> id_list_by_category_;

	public:
		template<class _CLASS, class ... _ARGS>
		_CLASS * const Add(const _ARGS &... args)
		{
			_ID id = static_cast<_ID>(0);

			if (this->unused_id_list_.size())
			{
				id = this->unused_id_list_.back();
				this->unused_id_list_.pop_back();
			}
			else
			{
				id = this->current_id_++;
			}

			auto data = new _CLASS(args ...);

			this->id_list_by_category_[data->category()].emplace_back(id);
			this->id_list_by_type_[data->type()].emplace_back(id);
			this->data_list_by_id_[id] = data;

			return data;
		}
		void Remove(IData * const data)
		{
			{
				auto & list = this->id_list_by_category_[data->category()];
				auto itr = std::remove_if(list.cbegin(), list.cend(), [](auto & id) { id == data->id(); });
				list.erase(itr, list.end());
			}

			{
				auto & list = this->id_list_by_type_[data->type()];
				auto itr = std::remove_if(list.cbegin(), list.cend(), [](auto & id) { id == data->id(); });
				list.erase(itr, list.end());
			}

			this->data_list_by_id_.erase(data->id());
		}

		void RemoveById(const unsigned int & id)
		{
			auto & data = this->data_list_by_id_[id];

			this->Remove(data);
		}

		template<class _CATEGORY>
		const IdList & GetIdListByCategory(void)
		{
			return this->id_list_by_category_[typeid(_CATEGORY)];
		}

		template<class _TYPE>
		const IdList & GetIdListByType(void)
		{
			return this->id_list_by_type_[typeid(_TYPE)];
		}

		template<class _CLASS>
		_CLASS * const GetById(const unsigned int & id)
		{
			return static_cast<_CLASS*>(this->data_list_by_id_[id]);
		}
	};
}