#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include "sjf.h"
using namespace std;

void sjf(vector<Process>& processes){
    int n=processes.size();
    int time=0;
    int completed=0;
    
    vector<bool> done(n, false); //completed processes
    while(completed<n){
        int shortest=-1; //candidate process;
        for(int i=0;i<n;i++){
            if(done[i]) continue; //skip completed processes
            if(processes[i].arrival_time>time) continue; //skip unarrived processes
            if(shortest==-1 || processes[i].burst_time<processes[shortest].burst_time) shortest=i; //update candidate process
        }
        //if nothing has arrived yet
        if(shortest==-1){
           int next_arrival=INT_MAX; //max integer value
           
           //find earliest arrival for uncompleted processes
           for(int i=0;i<n;i++){
                if(!done[i]){
                    next_arrival=min(next_arrival, processes[i].arrival_time);
                }
           }
           //jump to that arrival time
           time=next_arrival;
           continue;
        }
        //update variables
        Process& p=processes[shortest];
        time+=p.burst_time;
        p.turnaround_time=time-p.arrival_time;
        p.waiting_time=p.turnaround_time-p.burst_time;
        done[shortest]=true;
        completed++;
    }
}