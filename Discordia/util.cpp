#include "util.h"
#include <cstdlib>
#include <iostream>

std::filesystem::path Discordia::Util::config_home()
{
  if (const char* xdg = std::getenv("XDG_CONFIG_HOME"))
  {
    return xdg;
  }

  const char* home = std::getenv("HOME");
  return std::filesystem::path(home) / ".config";
}
