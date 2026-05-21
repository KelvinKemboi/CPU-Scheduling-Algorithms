#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void priority(vector<Process>& processes) {
    //variables
    int n=processes.size();
    int completed=0;
    int time=0;
    vector<bool> done(n,false);

    while(completed<n){
        int selected=-1;
        for(int i=0;i<n;i++){
            if(done[i]) continue; //skip completed
            if(processes[i].arrival_time>time) continue; //skip unarrived
            if(selected==-1 || processes[i].priority>processes[selected].priority) selected=i; //update based on priority
        }
        //idle check-jump to earliest arrival
        if(selected==-1){
            int next=INT_MAX;
            for(int i=0;i<n;i++){
                int v=processes[i].arrival_time;
                next=min(next, v);
            }
            time=next;
            continue;
        }
        //select process
        Process& p=processes[selected];

        //update response time
        if(p.response_time==-1){
            p.response_time=time-p.arrival_time;
        }
        //update variables
        time+=p.burst_time;
        p.turnaround_time=time-p.arrival_time;
        p.waiting_time=p.turnaround_time-p.burst_time;
        done[selected]=true;
        completed++;
    }
}