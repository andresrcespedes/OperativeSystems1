#! /bin/bash

# This bash file is for test the situation if refer to files outside of this sub-tree.

# Start the server, give the arg basedir=. port=10000 threads=3 buffers=3
gnome-terminal --window --title='server' -- bash -c \
"echo 'Server start!';
echo 'port=10000 threads=3 buffers=3';
echo; 
cd ..;
./wserver -d . -p 10000 -t 3 -b 3;
exec bash"

# Send a dynamic request within the sub-tree for 30 sec.
gnome-terminal --window --title='dynamic request 1' \
-- bash -c \
"cd ..;
./wclient localhost 10000 /spin.cgi?30;
exec bash"

# Try to send a static request outside of the sub-tree.
gnome-terminal --window --title='static request 1' \
-- bash -c \
"cd ..;
./wclient localhost 10000 /../hello_world.html;
exec bash"
