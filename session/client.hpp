#pragma once

#include "config.hpp"

namespace session
{
class Client
{
    Config _conf;
public:
    explicit Client(Config conf);
    
    Client(const Client &) = delete;
    Client( Client &&) = delete;

    /// run mainloop
    void Run();
};
}
