#pragma once

#include "data.h"

#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ECS
{
	template<class _DATA>
	class Manager final
	{
	public:
		using IdList = std::vector<unsigned int>;
		using DataList = std::vector<_DATA*>;

	public:
		Manager(void)
			: current_id_(0U)
		{

		}

		~Manager(void)
		{
			for (auto data : this->data_list_)
				if (data != nullptr)
					delete data;
		}

	private:
		unsigned int current_id_;
		IdList unused_id_list_;
		DataList data_list_;
		std::unordered_map<std::type_index, DataList> data_list_by_type_;

	public:
		template<class _CLASS, class ... _ARGS>
		_CLASS * const Add(const _ARGS &... args)
		{
			unsigned int id = 0;

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

			this->data_list_by_type_[data->type()].emplace_back(data);
			this->data_list_by_id_[id] = data;

			return data;
		}

		void Remove(_DATA * const data)
		{
			auto & list = this->data_list_by_type_[data->type()];
			auto itr = std::remove_if(list.begin(), list.end(), [data](auto & tmp) { return tmp == data; });
			list.erase(itr, list.end());

			auto & id = data->id();
			delete this->data_list_[id];
			this->data_list_[id] = nullptr;
			this->unused_id_list_.emplace_back(id);
		}

		void RemoveById(const unsigned int & id)
		{
			auto & data = this->data_list_[id];

			this->Remove(data);
		}

		const DataList & GetList(void)
		{
			return this->data_list_;
		}

		template<class _TYPE>
		const DataList & GetListByType(void)
		{
			return this->data_list_by_type_[typeid(_TYPE)];
		}

		template<class _CLASS>
		_CLASS * const GetById(const unsigned int & id)
		{
			return static_cast<_CLASS*>(this->data_list_[id]);
		}

	public:
		void RemoveDestroyedDatas(void)
		{
			std::for_each(this->data_list_.cbegin(), this->data_list_.cend(), [this](auto & data)
			{
				if (data->IsAlive())
					this->Remove(data);
			});
		}
	};
}