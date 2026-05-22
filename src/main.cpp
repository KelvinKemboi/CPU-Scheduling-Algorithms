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

    }
    return 0;
}


