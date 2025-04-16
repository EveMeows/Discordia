#include "discordia_api.h"
#include "discord_rpc.h"
#include <iostream>

namespace {
  void ready(const DiscordUser* request)
  {
    std::cout << "INFO: Connected to RPC Server." << std::endl;
  }

  void errored(int error_code, const char* message)
  {
    std::cerr << "ERROR: RPC Server failed with error code " << error_code << ": " << message << std::endl;
  }
}

void Discordia::DiscordiaApi::id(const char* id)
{
  this->m_appid = id;
}

void Discordia::DiscordiaApi::small_image(const char* key, const char* text)
{
  this->m_small.text = text;
  this->m_small.key = key;

  this->m_small.init = true;
}

void Discordia::DiscordiaApi::large_image(const char* key, const char* text)
{
  this->m_big.text = text;
  this->m_big.key = key;

  this->m_big.init = true;
}

void Discordia::DiscordiaApi::construct_rpc()
{
  if (!this->m_appid)
  {
    std::cerr << "ERROR: No APPID provided, so the app cannot continue." << std::endl;
    exit(1);
  }

  this->m_presence = DiscordRichPresence {
    .state = "Testing test",
    .details = "More testing test"
  };

  if (this->m_small.init)
  {
    this->m_presence.smallImageKey = this->m_small.key;
    this->m_presence.smallImageText = this->m_small.text;
  }

  if (this->m_big.init)
  {
    this->m_presence.largeImageKey = this->m_big.key;
    this->m_presence.largeImageText = this->m_big.text;
  }

  DiscordEventHandlers handlers = {
    .ready = ready,
    .errored = errored
  };

  Discord_Initialize(this->m_appid, &handlers, 0, nullptr);

  this->update_rpc();
}

void Discordia::DiscordiaApi::update_rpc()
{
  Discord_RunCallbacks();
  Discord_UpdatePresence(&this->m_presence);
}
