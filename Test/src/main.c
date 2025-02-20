#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// TBD: a container like a vector needed
struct rooms {
    long *meeting_ids;  // meeting_ids[i] is the head of a list, where is the room id
    long count;         // number of rooms needed; each room has a list of meetings
    long n;             // n meetings in all, i.e., the number of meetings
};

// meeting id is represented as the index in the array meetings[]
struct meeting{
    long from;          // start time
    long to;            // end time
    long prev;          // the previous meeting id in the same room
};

struct rooms *create_rooms(long n) {
    assert(n > 0);
    struct rooms * rs = (struct rooms *) malloc(sizeof(struct rooms));
    long *meeting_ids = (long *) malloc(sizeof(long) * n);
    assert(rs && meeting_ids);
    rs->meeting_ids = meeting_ids;
    rs->count = 0;
    rs->n = n;
    return rs;
}

void release_rooms(struct rooms *rs) {
    if (rs) {
        free(rs->meeting_ids);
        free(rs);
    }
}

/*
    allocate a new room for meeting meeting_id
 */
static void allocate_one_room(struct rooms *rs, long meeting_id) {
    assert(rs->count < rs->n);
    rs->meeting_ids[rs->count] = meeting_id;
    rs->count++;
}

/*
    let meeting_id be the current meeting in room room_id
 */
static void update_one_room(struct rooms *rs, long room_id, struct meeting meetings[], long meeting_id) {
    assert(room_id < rs->count);
    long old_mid = rs->meeting_ids[room_id];
    rs->meeting_ids[room_id] = meeting_id;
    meetings[meeting_id].prev = old_mid;
}

static void swap(struct meeting meetings[], long i, long j) {
    struct meeting p = meetings[i];
    meetings[i] = meetings[j];
    meetings[j] = p;
}

static int is_conflict(struct meeting *p1, struct meeting *p2) {
    return (p1->from < p2->from && p2->from < p1->to) 
                || (p2->from < p1->from && p1->from < p2->to)
                    || (p1->from == p2->from);
}

static int is_less(struct meeting *p1, struct meeting *p2) {
    return (p1->from < p2->from) || ((p1->from == p2->from) && (p1->to < p2->to));
}

// [left, right]
static void quick_sort(struct meeting meetings[], long left, long right) {
    if (left < right) {
        long middle = left + (right - left) / 2;
        swap(meetings, left, middle);
        struct meeting pivot = meetings[left];
        long last = left;
        // pivot, {<}, {>=}
        for (long i = left + 1; i <= right; i++) {
            if (is_less(&meetings[i], &pivot)) {
                last++;
                swap(meetings, last, i);
            }
        }
        // {<}, pivot, {>=}
        swap(meetings, last, left);
        //
        quick_sort(meetings, left, last - 1);
        quick_sort(meetings, last + 1, right);
    }
}

/*
    Test whether there is any available time slot in the room room_id
    for a new meeting

    If found
        update the room information
        return 1
    else
        return 0
 */
static int find_in_one_room(struct rooms *rs, struct meeting meetings[], long room_id, long new_mid) {
    long cur_mid = rs->meeting_ids[room_id];
    if (is_conflict(meetings + cur_mid, meetings + new_mid)) {
        return 0;
    } else {
        update_one_room(rs, room_id, meetings, new_mid);
        return 1;
    }
}

static int find_a_slot(struct rooms *rs, struct meeting meetings[], long new_mid) {
    for (long room_id = 0; room_id < rs->count; room_id++) {
        if (find_in_one_room(rs, meetings, room_id, new_mid)) {
            return 1;
        }
    }    
    return 0;
}

long get_min_rooms(struct rooms *rs, struct meeting meetings[], long n) {
    allocate_one_room(rs, 0);
    for (long meeting_id = 1; meeting_id < n; meeting_id++) {
        if (!find_a_slot(rs, meetings, meeting_id)) {
            allocate_one_room(rs, meeting_id);           
        }
    }
    return rs->count;
}

static void print_one_room(struct meeting meetings[], long i) {
    if (i != -1) {
        print_one_room(meetings, meetings[i].prev);
        printf("(%ld, %ld) ", meetings[i].from, meetings[i].to);
    }
}

static void print_meetings(struct rooms *rs, struct meeting meetings[], long n, const char *info) {
    printf("\n----------------- %s(): %s ----------------\n", __FUNCTION__, info);
    for (long room_id = 0; room_id < rs->count; room_id++) {
        print_one_room(meetings, rs->meeting_ids[room_id]);
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    struct meeting meetings[] = {{1, 3, -1},
                                 {1, 3, -1},
                                 {1, 2, -1}, // three rooms
                                 {2, 4, -1},
                                 {4, 6, -1},
                                 {3, 7, -1},
                                 {7, 10, -1}
                              };
    long n = sizeof(meetings) / sizeof(meetings[0]);
    struct rooms *rs = create_rooms(n);
    quick_sort(meetings, 0, n - 1);
    long rooms = get_min_rooms(rs, meetings, n);
    printf("The minimum number of rooms is %ld\n", rooms);
    print_meetings(rs, meetings, n, "meetings in each room");
    release_rooms(rs);
    return 0;
}

