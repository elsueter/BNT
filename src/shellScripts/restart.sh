pkill -9 BNT
git pull
cmake ..
make
./webServer/BNT > webServer/BNT.log 2>&1 &