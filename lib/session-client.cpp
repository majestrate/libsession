#include "session-client.hpp"

namespace session
{
  Client::Client(Config conf) : _conf{std::move(conf)}
  {}

  void
  Client::Run()
  {}
}  // namespace session
