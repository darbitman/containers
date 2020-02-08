#pragma once

#include <cstdint>

namespace ctr::network {

class TcpConnection {
  public:
    TcpConnection() noexcept;

    TcpConnection(int32_t existing_socket_fd) noexcept;

    ~TcpConnection() noexcept;

    bool CloseConnection() noexcept;

    int32_t GetSocketDescriptor() const;

  private:
    static constexpr int32_t kInactiveSocketFd_ = -1;

    int32_t socket_fd_ = kInactiveSocketFd_;
};

}  // namespace ctr::network
