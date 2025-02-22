# Meeting rooms needed, in C++

## How to run

```sh
MeetingRooms$ make CPPFLAGS="-fsanitize=address -O3 -g"

make main
make[1]: Entering directory '/home/iron/github/slides/MeetingRooms'
g++ -fsanitize=address -O3 -g -c src/main.cpp -o build/main.o
g++ -fsanitize=address -O3 -g -c src/MeetingRooms.cpp -o build/MeetingRooms.o
g++ -fsanitize=address -O3 -g -o main ./build/main.o ./build/MeetingRooms.o
make[1]: Leaving directory '/home/iron/github/slides/MeetingRooms'


MeetingRooms$ ./main

```

## Output

```sh
MeetingRooms$ ./main

At least 3 rooms needed

(1,2) (2,4) (4,6) (7,10) 
(1,3) (3,7) 
(1,3) 


```

