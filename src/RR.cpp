#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int remaining;
    int turnaround_time=0;
    int waiting_time=0;
}

int main(){
    //processes
    Process p1={1, 0, 6};
    Process p2={2, 2, 8};
    Process p3={3, 4, 3};
    vector<Process> processes={p1, p2, p3};
    //variables
    int n=processes.size();
    int time=0;
    int quantum=2;
    int completed=0;
    queue<int> q;
    vector<bool> inQueue(n, false);

    //add to queue those arrivaing at t==0
    for(int i=0;i<n;i++){
        if(processes[i].arrival_time==0){
            q.push(i);
            inQueue[i]=true;
        }
    }

    while(completed<n){
        if(q.empty()){
            //jump to earliest arrival if empty
            int next_arrival=INT_MAX;
            for(int i=0;i<n;i++){
                int arrival=processes[i].arrival_time;
                if(!inQueue[i]){
                    next_arrival=min(next_arrival, arrival);
                }
            }
            time=next_arrival;

            //add to queue
            for(int i=0;i<n;i++){
                if(!inQueue[i] && processes[i].arrival_time<=time){
                    q.push(i);
                    inQueue[i]=true;
                }
            }
        }
    }
    return 0;
}