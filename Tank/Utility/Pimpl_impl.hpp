#ifndef TANK_PIMPL_IMPL_HPP
#define TANK_PIMPL_IMPL_HPP

#ifndef TANK_PIMPL_HPP
#error "You've included Pimpl_impl.hpp without including Pimpl.hpp!"
#endif

#include <utility>

namespace tank {

template<typename T>
Pimpl<T>::Pimpl() : ptr{new T{}}
{
}

template<typename T>
template<typename ...Args>
Pimpl<T>::Pimpl( Args&& ...args )
    : ptr{new T{std::forward<Args>(args)...}}
{
}

template<typename T>
Pimpl<T>::~Pimpl() = default;

template<typename T>
T* Pimpl<T>::operator->()
{
    return ptr.get();
}

template<typename T>
T& Pimpl<T>::operator*()
{
    return *ptr.get();
}

template<typename T>
const T* Pimpl<T>::operator->() const
{
    return ptr.get();
}

template<typename T>
const T& Pimpl<T>::operator*() const
{
    return *ptr.get();
}

}

#endif
