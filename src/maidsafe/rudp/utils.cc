/*******************************************************************************
 *  Copyright 2012 MaidSafe.net limited                                        *
 *                                                                             *
 *  The following source code is property of MaidSafe.net limited and is not   *
 *  meant for external use.  The use of this code is governed by the licence   *
 *  file licence.txt found in the root of this directory and also on           *
 *  www.maidsafe.net.                                                          *
 *                                                                             *
 *  You are not free to copy, amend or otherwise use this source code without  *
 *  the explicit written permission of the board of directors of MaidSafe.net. *
 ******************************************************************************/

#include "maidsafe/rudp/utils.h"

#include <string>
#include <utility>

#include "maidsafe/common/log.h"
#include "maidsafe/common/utils.h"

namespace asio = boost::asio;
namespace ip = asio::ip;


namespace maidsafe {

namespace rudp {

namespace detail {

ip::address GetLocalIp(ip::udp::endpoint peer_endpoint) {
  asio::io_service io_service;
  ip::udp::socket socket(io_service);
  try {
    socket.connect(peer_endpoint);
    if (socket.local_endpoint().address().is_unspecified() ||
        socket.local_endpoint().address().is_loopback())
      return ip::address();
    return socket.local_endpoint().address();
  }
  catch(const std::exception& e) {
    LOG(kError) << "Failed trying to connect to " << peer_endpoint << " - " << e.what();
    return ip::address();
  }
}

bool IsValid(const ip::udp::endpoint& endpoint) {
  return endpoint.port() > 1024U && !endpoint.address().is_unspecified();
}

}  // namespace detail

}  // namespace rudp

}  // namespace maidsafe
