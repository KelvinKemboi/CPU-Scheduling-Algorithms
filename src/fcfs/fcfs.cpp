#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void fcfs(vector<Process>& processes){
    //sort by arrival time- ascending order
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        if(a.arrival_time==b.arrival_time)
            return a.id<b.id;
        return a.arrival_time<b.arrival_time;
    });
    int current_time=0;
    //loop throguh processes
    for(Process& p:processes){
        //idle check-if finished early, jump to next arrival time
        if(current_time<p.arrival_time){
            current_time=p.arrival_time;
        }
        //update waiting, current, and turnaround time
        p.waiting_time=current_time-p.arrival_time;
        p.turnaround_time=p.waiting_time+p.burst_time;
        current_time+=p.burst_time;
    }
}