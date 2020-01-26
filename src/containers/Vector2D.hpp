#pragma once

#include <vector>

namespace ctr {

template <typename _Tp>
class Vector2D {
  public:
    struct Dimensions {
        size_t rows;
        size_t columns;
    };

    class iterator {
      public:
        iterator(typename std::vector<_Tp>::iterator&& iter) noexcept
            : current_iterator_(std::move(iter)) {}

        ~iterator() noexcept {}

        /// @brief postfix increment
        iterator operator++(int) {
            decltype(current_iterator_) temp(current_iterator_);
            ++current_iterator_;
            return temp;
        }

        /// @brief prefix increment
        iterator& operator++() {
            ++current_iterator_;
            return *this;
        }

        bool operator!=(const iterator& rhs) { return current_iterator_ != rhs.current_iterator_; }

        _Tp& operator*() { return *current_iterator_; }

      private:
        typename std::vector<_Tp>::iterator current_iterator_;
    };

    Vector2D(size_t num_rows, size_t num_columns)
        : max_elements_(num_rows * num_columns),
          num_rows_(num_rows),
          num_columns_(num_columns),
          num_elements_(max_elements_),
          array_(max_elements_) {}

    Vector2D(size_t num_rows, size_t num_columns, const _Tp& default_value)
        : max_elements_(num_rows * num_columns),
          num_rows_(num_rows),
          num_columns_(num_columns),
          num_elements_(max_elements_),
          array_(max_elements_, default_value) {}

    Vector2D(const Vector2D& other) = default;

    Vector2D(Vector2D&& temp) noexcept = default;

    ~Vector2D() = default;

    void resize(size_t num_rows, size_t num_columns) {
        // for fast resizing, don't change the array size if only need to use a subset of its
        // allocated memory
        if (num_rows * num_columns <= max_elements_) {
            num_rows_ = num_rows;
            num_columns_ = num_columns;

            num_elements_ = num_rows * num_columns;
        }

        // need more elements than the array can support, it needs to be resized
        else {
            max_elements_ = num_rows * num_columns;
            num_elements_ = max_elements_;

            num_rows_ = num_rows;
            num_columns_ = num_columns;

            array_.resize(max_elements_);
        }
    }

    Dimensions capacity() const noexcept { return Dimensions{num_rows_, num_columns_}; }

    _Tp& at(size_t row, size_t column) { return array_.at(FlattenDimensions(row, column)); }

    const _Tp& at(size_t row, size_t column) const {
        return array_.at(FlattenDimensions(row, column));
    }

    _Tp& operator()(size_t row, size_t column) { return array_.at(FlattenDimensions(row, column)); }

    const _Tp& operator()(size_t row, size_t column) const {
        return array_.at(FlattenDimensions(row, column));
    }

    iterator begin() { return iterator(array_.begin()); }

    iterator end() { return iterator(array_.end()); }

  private:
    size_t FlattenDimensions(size_t row, size_t column) const noexcept {
        size_t flat_index = (row * num_columns_) + column;

        assert(flat_index < num_elements_);

        return flat_index;
    }

    /// Maximum number of elements the array can store
    size_t max_elements_ = 0;

    /// Number of rows & columns used for storing data in the array
    /// These can be <= the maximum number of rows & columns
    size_t num_rows_ = 0;
    size_t num_columns_ = 0;

    /// Number elements the array is storing
    size_t num_elements_ = 0;

    std::vector<_Tp> array_;
};

}  // namespace ctr
