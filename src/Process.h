#include <vector>
//shared struct
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining=0;
    int priority=0;
    int waiting_time=0;
    int turnaround_time=0;
    int response_time=-1;
};
