#pragma once

#include <cassert>

namespace ctr {

template <typename InterfaceType>
class InterfaceSingletonHolder {
  public:
    static void SetInstance(InterfaceType& interface) { p_interface_ = &interface; }

    static void SetInstance(InterfaceType* p_interface) { p_interface_ = p_interface; }

    template <typename ReturnType>
    static ReturnType GetInstance() {
        if constexpr (std::is_reference<ReturnType>::value) {
            assert(p_interface_ != nullptr);
            return *p_interface_;
        }
        if constexpr (std::is_pointer<ReturnType>::value) {
            return p_interface_;
        }
    }

  private:
    inline static InterfaceType* p_interface_ = nullptr;
};

}  // namespace ctr
