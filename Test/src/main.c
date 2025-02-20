#include <stdio.h>

struct pair{
    long from;
    long to;
    //
    long next;          // -1
    long visited;       // for printing
};

static void swap(struct pair pairs[], long i, long j) {
    struct pair p = pairs[i];
    pairs[i] = pairs[j];
    pairs[j] = p;
}

static int is_conflict(struct pair *p1, struct pair *p2) {
    return (p1->from < p2->from && p2->from < p1->to) 
                || (p2->from < p1->from && p1->from < p2->to)
                    || (p1->from == p2->from);
}

static int is_less(struct pair *p1, struct pair *p2) {
    return (p1->from < p2->from) || ((p1->from == p2->from) && (p1->to < p2->to));
}

// [left, right]
static void quick_sort(struct pair pairs[], long left, long right) {
    if (left < right) {
        long middle = left + (right - left) / 2;
        swap(pairs, left, middle);
        struct pair pivot = pairs[left];
        long last = left;
        // pivot, {<}, {>=}
        for (long i = left + 1; i <= right; i++) {
            if (is_less(&pairs[i], &pivot)) {
                last++;
                swap(pairs, last, i);
            }
        }
        // {<}, pivot, {>=}
        swap(pairs, last, left);
        //
        quick_sort(pairs, left, last - 1);
        quick_sort(pairs, last + 1, right);
    }
}

/*
    Test whether there is any available time slot in the room 
    used by pairs in the list starting from pairs[i].

    If found
        return 1
    else
        return 0
 */
int find_in_one_list(struct pair pairs[], long i, long j) {
    while(i != -1) {
        if (is_conflict(pairs + j, pairs + i)) {
            return 0;
        } else {
            if (pairs[i].next == -1) {
                break;
            } else {
                i = pairs[i].next;
            }
        }
    }
    // no conflict
    pairs[i].next = j;
    pairs[j].next = -1;
    return 1;
}

/*
    pairs[0] ... pairs[end] have been allocated.
    We try to find a slot for pair[j].
 */
int find_a_slot(struct pair pairs[], long end, long j, long *pNum) {
    for (long i = 0; i <= end; i++) {
        if (find_in_one_list(pairs, i, j)) {
            return 1;
        }
    }
    return 0;
}


long get_min_rooms(struct pair pairs[], long n) {
    long rooms = 1;
    for (long i = 1; i < n; i++) {
        if (!find_a_slot(pairs, i - 1, i, &rooms)) {
            rooms++;            
        }
    }
    return rooms;
}


static void print_one_list(struct pair pairs[], long i) {
    while (i != -1) {
        //printf("(<%ld, %ld>, %ld) ", pairs[i].from, pairs[i].to, pairs[i].next);
        printf("(%ld, %ld) ", pairs[i].from, pairs[i].to);
        pairs[i].visited = 1;
        i = pairs[i].next;
        if (i != -1) {
            printf("-> ");
        }
    }
    printf("\n");
}

void print_pairs(struct pair pairs[], long n, const char *info) {
    printf("\n----------------- %s(): %s ----------------\n", __FUNCTION__, info);
    for (long i = 0; i < n; i++) {
        pairs[i].visited = 0;
    }
    for (long i = 0; i < n; i++) {
        if (!pairs[i].visited) {
            print_one_list(pairs, i);
        }
    }
    printf("\n");
}

int main(void) {
    struct pair pairs[] = {{1, 3, -1}, 
                           {1, 3, -1},   
                           {1, 2, -1},  // three rooms
                           {2, 4, -1}, 
                           {4, 6, -1}, 
                           {3, 7, -1}, 
                           {7, 10, -1}};    
    long n = sizeof(pairs) / sizeof(pairs[0]);
    print_pairs(pairs, n, "before sorting");
    quick_sort(pairs, 0, n - 1);
    print_pairs(pairs, n, "after sorting");
    long rooms = get_min_rooms(pairs, n);
    printf("The minimum number of rooms is %ld\n", rooms);
    print_pairs(pairs, n, "meetings in each room");
    return 0;
}

