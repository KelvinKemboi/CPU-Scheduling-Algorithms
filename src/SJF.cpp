#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int turnaround_time=0;
    int waiting_time=0;
};

int main(){
    Process p1={1, 0, 6};
    Process p2={2, 2, 8};
    Process p3={3, 4, 3};
    vector<Process> processes={p1, p2, p3};

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
        p.turnaround_time=(time+p.burst_time)-p.arrival_time;
        p.waiting_time=p.turnaround_time-p.burst_time;
        time+=p.burst_time;
        done[shortest]=true;
        completed++;
    }

    //printing results and average wait times
    int av_waiting=0;
    for(auto& p: processes){
        cout<<"P: "<<p.id<<endl;
        cout<<"W.T: "<<p.waiting_time<<endl;
        cout<<"T.T: "<<p.turnaround_time<<endl;
        av_waiting+=p.waiting_time;
    }
    double average=(double) av_waiting/n;
    cout<<"Average waiting time: "<<average<<endl;
    return 0;
}