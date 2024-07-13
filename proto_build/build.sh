#!/bin/bash  
  
current_dir=$(pwd) 

echo "当前目录是: $current_dir"

export LD_LIBRARY_PATH=$current_dir/protobuf/lib:$LD_LIBRARY_PATH


rm -rf build && mkdir build && cd build && cmake .. && make  && ./my_app 
