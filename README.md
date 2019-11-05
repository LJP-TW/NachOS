# Build
```
git clone https://github.com/LJP-TW/NachOS.git
cd NachOS
sudo cp -r usr /

cd code
make
```

# Run example
```
cd NachOS/code
./userprog/nachos -e test/example_sleep
```

output:
```
Total user threads number is 1
Thread test/example_sleep is executing.
Sleep :100000
Example value:1
Sleep :100000
Example value:2
Sleep :100000
Example value:3
Sleep :100000
Example value:4
return value:0
No threads ready or runnable, and no pending interrupts.
Assuming the program completed.
Machine halting!

Ticks: total 400512, idle 30, system 400360, user 122
Disk I/O: reads 0, writes 0
Console I/O: reads 0, writes 0
Paging: faults 0
Network I/O: packets received 0, sent 0
```

You also can enable debug flag 'S' to see debug info about 'sleep'
```
./userprog/nachos -e test/example_sleep -d S
```

# MultiProgramming
```
cd NachOS/code
./userprog/nachos -e test/test1 -e test/test2 -e test/example_sleep
```

output:
```
Total user threads number is 3
Thread test/test1 is executing.
Thread test/test2 is executing.
Thread test/example_sleep is executing.
Print integer:9
Print integer:8
Print integer:20
Print integer:21
Print integer:22
Print integer:23
Print integer:24
Sleep :100000
Print integer:7
Print integer:6
return value:0
Print integer:25
return value:0
Example value:1
Sleep :100000
Example value:2
Sleep :100000
Example value:3
Sleep :100000
Example value:4
return value:0
No threads ready or runnable, and no pending interrupts.
Assuming the program completed.
Machine halting!

Ticks: total 400714, idle 30, system 400340, user 344
Disk I/O: reads 0, writes 0
Console I/O: reads 0, writes 0
Paging: faults 0
Network I/O: packets received 0, sent 0
```

# CPU Scheduling
- Run Test
```
cd NachOS/code
make testscheduling

cat log/RR      # Round-Robin
cat log/FCFS    # First Come First Serve
cat log/SJF     # Shortest Job First
cat log/SRTF    # Shortest Remain Time First
cat log/NPP     # Non-preemptive Priority
cat log/PP      # Preemptive Priority
```

- Userprogram doesn't support SRTF & SJF
> Because we cannot know job time.

- Run userprogram with RR & FCFS
```
# Default is RR
./userprog/nachos -e test/test3 -e test/test4 -e test/test5 -RR
# FCFS
./userprog/nachos -e test/test3 -e test/test4 -e test/test5 -FCFS
```

- Run userprogram with Non-preemptive Priority & Preemptive Priority
```
# Use -p to set priority
# Non-preemptive Priority
./userprog/nachos -e test/test3 -p 3 -e test/test4 -p 3 -e test/test5 -p 1 -NPP
# Preemptive Priority
./userprog/nachos -e test/test3 -p 3 -e test/test4 -p 3 -e test/test5 -p 1 -PP
```






