#include <gtest/gtest.h>

#include "network/TcpConnection.hpp"

#include <sys/socket.h>

namespace ctr::network {
namespace {

TEST(TcpConnectionTest, CloseDefaultTcpConnection) {
    TcpConnection tcp_connection;

    ASSERT_NE(tcp_connection.GetSocketDescriptor(), -1);

    EXPECT_EQ(tcp_connection.CloseConnection(), true);
}

TEST(TcpConnectionTest, CloseExternalConnection) {
    auto socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    TcpConnection tcp_connection(socket_fd);

    ASSERT_NE(socket_fd, -1);

    EXPECT_EQ(tcp_connection.GetSocketDescriptor(), socket_fd);

    EXPECT_EQ(tcp_connection.CloseConnection(), true);
}

}  // namespace
}  // namespace ctr::network
