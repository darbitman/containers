#pragma once

#include <cassert>

namespace ctr {

template <typename InterfaceType>
class InterfaceSingletonHolder {
  public:
    static void SetInstance(InterfaceType& interface) { p_interface_ = &interface; }

    static InterfaceType& GetInstance() {
        assert(p_interface_ != nullptr);

        return *p_interface_;
    }

  private:
    inline static InterfaceType* p_interface_ = nullptr;
};

}  // namespace ctr
