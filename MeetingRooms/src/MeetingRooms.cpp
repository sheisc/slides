#include <iostream>
#include <cassert>
#include <algorithm>
#include "MeetingRooms.h"

using namespace std;

bool CompareMeeting(const Meeting *m1, const Meeting *m2) {
    return m1->from < m2->from || ((m1->from == m2->from) && (m1->to < m2->to));
}

std::ostream & operator << (std::ostream &os, const MeetingRooms &mr) {
    os << "At least " << mr.rooms.size() << " rooms needed\n";
    for (const vector<const Meeting *> *room : mr.rooms) {
        for (const Meeting *m : *room) {
            os << "(" << m->from << "," << m->to << ") "; 
        }
        os << "\n";
    }  
    os << endl;
    return os;
}

void MeetingRooms::AllocateOneRoom(const Meeting *m) {
    vector<const Meeting *> *room = new vector<const Meeting *>();
    room->push_back(m);
    this->rooms.push_back(room);
}

void MeetingRooms::Schedule() {
    assert(this->meetings.size() > 0);
    sort(this->meetings.begin(), this->meetings.end(), CompareMeeting);
    this->AllocateOneRoom(this->meetings[0]);
    for (size_t mid = 1; mid < this->meetings.size(); mid++) {
        if (!FindSlot(this->meetings[mid])) {
            this->AllocateOneRoom(this->meetings[mid]);
        }
    }    
}

unsigned long MeetingRooms::GetNumOfRooms() {
    return this->rooms.size();
}

bool MeetingRooms::IsConflict(const Meeting *m1, const Meeting *m2) {
    return (m1->from < m2->from && m2->from < m1->to) 
                || (m2->from < m1->from && m1->from < m2->to)
                    || (m1->from == m2->from);
}

bool MeetingRooms::FindSlot(const Meeting *m) {
    for (std::vector<const Meeting *> *room : rooms) {
        if (!IsConflict(room->back(), m)) {
            room->push_back(m);
            return true;
        }
    }
    return false;
}

