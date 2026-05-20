#include <iostream>
#include <vector>
using namespace std;

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int response_time;
    int turnaround_time=0;
    int waiting_time=0;
};

int main() {
    Process p1={1, 0, 6, 2, 6};
    Process p2={2, 2, 8, 1, 8};
    Process p3={3, 4, 3, 3, 3};
    //processes
    vector<Process>processes={p1, p2, p3};
    //variables
    int n=processes.size();
    int completed=0;
    int time=0;
    vector<bool> done(n false);

    while(completed<n){
        int selected=-1;
        for(int i=0;i<n;i++){
            if(done[i]) continue; //skip completed
            if(processes[i].arrival_time>time) continue; //skip unarrived
            if(selected==-1 || processes[i].priority>processes[selected].priority) selected=i; //update based on priority
        }
    }
    
    return 0;
}