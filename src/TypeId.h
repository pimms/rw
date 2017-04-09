#pragma once

#include <typeinfo>

typedef const std::type_info* TypeId;

template<class BaseT, class SubT>
inline TypeId GetTypeId()
{
    static_assert(std::is_base_of<BaseT,SubT>::value, "SubT must be a base of BaseT");
    return &typeid(SubT);
}

