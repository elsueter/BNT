pkill -9 BNT
git pull
cmake ..
make
cd BNT
./BNT > BNT.log 2>&1 &