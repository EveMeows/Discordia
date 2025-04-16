#pragma once

#include <discord_rpc.h>

namespace Discordia
{
  namespace Internal
  {
    struct Image
    {
      // Massive hack lol
      bool init = false;

      const char* key;
      const char* text;
    };

    struct TimeStamp
    {
      bool init = false;
      int64_t start;
      int64_t end;
    };
  }
  
  class DiscordiaApi
  {
  public:
    /// @brief Set the application ID.
    /// @note The app will NOT run without this.
    void id(const char* id);

    /// @brief Set the large RPC image key and text.
    /// @note The key can also be a URL.
    void large_image(const char* key, const char* text);

    /// @brief Set the small RPC image key and text.
    /// @note The key can also be a URL.
    void small_image(const char* key, const char* text);

    /// @brief Set the start and end time dates.
    /// @note The time MUST be in UNIX TimeStamps.
    void timestamps(int64_t start, int64_t end);

    // INTERNAL API
    // ---------------------
    void construct_rpc();
    void update_rpc();
    // --------------------
  private:
    const char* m_appid;

    Internal::Image m_small;
    Internal::Image m_big;

    DiscordRichPresence m_presence;
  };
}
