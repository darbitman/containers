#include "TcpConnection.hpp"

#include <sys/socket.h>
#include <unistd.h>

namespace ctr::network {

TcpConnection::TcpConnection() noexcept : socket_fd_(socket(AF_INET, SOCK_STREAM, 0)) {}

TcpConnection::TcpConnection(int32_t existing_socket_fd) noexcept
    : socket_fd_(existing_socket_fd) {}

TcpConnection::~TcpConnection() noexcept { CloseConnection(); }

bool TcpConnection::CloseConnection() noexcept {
    if (socket_fd_ == kInactiveSocketFd_) {
        return true;
    } else {
        shutdown(socket_fd_, SHUT_RDWR);

        int32_t return_status = close(socket_fd_);

        socket_fd_ = kInactiveSocketFd_;

        return (return_status == 0);
    }
}

int32_t TcpConnection::GetSocketDescriptor() const { return socket_fd_; }

}  // namespace ctr::network
