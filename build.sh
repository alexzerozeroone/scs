mkdir build
cd src
g++ main.cpp -lcurl -o ../build/scs
cd ../build
sudo rm /usr/bin/scs -rf
sudo cp ./scs /usr/bin/scs
cd ../
rm -rf build
echo "Build successfully. scs command is now available"
scs --help
exit 0