#pragma once
#include <string>

namespace session
{
  struct DBConfig
  {
    std::string file;
  };

  struct Config
  {
    DBConfig db;
  };
}  // namespace session
