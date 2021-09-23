# Some CURL Spammer

This repository contains the source code to `scs`
Name inspired after center-feature, flooding.

# Building

Linux

```bash
mkdir build
cd src
g++ main.cpp -l curl -o ../build/scs
cd ../build
./scs --help
```

Windows

```bash
mkdir build
cd src
g++ main.cpp -l curl -o ../build/scs
cd ../build
./scs.exe --help
```

# Dev quick building

```bash
g++ main.cpp -l curl && ./a.out <url> [arguments]
```

# Linking

Currently I use a Linux solution I have made that I don't think it's the best but it's alright for now

```bash
# After building
cd build
rm /usr/bin/scs -rf
sudo mv ./scs /usr/bin/scs # This will ask after your password
```

# Pull requests

Having a merged pull request will put you on the Supporter Wall and my eternal appreciation

# Supporter Wall

Nobody yet :(
