#include <iostream>
#include <vector>
#include "MeetingRooms.h"
using namespace std;

int main(void) {
    long timeSlots[][2] = {
        {1, 3},
        {1, 3},
        {1, 2}, // three rooms
        {2, 4},
        {4, 6},
        {3, 7},
        {7, 10}     
    };  
    long n = sizeof(timeSlots)/sizeof(timeSlots[0]);
    MeetingRooms rooms(timeSlots, n);   
    rooms.Schedule();
    cout << rooms << endl;
    return 0;
}
