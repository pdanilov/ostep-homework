1.  - Q: Run process-run.py with the following flags: -l 5:100,5:100.
What should the CPU utilization be (e.g., the percent of time the
CPU is in use?) Why do you know this? Use the -c and -p flags to
see if you were right.

    - A: Process PID:0 runs (RUN:cpu state) in first 5 time ticks, while PID:1 is waiting for its turn in READY state, then PID:1 runs (RUN:cpu state) in the following 5 ticks and PID:0 is in the DONE state. CPU column is 1 every tick, so cpu utilization is 100% because there are no ticks when performing IO operation.

        ```sh
        prompt> ./process-run.py -l 5:100,5:100 -c -p
        Time        PID: 0        PID: 1           CPU           IOs
          1        RUN:cpu         READY             1          
          2        RUN:cpu         READY             1          
          3        RUN:cpu         READY             1          
          4        RUN:cpu         READY             1          
          5        RUN:cpu         READY             1          
          6           DONE       RUN:cpu             1          
          7           DONE       RUN:cpu             1          
          8           DONE       RUN:cpu             1          
          9           DONE       RUN:cpu             1          
         10           DONE       RUN:cpu             1          

        Stats: Total Time 10
        Stats: CPU Busy 10 (100.00%)
        Stats: IO Busy  0 (0.00%)  
        ```
 
 2. - Q: Now run with these flags: ./process-run.py -l 4:100,1:0.
These flags specify one process with 4 instructions (all to use the
CPU), and one that simply issues an I/O and waits for it to be done.
How long does it take to complete both processes? Use -c and -p
to find out if you were right.

    - A: Process PID:0 runs (RUN:cpu state) for the first 4 ticks while PID:1 stay in READY state, then PID:0 is in READY state and PID:1 first runs io (RUN:cpu state) followed by 5 ticks (default io length value) in BLOCKED state, finishing in RUN:io_done state. There are 6 ticks when cpu is active: 4 ticks for running PID:0, 1 tick for beginning and 1 for finishing io in PID:1; and there are 5 ticks of active io when cpu isn't active. Total execution time is 11.

        ```sh
        prompt> ./process-run.py -l 4:100,1:0 -c -p
        Time        PID: 0        PID: 1           CPU           IOs
          1        RUN:cpu         READY             1          
          2        RUN:cpu         READY             1          
          3        RUN:cpu         READY             1          
          4        RUN:cpu         READY             1          
          5           DONE        RUN:io             1          
          6           DONE       BLOCKED                           1
          7           DONE       BLOCKED                           1
          8           DONE       BLOCKED                           1
          9           DONE       BLOCKED                           1
         10           DONE       BLOCKED                           1
         11*          DONE   RUN:io_done             1          

        Stats: Total Time 11
        Stats: CPU Busy 6 (54.55%)
        Stats: IO Busy  5 (45.45%)
        ```

3.  - Q: Switch the order of the processes: -l 1:0,4:100. What happens
now? Does switching the order matter? Why? (As always, use -c
and -p to see if you were right)

    - A: During the first tick cpu executes RUN:io for PID:0, then it is PID:1 running in RUN:cpu state for 4 ticks, while PID:0 stays in BLOCKED state. Since io length is equal to 5, at tick number 6 PID:1 becomes DONE but PID:0 is still BLOCKED, so cpu isn't active. At the tick 7 PID:0 finishes execution with RUN:io_done. Total completion time is 7.
        ```sh
        prompt> ./process-run.py -l 1:0,4:100 -c -p
        Time        PID: 0        PID: 1           CPU           IOs
          1         RUN:io         READY             1          
          2        BLOCKED       RUN:cpu             1             1
          3        BLOCKED       RUN:cpu             1             1
          4        BLOCKED       RUN:cpu             1             1
          5        BLOCKED       RUN:cpu             1             1
          6        BLOCKED          DONE                           1
          7*   RUN:io_done          DONE             1          

        Stats: Total Time 7
        Stats: CPU Busy 6 (85.71%)
        Stats: IO Busy  5 (71.43%)
        ```

4.  - Q: We’ll now explore some of the other flags. One important flag is
-S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system
will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100
-c -S SWITCH_ON_END), one doing I/O and the other doing CPU
work?

    - A: This case is equal to question #2 but processes are switched in order, so execution time is equal to 11.
        ```sh
        prompt> ./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END
        Time        PID: 0        PID: 1           CPU           IOs
          1         RUN:io         READY             1          
          2        BLOCKED         READY                           1
          3        BLOCKED         READY                           1
          4        BLOCKED         READY                           1
          5        BLOCKED         READY                           1
          6        BLOCKED         READY                           1
          7*   RUN:io_done         READY             1          
          8           DONE       RUN:cpu             1          
          9           DONE       RUN:cpu             1          
         10           DONE       RUN:cpu             1          
         11           DONE       RUN:cpu             1          
        ```

5.  - Q: Now, run the same processes, but with the switching behavior set
to switch to another process whenever one is WAITING for I/O (-l
1:0,4:100 -c -S SWITCH_ON_IO). What happens now? Use -c
and -p to confirm that you are right.

    - A: This case equal to question #3 since SWITCH_ON_IO is a default policy for this parameter.
        ```sh
        prompt> ./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO
        Time        PID: 0        PID: 1           CPU           IOs
          1         RUN:io         READY             1          
          2        BLOCKED       RUN:cpu             1             1
          3        BLOCKED       RUN:cpu             1             1
          4        BLOCKED       RUN:cpu             1             1
          5        BLOCKED       RUN:cpu             1             1
          6        BLOCKED          DONE                           1
          7*   RUN:io_done          DONE             1          
        ```

6.  - Q: One other important behavior is what to do when an I/O completes. With -I IO_RUN_LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when
you run this combination of processes? (./process-run.py -l
3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I
IO_RUN_LATER) Are system resources being effectively utilized?

    - A: Utilization of resources is ineffective since after completing first io operation the scheduler still waits for another processes to be completed, after that it executes finishing io and executes remaining io operations.
        ```sh
        prompt> ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_LATER
        Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
          1         RUN:io         READY         READY         READY             1          
          2        BLOCKED       RUN:cpu         READY         READY             1             1
          3        BLOCKED       RUN:cpu         READY         READY             1             1
          4        BLOCKED       RUN:cpu         READY         READY             1             1
          5        BLOCKED       RUN:cpu         READY         READY             1             1
          6        BLOCKED       RUN:cpu         READY         READY             1             1
          7*         READY          DONE       RUN:cpu         READY             1          
          8          READY          DONE       RUN:cpu         READY             1          
          9          READY          DONE       RUN:cpu         READY             1          
         10          READY          DONE       RUN:cpu         READY             1          
         11          READY          DONE       RUN:cpu         READY             1          
         12          READY          DONE          DONE       RUN:cpu             1          
         13          READY          DONE          DONE       RUN:cpu             1          
         14          READY          DONE          DONE       RUN:cpu             1          
         15          READY          DONE          DONE       RUN:cpu             1          
         16          READY          DONE          DONE       RUN:cpu             1          
         17    RUN:io_done          DONE          DONE          DONE             1          
         18         RUN:io          DONE          DONE          DONE             1          
         19        BLOCKED          DONE          DONE          DONE                           1
         20        BLOCKED          DONE          DONE          DONE                           1
         21        BLOCKED          DONE          DONE          DONE                           1
         22        BLOCKED          DONE          DONE          DONE                           1
         23        BLOCKED          DONE          DONE          DONE                           1
         24*   RUN:io_done          DONE          DONE          DONE             1          
         25         RUN:io          DONE          DONE          DONE             1          
         26        BLOCKED          DONE          DONE          DONE                           1
         27        BLOCKED          DONE          DONE          DONE                           1
         28        BLOCKED          DONE          DONE          DONE                           1
         29        BLOCKED          DONE          DONE          DONE                           1
         30        BLOCKED          DONE          DONE          DONE                           1
         31*   RUN:io_done          DONE          DONE          DONE             1          

        Stats: Total Time 31
        Stats: CPU Busy 21 (67.74%)
        Stats: IO Busy  15 (48.39%)
        ```

7.  - Q: Now run the same processes, but with -I IO_RUN_IMMEDIATE set,
which immediately runs the process that issued the I/O. How does
this behavior differ? Why might running a process that just completed an I/O again be a good idea?

    - A: In this case finishing io task leads to immediate executing io_done task and starting next io task then switching to another cpu-bound task. This strategy leads to huge shortening of execution time. The idea of immediate processing of finished io task is good because starting next io task has little cpu task, after that the context can be switched to cpu-bound task.
        ```sh
        prompt> ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_IMMEDIATE
        Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
          1         RUN:io         READY         READY         READY             1          
          2        BLOCKED       RUN:cpu         READY         READY             1             1
          3        BLOCKED       RUN:cpu         READY         READY             1             1
          4        BLOCKED       RUN:cpu         READY         READY             1             1
          5        BLOCKED       RUN:cpu         READY         READY             1             1
          6        BLOCKED       RUN:cpu         READY         READY             1             1
          7*   RUN:io_done          DONE         READY         READY             1          
          8         RUN:io          DONE         READY         READY             1          
          9        BLOCKED          DONE       RUN:cpu         READY             1             1
         10        BLOCKED          DONE       RUN:cpu         READY             1             1
         11        BLOCKED          DONE       RUN:cpu         READY             1             1
         12        BLOCKED          DONE       RUN:cpu         READY             1             1
         13        BLOCKED          DONE       RUN:cpu         READY             1             1
         14*   RUN:io_done          DONE          DONE         READY             1          
         15         RUN:io          DONE          DONE         READY             1          
         16        BLOCKED          DONE          DONE       RUN:cpu             1             1
         17        BLOCKED          DONE          DONE       RUN:cpu             1             1
         18        BLOCKED          DONE          DONE       RUN:cpu             1             1
         19        BLOCKED          DONE          DONE       RUN:cpu             1             1
         20        BLOCKED          DONE          DONE       RUN:cpu             1             1
         21*   RUN:io_done          DONE          DONE          DONE             1          

        Stats: Total Time 21
        Stats: CPU Busy 21 (100.00%)
        Stats: IO Busy  15 (71.43%)
        ```

8.  - Q: Now run with some randomly generated processes using flags -s
1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50,
3:50. See if you can predict how the trace will turn out. What happens when you use the flag -I IO_RUN_IMMEDIATE versus that
flag -I IO_RUN_LATER? What happens when you use the flag -S
SWITCH_ON_IO versus -S SWITCH_ON_END?

    - A: Let's use an example with random seed value of 1.
      ```sh
      prompt> ./process-run.py -s 1 -l 3:50,3:50
      Produce a trace of what would happen when you run these processes:
      Process 0
        cpu
        io
        io_done
        io
        io_done

      Process 1
        cpu
        cpu
        cpu

      Important behaviors:
      System will switch when the current process is FINISHED or ISSUES AN IO
      After IOs, the process issuing the IO will run LATER (when it is its turn)
      ```
      Since default switch policy is switching on io, then during first ticks cpu executes instructions from PID:0, after io context switch happens to PID:1. IO task default length is 5, so during ticks 3 to 5 cpu tasks are executed from PID:1, then PID:1 stays in DONE state and PID:0 is BLOCKED util tick 8 in which cpu executes io_done task from PID:0. After that another RUN:io happens, 5 more ticks being BLOCKED and the final RUN:io_done happens at the tick 15.
      ```sh
      prompt> ./process-run.py -s 1 -l 3:50,3:50 -c -p
      Time        PID: 0        PID: 1           CPU           IOs
        1        RUN:cpu         READY             1          
        2         RUN:io         READY             1          
        3        BLOCKED       RUN:cpu             1             1
        4        BLOCKED       RUN:cpu             1             1
        5        BLOCKED       RUN:cpu             1             1
        6        BLOCKED          DONE                           1
        7        BLOCKED          DONE                           1
        8*   RUN:io_done          DONE             1          
        9         RUN:io          DONE             1          
       10        BLOCKED          DONE                           1
       11        BLOCKED          DONE                           1
       12        BLOCKED          DONE                           1
       13        BLOCKED          DONE                           1
       14        BLOCKED          DONE                           1
       15*   RUN:io_done          DONE             1          

    Stats: Total Time 15
    Stats: CPU Busy 8 (53.33%)
    Stats: IO Busy  10 (66.67%)
    ```
    Using flag -I IO_RUN_LATER doesn't change anything because it's a default policy for this parameter; the same for -I IO_RUN_IMMEDIATE because the first io_done in PID:0 happens after PID:1 is in the DONE state.
    Using flag -S SWITCH_ON_IO is a default policy, so the result is same; -S SWITCH_ON_END results in a longer execution time since tasks from PID:1 executes only after all the tasks from PID:0 are finished.
