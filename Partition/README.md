# Partition

## How to run

```sh
Partition$ make

Partition$ ./main

```

## Output

```sh

Partition$ ./main
0 0 0 3 3 0 -2 -2 7 6 0 7 -4 -4 
pivot = 0
-4 -2 -2 -4 0 0 0 0 0 3 7 7 6 3

Partition$ ./main 0
0 0 0 3 3 0 -2 -2 7 6 0 7 -4 -4 
pivot = 0
-4 -2 -2 -4 0 0 0 0 0 3 7 7 6 3 

iron@Katana:Partition$ ./main -2
0 0 0 3 3 0 -2 -2 7 6 0 7 -4 -4 
pivot = -2
-4 -4 -2 -2 0 3 0 3 7 6 0 7 0 0 

iron@Katana:Partition$ ./main 3
0 0 0 3 3 0 -2 -2 7 6 0 7 -4 -4 
pivot = 3
-4 0 0 0 0 -2 -2 0 -4 3 3 6 7 7 

iron@Katana:Partition$ ./main 7
0 0 0 3 3 0 -2 -2 7 6 0 7 -4 -4 
pivot = 7
-4 0 0 3 3 0 -2 -2 0 6 0 -4 7 7 

```

