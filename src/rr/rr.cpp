#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "rr.h"
using namespace std;

void rr(vector<Process>& processes, int quantum){
    //variables
    int n=processes.size();
    int time=0;
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
            continue;
        }
        //get frontmost process
        int front=q.front();
        q.pop();
        Process& p=processes[front];

        if(p.response_time==-1){
            p.response_time=time-p.arrival_time;
        }
        //run for quantum time/ remaining time-whichever is smaller
        int run=min(quantum, p.remaining);
        p.remaining-=run;
        time+=run;
        //add any new processes to queue
        for(int i=0;i<n;i++){
            if(!inQueue[i] && processes[i].arrival_time<=time){
                q.push(i);
                inQueue[i]=true;
            }
        }
        //completed check
        if(p.remaining==0){
            p.turnaround_time=time-p.arrival_time;
            p.waiting_time=p.turnaround_time-p.burst_time;
            completed++;
        }else{
            q.push(front); //push back to queue if not done
        }
    }
}