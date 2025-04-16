#!/bin/bash

if [ "$1" == "--remove" ]; then
    systemctl --user stop discordia
    rm -v $HOME/.config/systemd/user/discordia.service
    
    rm -v /usr/local/bin/discordia

    exit 0
fi

read -r -p "Before running, Make sure you have all depedencies. Continue? [Y/n] " RESPONSE
case $RESPONSE in
  [nN])
    exit 0
  ;;
esac

mkdir build && cd build

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja

mkdir -pv $HOME/.config/systemd/user
cp -v ../discordia.service $HOME/.config/systemd/user/discordia.service

sudo mkdir -pv /usr/local/bin
sudo cp -v ./Discordia /usr/local/bin

cd ..
