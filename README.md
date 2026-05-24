# CPU Scheduling Simulator

A small C++ simulator for some CPU scheduling algorithms. The
program accepts process details from input, lets you choose one
scheduling strategy, and computes scheduling metrics for each process.

## Supported Algorithms

| Option | Algorithm | Type | Selection rule |
|---|---|---|---|
| 1 | First Come First Served (FCFS) | Non-preemptive | Earliest arrival time runs first |
| 2 | Shortest Job First (SJF) | Non-preemptive | Shortest burst time among arrived processes |
| 3 | Round Robin (RR) | Preemptive | Fixed time quantum, processes rotate through a queue |
| 4 | Priority Scheduling | Non-preemptive | Highest priority value among arrived processes |
| 5 | All algorithms | Mixed | Runs FCFS, SJF, RR, and Priority on the same input |

## Project Structure

```text
CPU-Scheduling/
├── README.md
└── src/
    ├── main.cpp
    ├── Process.h
    ├── fcfs/
    │   ├── fcfs.cpp
    │   └── fcfs.h
    ├── priority/
    │   ├── priority.cpp
    │   └── priority.h
    ├── rr/
    │   ├── rr.cpp
    │   └── rr.h
    └── sjf/
        ├── sjf.cpp
        └── sjf.h
```

## Requirements

- Linux, macOS, or Windows with a C++ compiler
- `g++` or another compiler with C++17 support

## Build

From the project root:

```bash
g++ -std=c++17 -Isrc \
  src/main.cpp \
  src/fcfs/fcfs.cpp \
  src/sjf/sjf.cpp \
  src/rr/rr.cpp \
  src/priority/priority.cpp \
  -o cpu-scheduling
```

## Run

```bash
./cpu-scheduling
```

The program prompts for:

1. The number of processes
2. Each process's arrival time, burst time, and priority
3. The scheduling algorithm to run
4. A time quantum when Round Robin is selected

Example input:

```text
Enter number of processes: 3
P1 arrival, burst, priority: 0 6 2
P2 arrival, burst, priority: 2 8 1
P3 arrival, burst, priority: 4 3 3

1. First Come First Served
2. Shortest Job First
3. Round Robin
4. Priority Scheduling
5. All
5
Quantum: 2
```

## Process Model

Each process is represented by the shared `Process` struct in `src/Process.h`.

| Field | Meaning |
|---|---|
| `id` | Process number assigned by the program |
| `arrival_time` | Time when the process enters the ready queue |
| `burst_time` | Total CPU time required |
| `remaining` | CPU time still needed, used by Round Robin |
| `priority` | Priority value, where a larger value means higher priority |
| `waiting_time` | Total time spent waiting in the ready queue |
| `turnaround_time` | Total time from arrival to completion |
| `response_time` | Time from arrival until the process first gets CPU time |

## Metrics

| Metric | Formula | Meaning |
|---|---|---|
| Waiting time | `turnaround_time - burst_time` | Time spent waiting before and between CPU runs |
| Turnaround time | `finish_time - arrival_time` | Total time from arrival to completion |
| Response time | `first_run_time - arrival_time` | Time until the process first starts running |

## Algorithm Notes

### First Come First Served

FCFS sorts processes by arrival time, using process id as a tie breaker. Each
process runs until it finishes

### Shortest Job First

SJF repeatedly scans the arrived, unfinished processes and selects the one with
the smallest burst time. If no process has arrived yet, the scheduler jumps to
the next arrival time

### Round Robin

Round Robin uses a ready queue and a user-provided quantum. Each process runs
for at most one quantum before either finishing or returning to the back of the
queue

### Priority Scheduling

Priority scheduling repeatedly selects the arrived, unfinished process with the
highest priority value. The implementation is non-preemptive, so a selected
process runs to completion

## Current Limitations

- Process data is entered at runtime.
- SJF and Priority Scheduling require burst time and priority info

