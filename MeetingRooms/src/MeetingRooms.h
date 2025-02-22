#ifndef MEETING_ROOMS_H
#define MEETING_ROOMS_H
#include <vector>
#include <iostream>

struct Meeting {
    long from;
    long to;    
    Meeting(long from, long to): from(from), to(to) {
        //std::cout << this << ": Meeting()" << std::endl;
    }    
    ~Meeting() {
        //std::cout << this << ": ~Meeting()" << std::endl;
    }
};

bool CompareMeeting(const Meeting *m1, const Meeting *m2);

class MeetingRooms {  
    std::vector<std::vector<const Meeting *> *> rooms;
    std::vector<const Meeting *> meetings;

    void AllocateOneRoom(const Meeting *m);
    bool IsConflict(const Meeting *m1, const Meeting *m2);
    bool FindSlot(const Meeting *m);

public:
    MeetingRooms(long timeSlots[][2], long n) { 
        for (long i = 0; i < n; i++) {
            meetings.push_back(new Meeting(timeSlots[i][0], timeSlots[i][1]));
        }               
    }
    // number of rooms needed
    unsigned long GetNumOfRooms();
    // allocate a room for meetings
    void Schedule();

    virtual ~MeetingRooms() {
        for (const Meeting *meeting : meetings) {
            delete meeting;
        }
        for (std::vector<const Meeting *> *room : rooms) {
            delete room;
        }
    }

    friend std::ostream & operator << (std::ostream &os, const MeetingRooms &mr);     
};
#endif

