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

    /// @brief Set the start date.
    /// @note Leave empty if start is now. The time MUST be in UNIX TimeStamp.
    void start_time(int64_t start);

    /// @brief Set the end date.
    /// @note The time MUST be in UNIX TimeStamp.
    void end_time(int64_t end);

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

    int64_t m_start = -1;
    int64_t m_end = -1;

    DiscordRichPresence m_presence;
  };
}
