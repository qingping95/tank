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
    Pimpl();
    template<typename ...Args> Pimpl(Args&&...);
    ~Pimpl();

    // Do a deep copy if asked to copy. This is so that using a pimpl doesn't
    // supress copy behaivour if it wouldn't be otherwise supressed.
    // Note: this will supress copy behaivour if your pimpl class has non-copiable
    // members, i.e. it is not transitive. This is desireable because that's
    // the behaivour you'd get if you just used private data members.
    //Pimpl(const Pimpl& other);
    //Pimpl(Pimpl&& other) = default;

    //Pimpl& operator=(const Pimpl& other);
    //Pimpl& operator=(Pimpl&& other) = default;

    T* operator->();
    T& operator*();
};

}


#endif
