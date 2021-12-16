#! /bin/bash

# This bash file is for test the situation of all the threads are occupied,
# Can the nest requests be safely stored in the buffer,
# And can be handled after the dynamic request done.

# First, start a server with 3 threads and 3 buffers.
# Second, send 3 dynamic requests to occupy all 3 threads for 30 sec.
# Then, send 2 static requests.


# Start the server, give the arg basedir=. port=10000 threads=3 buffers=3
gnome-terminal --window --title='server' -- bash -c \
"echo 'Server start!';
echo 'port=10000 threads=3 buffers=3';
echo; 
cd ..;
./wserver -d . -p 10000 -t 3 -b 3;
exec bash"

# Send 3 dynamic requests at the same time
gnome-terminal --window --title='dynamic request 1' \
--tab --title='dynamic request 2' --tab --title='dynamic request 3' -- bash -c \
"cd ..;
./wclient localhost 10000 /spin.cgi?30;
exec bash"

# Send 2 static requests at the same time 
gnome-terminal --window --title='static request 1' \
--tab --title='static request 2' -- bash -c \
"cd ..;
./wclient localhost 10000 /hello_world.html;
exec bash"