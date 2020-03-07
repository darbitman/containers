#pragma once

#include <cassert>

namespace helpers::creators {

template <typename InterfaceType>
class InterfaceSingletonHolder {
  public:
    static void SetInstance(InterfaceType& interface) { p_interface_ = &interface; }

    static void SetInstance(InterfaceType* p_interface) { p_interface_ = p_interface; }

    static InterfaceType& GetInstance() {
        assert(p_interface_ != nullptr);

        return *p_interface_;
    }

    static InterfaceType* GetInstancePointer() { return p_interface_; }

  private:
    inline static InterfaceType* p_interface_ = nullptr;
};

}  // namespace helpers::creators
