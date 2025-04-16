#pragma once

namespace Discordia::Internal
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