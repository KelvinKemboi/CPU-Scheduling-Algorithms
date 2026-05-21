# CPU Scheduling Simulator

A collection of CPU scheduling algorithms. Each algorithm simulates how an operating system scheduler decides which process runs next, and computes waiting time, turnaround time, and response time.

---

## Project structure

```
.
├── FCFS.cpp       — First Come First Served
├── SJF.cpp        — Shortest Job First (non-preemptive)
├── RR.cpp         — Round Robin (quantum=2)
└── PS.cpp         — Priority Scheduling (non-preemptive, higher value = higher priority)
```

---

## Requirements

- Linux or macOS
- g++ with C++20 support

---

## Build

```bash
g++ -std=c++20 FCFS.cpp -o fcfs
g++ -std=c++17 SJF.cpp -o sjf
g++ -std=c++17 RR.cpp -o rr
g++ -std=c++17 PS.cpp -o priority
```

---

## Run

```bash
./fcfs
./sjf
./rr
./priority
```

Each program runs on the same three processes and prints per-process metrics plus averages.

---

## Test processes

All four algorithms run on the same input for direct comparison:

| Process | Arrival | Burst | Priority |
|---|---|---|---|
| P1 | 0 | 6 | 2 |
| P2 | 2 | 8 | 1 |
| P3 | 4 | 3 | 3 |

Priority is only used by `PS.cpp`. RR uses a time slice/quantum of 2.

---

## Algorithms

### FCFS — First Come First Served (`FCFS.cpp`)

Processes run in arrival order. Sorted by `arrival_time` (ties broken by `id`). Once a process starts it runs to completion. Implements a queue

```
Sort by arrival -> run in order -> no preemption
```

**Metrics computed:** `waiting_time`, `turnaround_time`, average waiting time.

---

### SJF — Shortest Job First (`SJF.cpp`)

At each point in time, the scheduler picks the arrived process with the smallest `burst_time`. Non-preemptive - a running process is never interrupted. Uses a `done[]` boolean array to track completed processes and jumps `time` forward to the next arrival when the CPU is idle.

```
At each step: scan arrived processes -> pick smallest burst -> run to completion
```

**Metrics computed:** `waiting_time`, `turnaround_time`, average waiting time.

---

### Round Robin (`RR.cpp`)

Each process gets a fixed time slice (`quantum = 2`). If it does not finish within the quantum it goes to the back of the ready queue. A `remaining` field tracks how much CPU time each process still needs. New arrivals are pushed into the queue as time advances. `response_time` is recorded the first time a process reaches the front of the queue.

```
Queue → pop front → run min(quantum, remaining) → push back if not done
```

**Metrics computed:** `waiting_time`, `turnaround_time`, `response_time`, averages for both.

---

### Priority Scheduling (`PS.cpp`)

At each point in time, the scheduler picks the arrived process with the highest `priority` value (larger number = higher priority). Non-preemptive. Ties default to whichever appears first in the vector. `response_time` is recorded the first time a process is selected.

```
At each step: scan arrived processes -> pick highest priority -> run to completion
```

**Metrics computed:** `waiting_time`, `turnaround_time`, `response_time`, averages for both.

---

## Metrics explained

| Metric | Formula | Meaning |
|---|---|---|
| `waiting_time` | `turnaround_time - burst_time` | Time spent sitting in the ready queue |
| `turnaround_time` | `finish_time - arrival_time` | Total time from arrival to completion |
| `response_time` | `first_run_time - arrival_time` | Time until the process first gets the CPU |

---

## Algorithm comparison

| Algorithm | Preemptive | Optimal for | Weakness |
|---|---|---|---|
| FCFS | No | Simplicity | Long jobs block short ones (convoy effect) |
| SJF | No | Minimizing average wait | Requires knowing burst time in advance |
| Round Robin | Yes | Fairness, response time | Higher turnaround than SJF |
| Priority | No | Urgent job ordering | Low-priority jobs may starve |

---

## Known limitations

- Processes are hardcoded
- SJF and Priority require burst times known upfront
- Round Robin quantum is fixed at 2
