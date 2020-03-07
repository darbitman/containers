#include <gtest/gtest.h>

#include <cstdint>

#include "containers/Vector2D.hpp"

namespace helpers::containers {
namespace {

class Vector2DTest : public ::testing::Test {
  public:
    Vector2DTest() : vector(height, width) {}

  protected:
    static constexpr size_t width = 1920;
    static constexpr size_t height = 1080;

    size_t FlattenDimensions(size_t row, size_t column, size_t num_columns) const noexcept {
        return (row * num_columns) + column;
    }

    Vector2D<uint32_t> vector;
};

struct NoDefaultCtor {
    explicit NoDefaultCtor(uint32_t default_value) : value(default_value) {}

    uint32_t value;
};

TEST_F(Vector2DTest, EmptyVector) {
    auto dims = vector.capacity();

    EXPECT_EQ(dims.columns, width);
    EXPECT_EQ(dims.rows, height);
}

TEST_F(Vector2DTest, Iteration) {
    // assign values to every position in the range of [0, width*height) using row major traversal
    // which means the first row will have values [0, width), then next row will have [width,
    // 2*width), and so on
    for (size_t row = 0; row < height; ++row) {
        for (size_t column = 0; column < width; ++column) {
            vector(row, column) = FlattenDimensions(row, column, width);
        }
    }

    // iterate through the 2D vector using row major traversal and make sure the values are correct
    {
        uint32_t i = 0;
        for (auto& element : vector) {
            EXPECT_EQ(element, i++);
        }
    }
}

TEST_F(Vector2DTest, ConstIteration) {
    // assign values to every position in the range of [0, width*height) using row major traversal
    // which means the first row will have values [0, width), then next row will have [width,
    // 2*width), and so on
    for (size_t row = 0; row < height; ++row) {
        for (size_t column = 0; column < width; ++column) {
            vector(row, column) = FlattenDimensions(row, column, width);
        }
    }

    const decltype(vector)& const_vector = vector;

    // iterate through the 2D vector using row major traversal and make sure the values are correct
    {
        uint32_t i = 0;
        for (auto& element : const_vector) {
            EXPECT_EQ(element, i++);
        }
    }
}

TEST_F(Vector2DTest, TypeWithoutDefaultConstructor) {
    NoDefaultCtor default_value(0xDEADBEEF);

    Vector2D<NoDefaultCtor> vec(height, width, default_value);

    EXPECT_EQ(vec.at(height / 2, width / 2).value, default_value.value);
}

}  // namespace
}  // namespace helpers::containers
