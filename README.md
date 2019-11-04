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
Total threads number is 1
Thread test/example_sleep is executing.
Sleep :300000000
Example value:1
Sleep :300000000
Example value:2
Sleep :300000000
Example value:3
Sleep :300000000
Example value:4
return value:0
No threads ready or runnable, and no pending interrupts.
Assuming the program completed.
Machine halting!

Ticks: total 1200000500, idle 1200000268, system 110, user 122
Disk I/O: reads 0, writes 0
Console I/O: reads 0, writes 0
Paging: faults 0
Network I/O: packets received 0, sent 0
```

# MultiProgramming
```
cd NachOS/code
./userprog/nachos -e test/test1 -e test/test2 -e test/example_sleep
```

output:
```
Total threads number is 3
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
Sleep :300000000
Print integer:7
Print integer:6
return value:0
Print integer:25
return value:0
Example value:1
Sleep :300000000
Example value:2
Sleep :300000000
Example value:3
Sleep :300000000
Example value:4
return value:0
No threads ready or runnable, and no pending interrupts.
Assuming the program completed.
Machine halting!

Ticks: total 1200000700, idle 1200000176, system 180, user 344
Disk I/O: reads 0, writes 0
Console I/O: reads 0, writes 0
Paging: faults 0
Network I/O: packets received 0, sent 0
```
