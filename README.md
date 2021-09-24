# Some CURL Spammer

This repository contains the source code to `scs`
Name inspired after center-feature, flooding.

# Building

## Requirements

```
build-essential libcurl4-gnutls-dev
```

To install the requirements type

```bash
sudo apt-get install build-essential libcurl4-gnutls-dev
```

## **NOTE: Run the code below based on your operating system and in the root folder (scs, not src)**

Linux
You can either build and link manually or use the build script
The script is basically all the steps tied into one command line
(If you only want the executable file and no linking, you should build manually)

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
sudo rm /usr/bin/scs -rf # This will ask after your password
sudo cp ./scs /usr/bin/scs # This will not ask for your password again
```

# Dev quick building

```bash
g++ main.cpp -l curl && ./a.out <url> [arguments]
```

# Pull requests

Having a merged pull request will put you on the Supporter Wall and will get my eternal appreciation

# Supporter Wall

Nobody yet :(
