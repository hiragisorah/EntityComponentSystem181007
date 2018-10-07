#pragma once

#define DO_ALL(XXX) \
void _##XXX(void) {} \
template <class _MANAGER, class... _TAIL> \
void _##XXX(_MANAGER && manager, _TAIL &&... tail) \
{ \
	auto & list = manager.GetList(); \
 \
	for (auto & data : list) \
		data->##XXX(this->delta_time_); \
 \
	this->_##XXX(std::forward<_TAIL>(tail)...); \
}