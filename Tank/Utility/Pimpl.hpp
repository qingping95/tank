#ifndef TANK_PIMPL_HPP
#define TANK_PIMPL_HPP

#include <memory>

namespace tank {


// See GOTW 101 if you want to know what's going on here:
// http://herbsutter.com/gotw/_101/
template<typename T>
class Pimpl {
    std::unique_ptr<T> ptr;
public:
    using value_type = T;
    Pimpl();
    template<typename ...Args> Pimpl(Args&&...);
    ~Pimpl();

    Pimpl(Pimpl&& other) = default;
    Pimpl& operator=(Pimpl&& other) = default;

    T* operator->();
    T& operator*();
    const T* operator->() const;
    const T& operator*() const;
};

}


#endif
