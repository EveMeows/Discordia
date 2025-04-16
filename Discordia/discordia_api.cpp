#include "discordia_api.h"
#include <iostream>

void Discordia::DiscordiaApi::id(const char* id)
{
  this->m_appid = id;
}

void Discordia::DiscordiaApi::construct_rpc()
{
  if (!this->m_appid)
  {
    std::cerr << "ERROR: No APPID provided, so the app cannot continue." << std::endl;
    exit(1);
  }

  // TODO: Build RPC.
}
