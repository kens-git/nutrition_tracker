#ifndef INTAKETARGET_HPP
#define INTAKETARGET_HPP

#include "Food.hpp"

// TODO: this is pretty pointless, just use the Food class

// Food isn't an ideal class to inherit from because IntakeTarget doesn't need the name and category
// that Food provides, but, it's too convenient to not reuse.
class IntakeTarget : public Food {
    public:
        IntakeTarget() = default;
};

#endif // INTAKETARGET_HPP
