#! /bin/bash

gnome-terminal --window --title='server' -- bash -c \
"echo 'Server start!';
echo 'port=10000 threads=3 buffers=3';
echo; 
cd ..;
./wserver -d . -p 10000 -t 3 -b 3;
exec bash"

gnome-terminal --window --title='dynamic request 1' \
--tab --title='dynamic request 2' --tab --title='dynamic request 3' -- bash -c \
"cd ..;
./wclient localhost 10000 /spin.cgi?30;
exec bash"

gnome-terminal --window --title='static request 1' \
--tab --title='static request 2' -- bash -c \
"cd ..;
./wclient localhost 10000 /hello_world.html;
exec bash"