#pragma once

namespace Discordia
{
  class DiscordiaApi
  {
  public:
    /// @brief Set the application ID.
    /// @note The app will NOT run without this.
    void id(const char* id);

    // INTERNAL API
    // ---------------------
    void construct_rpc();
    // --------------------
  private:
    const char* m_appid;
  };
}
