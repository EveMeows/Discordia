# Discordia

Discord RPC client configured in lua!

# Usage
Since Discordia is configured through lua, and managed through SystemD, its pretty easy to get the hang of it.

```bash
# Start the service
systemctl --user start discordia

# Restart the service (incase you changed the config)
systemctl --user restart discordia

# Stop the service
systemctl --user stop discordia

# Enable the service (it will always start at bootup (not recommended))
systemctl --user enable discordia

# Disable the service (it can no longer be started)
systemctl --user disable discordia
```

The configuration file should be placed in `$HOME/.config/discordia/config.lua` for default, or if `XDG_CONFIG_HOME` is set, it will be found inside `$XDG_CONFIG_HOME/discordia/config.lua`.

# Example Config
The config is pretty simple to grasp, it has very few functions, and a self documenting code-base, you can find every function you can call inside lua [here](./Discordia/discordia_api.h).
```lua
-- ~/.config/discordia/config.lua

local appid = '1234657895643'
Discordia:id(appid)

Discordia:details("Appears at the top", "Appears at the bottom")

Discordia:large_image('key', 'text')
Discordia:small_image('key', 'text')

Discordia:start_time(125489345923)
Discordia:end_time(1234782344)
```

# Installation
Discordia is a linux-first application, so the installation instructions are for linux.

## Prerequisities
Before installing Discordia, you must install CMake, Git, Ninja and clang
```bash
# Fedora
sudo dnf in cmake git ninja clang cmake

# Ubuntu
sudo apt install cmake git ninja-build clang cmake

# Arch
sudo pacman -S cmake git ninja clang cmake
```

## Compiling
First, you must start by cloning the repo, open your favourite terminal emulator
```bash
git clone https://github.com/EveMeows/Discordia
cd Discordia
```
Now, you can run the install script I've provided, it will compile, move the binary to /usr/local/bin, and create a user-level systemd service.
```bash
chmod +x ./install.sh
./install.sh
```

This will use the boundled libraries, You can compile the project yourself with custom LUA and DiscordRPC paths by running the following command:

> [!NOTE]
> The the root paths are supposed to lead to the `discord` and `lua` directories as shown below.

```bash
mkdir build && cd build

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DLUA_ROOT=/path/to/lua -DDISCORD_ROOT=/path/to/discord
ninja
```

The paths should look like this:
```bash
Parent
├── discord
│   ├── include
│   │   ├── discord_register.h
│   │   └── discord_rpc.h
│   └── lib
│       └── libdiscord-rpc.a
└── lua
    ├── include
    │   ├── lauxlib.h
    │   ├── luaconf.h
    │   ├── lua.h
    │   ├── lua.hpp
    │   └── lualib.h
    └── lib
        └── liblua.a
```

# LICENSE
GPL 3.0
