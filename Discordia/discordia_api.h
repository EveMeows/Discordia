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

    struct Text
    {
      bool init = false;

      const char* details;
      const char* state;
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

    /// @brief Set the details and state of the RPC.
    /// @note Details is above, State is below.
    void details(const char* details, const char* state);



    // INTERNAL API
    // ---------------------
    void construct_rpc();
    void update_rpc();
    // --------------------
  private:
    const char* m_appid;

    Internal::Image m_small;
    Internal::Image m_big;
    Internal::Text m_text;

    DiscordRichPresence m_presence;
  };
}
