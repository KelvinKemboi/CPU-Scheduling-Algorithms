#include "Process.h"
#include "fcfs/fcfs.h"
#include "sjf/sjf.h"
#include "priority/priority.h"
#include "rr/rr.h"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector<Process> processes(n);
    for(int i=0;i<n;i++){
        int id=i+1;
        cout<<"P"<<id<<" arrival, burst, priority: ";
        cin>>processes[i].arrival_time>>processes[i].burst_time>>processes[i].priority; //input for metric values
        processes[i].id=id;
        processes[i].remaining=processes[i].burst_time;
    }
    int choice;
    int quantum=2; //default time slice
    //show list
    cout<<"\n1. First Come First Served"
    <<"\n2. Shortest Job First"
    <<"\n3. Round Robin"
    <<"\n4. Priority Scheduling"
    <<"\n5. All"; 
    cin>>choice; //pick an algorithm
    if(choice==3||choice==5){
        cout<<"Quantum: ";
        cin>>quantum; //can choose another time slice
    }

    auto run=[&](int algo){
        vector<Process> p=processes;
        switch(algo){
            case 1: fcfs(p); break;
            case 2: sjf(p); break;
            case 3: rr(p, quantum); break;
            case 4: priority(p);
        }
    };
    if(choice==5){
        run(1);
        run(2);
        run(3);
        run(4);
    }else{
        run(choice);
    }
    return 0;
}


