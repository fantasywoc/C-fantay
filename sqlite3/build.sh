
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/f/data/sqlite3/lib
rm -rf build&&mkdir -p build &&cd build&& cmake .. && make
#sudo ln -s /home/f/data/sqlite3/bin/sqlite3 /usr/local/bin/sqlite3
