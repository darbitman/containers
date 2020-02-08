#include <gtest/gtest.h>

#include <cstdint>
#include <thread>
#include <vector>

#include "containers/SharedQueue.hpp"

namespace ctr {
namespace {

class BlockingSharedQueueTest : public ::testing::Test {
  protected:
    void ConsumerThread(std::vector<uint32_t>& output_vector) {
        while (true) {
            uint32_t element = queue_.front();
            queue_.pop();

            // stop the thread
            if (element == 0) {
                break;
            }

            output_vector.push_back(element);
        }
    }

    std::vector<uint32_t> vector_;

    ctr::SharedQueue<uint32_t> queue_;
};

TEST_F(BlockingSharedQueueTest, EmptyQueue) { EXPECT_EQ(queue_.empty(), true); }

TEST_F(BlockingSharedQueueTest, PushPopSameThread) {
    queue_.push(12);

    EXPECT_EQ(queue_.empty(), false);

    auto& element = queue_.front();

    EXPECT_EQ(element, 12);

    queue_.pop();

    EXPECT_EQ(queue_.empty(), true);
}

TEST_F(BlockingSharedQueueTest, ProducerConsumer) {
    for (uint32_t i = 1; i < 100000; ++i) {
        vector_.push_back(i);
    }

    // this vector will be modified in the consumer thread
    std::vector<uint32_t> output_vector;

    std::thread consumer_thread(&BlockingSharedQueueTest_ProducerConsumer_Test::ConsumerThread,
                                this, std::ref(output_vector));

    for (auto& element : vector_) {
        queue_.push(element);
    }

    // cause the consumer thread to exit
    queue_.push(0);

    consumer_thread.join();

    ASSERT_EQ(vector_.size(), output_vector.size());
}

TEST_F(BlockingSharedQueueTest, Emplace) {
    queue_.emplace(12);

    EXPECT_EQ(queue_.front(), 12);
}

}  // namespace
}  // namespace ctr
