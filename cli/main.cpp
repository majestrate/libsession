#include "session-client.hpp"

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

#include <spdlog/spdlog.h>

session::Config
setupConfigOpts(CLI::App& app)
{
  session::Config conf;
  app.add_option<std::string>("--db", conf.db.file);
  return conf;
}

int
main(int argc, char** argv)
{
  CLI::App app{"session-cli"};
  auto conf = setupConfigOpts(app);
  CLI11_PARSE(app, argc, argv);
  spdlog::info("session starting up");
  session::Client cl{std::move(conf)};
  try
  {
    spdlog::debug("session running...");
    cl.Run();
    spdlog::debug("session ending...");
  }
  catch (std::exception& ex)
  {
    spdlog::error(ex.what());
  }
}
