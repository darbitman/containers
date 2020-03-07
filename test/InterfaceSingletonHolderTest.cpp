#include <gtest/gtest.h>

#include <cstdint>

#include "creators/InterfaceSingletonHolder.hpp"

namespace helpers::creators {
namespace {

class Interface {
  public:
    virtual ~Interface() {}

    virtual uint32_t GetValue() const noexcept = 0;
};

class Derived1 : public Interface {
  public:
    explicit Derived1(uint32_t value) : value_(value) {}

    virtual ~Derived1() override { InterfaceSingletonHolder<Interface>::SetInstance(nullptr); }

    virtual uint32_t GetValue() const noexcept override { return value_; }

  private:
    uint32_t value_;
};

class Derived2 : public Interface {
  public:
    explicit Derived2(uint32_t value) : value_(value) {}

    virtual ~Derived2() override { InterfaceSingletonHolder<Interface>::SetInstance(nullptr); }

    virtual uint32_t GetValue() const noexcept override { return value_; }

  private:
    uint32_t value_;
};

class InterfaceSingletonHolderTest : public ::testing::Test {
  public:
    InterfaceSingletonHolderTest() : d1(10), d2(12) {}

  protected:
    Derived1 d1;
    Derived2 d2;
};

TEST_F(InterfaceSingletonHolderTest, CheckFirstImplementation) {
    InterfaceSingletonHolder<Interface>::SetInstance(d1);

    EXPECT_EQ(InterfaceSingletonHolder<Interface>::GetInstance().GetValue(), d1.GetValue());
}

TEST_F(InterfaceSingletonHolderTest, CheckSecondImplementation) {
    InterfaceSingletonHolder<Interface>::SetInstance(d2);

    EXPECT_EQ(InterfaceSingletonHolder<Interface>::GetInstance().GetValue(), d2.GetValue());
}

TEST_F(InterfaceSingletonHolderTest, CheckSwitchingImplementation) {
    InterfaceSingletonHolder<Interface>::SetInstance(d1);

    EXPECT_EQ(InterfaceSingletonHolder<Interface>::GetInstance().GetValue(), d1.GetValue());

    InterfaceSingletonHolder<Interface>::SetInstance(d2);

    EXPECT_EQ(InterfaceSingletonHolder<Interface>::GetInstance().GetValue(), d2.GetValue());
}

TEST_F(InterfaceSingletonHolderTest, VerifyDestructorCleansReference) {
    {
        Derived1 d(99);
        InterfaceSingletonHolder<Interface>::SetInstance(d);
        EXPECT_EQ(InterfaceSingletonHolder<Interface>::GetInstance().GetValue(), d.GetValue());
    }

    EXPECT_EQ(InterfaceSingletonHolder<Interface>::GetInstancePointer(), nullptr);
}

}  // namespace
}  // namespace helpers::creators
