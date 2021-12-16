#! /bin/bash

# This bash file is for test normal process.
# 1. Start the server with 5 threads and 5 buffers.
# 2. Send four dynamic requests.
# 3. Send five static requests.

# 1. Start the server with 5 threads and 5 buffers.
gnome-terminal --window --title='server' -- bash -c \
"echo 'Server start!';
echo 'port=10000 threads=5 buffers=5';
echo; 
cd ..;
./wserver -d . -p 10000 -t 5 -b 5;
exec bash"

# 2. Send four dynamic requests.
gnome-terminal --window --title='Step 2: dynamic request 1' \
--tab --title='Step 2: dynamic request 2' --tab --title='Step 2: dynamic request 3' \
--tab --title='Step 2: dynamic request 4' -- bash -c \
"cd ..;
./wclient localhost 10000 /spin.cgi?30;
exec bash"

# 3. Send five static requests.
gnome-terminal --window --title='Step 3: static request 1' \
--tab --title='Step 3: static request 2' --tab --title='Step 3: static request 3' \
--tab --title='Step 3: static request 4' --tab --title='Step 3: static request 5' -- bash -c \
"cd ..;
./wclient localhost 10000 /hello_world.html;
exec bash"
