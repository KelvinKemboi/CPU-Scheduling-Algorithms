#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Process struct
struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int turnaround_time=0;
    int waiting_time=0;
};

int main(){
    //example process objects
    Process p1={1,0,6};
    Process p2={2,2,8};
    Process p3={3,4,3};
    vector<Process> processes={p1,p2,p3}; //vector for Process objects- {id, arrival, burst}
    
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
    int av=0;
    for(auto& p: processes){
        av+=p.waiting_time;
    }
    double average=double(av)/processes.size();
    cout<<"Average: "<<average<<endl;
    return 0;
}