# Some CURL Spammer

This repository contains the source code to `scs`

Name inspired after center-feature, flooding.

# Building

## Requirements

Debian-based

```bash
sudo apt-get install build-essential libcurl4-gnutls-dev libcurl4-ssl-dev
```

Arch-based

```bash
sudo pacman -Sy libcurl-compat base-devel
```

Fedora

```bash
sudo dnf install make automake gcc-c++ kernel-devel libcurl-devel
```

# **NOTE: Run the code below based on your operating system and in the root folder (scs, not src)**

Linux:

You can either build and link manually or use the build script 
The script is basically all the steps tied into one command line (If you only want the executable file and no linking, you should build manually)

Build script

```bash
chmod +x build.sh
./build.sh
```

Manually building

```bash
mkdir build
cd src
g++ main.cpp -l curl -o ../build/scs
cd ../build
./scs --help
```

Manually linking

```bash
# After building
cd build
sudo rm /usr/bin/scs -rf
sudo cp ./scs /usr/bin/scs
```

# Dev quick building

This assumes you're in the source directory (not root directory).

```bash
g++ main.cpp -l curl && ./a.out
```

# Pull requests

Having a merged pull request will put you on the Supporter Wall and will get my eternal appreciation

# Supporter Wall

Nobody yet :(
