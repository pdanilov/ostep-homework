1.  - Q: Compute the response time and turnaround time when running
three jobs of length 200 with the SJF and FIFO schedulers.
    - A: Let's recall fromulaes for the metrics:
        - $T_{response}(N) = \frac{1}{N} \sum_{i=i}^{N} T_{i; firstrun} - T_{i;arrival}$
        - $T_{turnaround}(N) = \frac{1}{N} \sum_{i=i}^{N} T_{i; completion} - T_{i;arrival}$

        Since job lengths are equal, there is no difference between scheduling with SJF and FIFO. Let's calculate:
        - $T_{response, SJF} = \frac{(0-0) + (200-0) + (400-0)}{3} = 200$
        - $T_{turnaround, SJF} = \frac{(200-0) + (400-0) + (600-0)}{3} = 400$
        - $T_{response, FIFO} = \frac{(0-0) + (200-0) + (400-0)}{3} = 200$
        - $T_{turnaround, FIFO} = \frac{(200-0) + (400-0) + (600-0)}{3} = 400$

        Time to check the answer:

        ```sh
        prompt> ./scheduler.py -p SJF -l 200,200,200 -c 
        ARG policy SJF
        ARG jlist 200,200,200

        Here is the job list, with the run time of each job: 
        Job 0 ( length = 200.0 )
        Job 1 ( length = 200.0 )
        Job 2 ( length = 200.0 )


        ** Solutions **

        Execution trace:
        [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
        [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
        [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

        Final statistics:
        Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
        Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
        Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

        Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
        ```

        ```sh
        prompt> ./scheduler.py -p FIFO -l 200,200,200 -c 
        ARG policy FIFO
        ARG jlist 200,200,200

        Here is the job list, with the run time of each job: 
        Job 0 ( length = 200.0 )
        Job 1 ( length = 200.0 )
        Job 2 ( length = 200.0 )


        ** Solutions **

        Execution trace:
        [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
        [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
        [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

        Final statistics:
        Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
        Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
        Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

        Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
        ```

2.  - Q: Now do the same but with jobs of different lengths: 100, 200, and 300.
    
    - A: Since, job length are sorted in increasing order, metrics for SJF and FIFO will be the same%
        - $T_{response, SJF} = \frac{(0-0) + (100-0) + (300-0)}{3} = 133.33$
        - $T_{turnaround, SJF} = \frac{(100-0) + (300-0) + (600-0)}{3} = 333.33$
        - $T_{response, FIFO} = \frac{(0-0) + (100-0) + (300-0)}{3} = 133.33$
        - $T_{turnaround, FIFO} = \frac{(100-0) + (300-0) + (600-0)}{3} = 333.33$

        Check:
        ```sh
        prompt> ./scheduler.py -p SJF -l 100,200,300 -c
        ARG policy SJF
        ARG jlist 100,200,300

        Here is the job list, with the run time of each job: 
        Job 0 ( length = 100.0 )
        Job 1 ( length = 200.0 )
        Job 2 ( length = 300.0 )


        ** Solutions **

        Execution trace:
        [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
        [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
        [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

        Final statistics:
        Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
        Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
        Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

        Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
        ```

        ```sh
        prompt> ./scheduler.py -p FIFO -l 100,200,300 -c
        ARG policy FIFO
        ARG jlist 100,200,300

        Here is the job list, with the run time of each job: 
        Job 0 ( length = 100.0 )
        Job 1 ( length = 200.0 )
        Job 2 ( length = 300.0 )


        ** Solutions **

        Execution trace:
        [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
        [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
        [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

        Final statistics:
        Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
        Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
        Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

        Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
        ```

3.  - Q:  Now do the same, but also with the RR scheduler and a time-slice of 1.

    - A: Let's look at the RR(1) policy: for the first 300 ticks jobs #1, #2 and #3 are executed repetitively for 1 tick. Finish time of job #1 is 298. Then, for the next 200 seconds remaining parts of jobs #2 and #3 are executed, finish time of job #2 is 499. The remaining parts of job #3 are executed during time ticks 501..600. Job #3 finish time is equal to 600.
        - $T_{response, RR} = \frac{(0-0) + (1-0) + (2-0)}{3} = 1$
        - $T_{turnaround, RR} = \frac{(298-0) + (499-0) + (600-0)}{3} = 465.67$

        Checking the answer:

        ```sh
        prompt> ./scheduler.py -p RR -q 1 -l 100,200,300 -c
        ARG policy RR
        ARG jlist 100,200,300

        Here is the job list, with the run time of each job: 
        Job 0 ( length = 100.0 )
        Job 1 ( length = 200.0 )
        Job 2 ( length = 300.0 )


        ** Solutions **

        Execution trace:
        # Omitting output for 600 time ticks
        # ...
        Final statistics:
        Job   0 -- Response: 0.00  Turnaround 298.00  Wait 198.00
        Job   1 -- Response: 1.00  Turnaround 499.00  Wait 299.00
        Job   2 -- Response: 2.00  Turnaround 600.00  Wait 300.00

        Average -- Response: 1.00  Turnaround 465.67  Wait 265.67
        ```

4.  - Q: For what types of workloads does SJF deliver the same turnaround
times as FIFO?
    
    - A: This happens when $length_1 \le length_2 \le ... \le length_N$, since for these inputs "first in" equals to "shortest job first".

5.  - Q: For what types of workloads and quantum lengths does SJF deliver
the same response times as RR?

    - A: Let q be a quantum of RR, then if job lengths are all equal to q then for both SJF and RR switch between jobs happens every q time ticks and also at every switch the previous job is done. If this happens, response time is equal for both methods.

6.  - Q: What happens to response time with SJF as job lengths increase?
Can you use the simulator to demonstrate the trend?

    - A: When job lengths increase, shortest job length increases, so remaining jobs need to wait longer to start execution, i.e. response time increases.

7.  - Q: What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?
    
    - A: We assume that quantum length q is less or equal to all job lengths, otherwise we can imagine a case when q is infinitely large which leads to infinite response time. Then $q = min(l_1, l_2, ..., l_N) = q^*$ is the worst case for response time. $T_{resp, 1} = 0, T_{resp, 2} = q^*, ..., T_{resp, N} = (N-1) * q^*$. $T_{resp, avg} = \frac{0 + q^* + 2*q^* + ... + (N-1)*q^*}{N} = \frac{q^*}{N} \sum_{i=0}^{N-1}i = \frac{q^*}{N} * \frac{N * (N-1)}{2} = \frac{q^* * (N-1)}{2}$.
