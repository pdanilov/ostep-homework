1.  - Q: Run a few randomly-generated problems with just two jobs and
two queues; compute the MLFQ execution trace for each. Make
your life easier by limiting the length of each job and turning off
I/Os.

    - A: This task is too complicated for handwriting, let's just use the simulator resources:

        ```sh
        prompt> ./mlfq.py -n 2 -j 2 -m 10 -M 0 -i 0 -q 5 -s 0 -c
        Here is the list of inputs:
        OPTIONS jobs 2
        OPTIONS queues 2
        OPTIONS allotments for queue  1 is   1
        OPTIONS quantum length for queue  1 is   5
        OPTIONS allotments for queue  0 is   1
        OPTIONS quantum length for queue  0 is   5
        OPTIONS boost 0
        OPTIONS ioTime 0
        OPTIONS stayAfterIO False
        OPTIONS iobump False


        For each job, three defining characteristics are given:
        startTime : at what time does the job enter the system
        runTime   : the total CPU time needed by the job to finish
        ioFreq    : every ioFreq time units, the job issues an I/O
                    (the I/O takes ioTime units to complete)

        Job List:
        Job  0: startTime   0 - runTime   8 - ioFreq   0
        Job  1: startTime   0 - runTime   4 - ioFreq   0


        Execution Trace:

        [ time 0 ] JOB BEGINS by JOB 0
        [ time 0 ] JOB BEGINS by JOB 1
        [ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 7 (of 8) ]
        [ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 6 (of 8) ]
        [ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 5 (of 8) ]
        [ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 4 (of 8) ]
        [ time 4 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 3 (of 8) ]
        [ time 5 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 3 (of 4) ]
        [ time 6 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 2 (of 4) ]
        [ time 7 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 1 (of 4) ]
        [ time 8 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 0 (of 4) ]
        [ time 9 ] FINISHED JOB 1
        [ time 9 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 2 (of 8) ]
        [ time 10 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 1 (of 8) ]
        [ time 11 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 0 (of 8) ]
        [ time 12 ] FINISHED JOB 0

        Final statistics:
        Job  0: startTime   0 - response   0 - turnaround  12
        Job  1: startTime   0 - response   5 - turnaround   9

        Avg  1: startTime n/a - response 2.50 - turnaround 10.50
        ```

2.  - Q: How would you run the scheduler to reproduce each of the examples in the chapter?

    - A: Let's dive into these cases:
        - Example 1: A Single Long-Running Job. Three queues, single job with length 200, time slice is 10, allotment is equal to time slice.

            ```sh
            prompt> ./mlfq.py -n 3 -l 0,200,0 -q 10 -a 1 -c
            Here is the list of inputs:
            OPTIONS jobs 1
            OPTIONS queues 3
            OPTIONS allotments for queue  2 is   1
            OPTIONS quantum length for queue  2 is  10
            OPTIONS allotments for queue  1 is   1
            OPTIONS quantum length for queue  1 is  10
            OPTIONS allotments for queue  0 is   1
            OPTIONS quantum length for queue  0 is  10
            OPTIONS boost 0
            OPTIONS ioTime 5
            OPTIONS stayAfterIO False
            OPTIONS iobump False


            For each job, three defining characteristics are given:
            startTime : at what time does the job enter the system
            runTime   : the total CPU time needed by the job to finish
            ioFreq    : every ioFreq time units, the job issues an I/O
                        (the I/O takes ioTime units to complete)

            Job List:
            Job  0: startTime   0 - runTime 200 - ioFreq   0


            Execution Trace:

            [ time 0 ] JOB BEGINS by JOB 0
            [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 200) ]
            [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 200) ]
            [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 200) ]
            [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 200) ]
            [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 200) ]
            [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 200) ]
            [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 200) ]
            [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 200) ]
            [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 200) ]
            [ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 200) ]
            [ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 189 (of 200) ]
            [ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 188 (of 200) ]
            [ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 187 (of 200) ]
            [ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 186 (of 200) ]
            [ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 185 (of 200) ]
            [ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 184 (of 200) ]
            [ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 183 (of 200) ]
            [ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 182 (of 200) ]
            [ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 181 (of 200) ]
            [ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 180 (of 200) ]
            [ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 179 (of 200) ]
            [ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 178 (of 200) ]
            [ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 177 (of 200) ]
            [ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 176 (of 200) ]
            [ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 175 (of 200) ]
            [ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 174 (of 200) ]
            [ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 173 (of 200) ]
            [ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 172 (of 200) ]
            [ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 171 (of 200) ]
            [ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 170 (of 200) ]
            [ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 169 (of 200) ]
            [ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 168 (of 200) ]
            [ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 167 (of 200) ]
            [ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 166 (of 200) ]
            [ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 165 (of 200) ]
            [ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 164 (of 200) ]
            [ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 163 (of 200) ]
            [ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 162 (of 200) ]
            [ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 161 (of 200) ]
            [ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 160 (of 200) ]
            [ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 159 (of 200) ]
            [ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 158 (of 200) ]
            [ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 157 (of 200) ]
            [ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 156 (of 200) ]
            [ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 155 (of 200) ]
            [ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 154 (of 200) ]
            [ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 153 (of 200) ]
            [ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 152 (of 200) ]
            [ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 151 (of 200) ]
            [ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 150 (of 200) ]
            [ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 149 (of 200) ]
            [ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 148 (of 200) ]
            [ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 147 (of 200) ]
            [ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 146 (of 200) ]
            [ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 145 (of 200) ]
            [ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 144 (of 200) ]
            [ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 143 (of 200) ]
            [ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 142 (of 200) ]
            [ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 141 (of 200) ]
            [ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 140 (of 200) ]
            [ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 139 (of 200) ]
            [ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 138 (of 200) ]
            [ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 137 (of 200) ]
            [ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 136 (of 200) ]
            [ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 135 (of 200) ]
            [ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 134 (of 200) ]
            [ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 133 (of 200) ]
            [ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 132 (of 200) ]
            [ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 131 (of 200) ]
            [ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 130 (of 200) ]
            [ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 129 (of 200) ]
            [ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 128 (of 200) ]
            [ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 127 (of 200) ]
            [ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 126 (of 200) ]
            [ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 125 (of 200) ]
            [ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 124 (of 200) ]
            [ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 123 (of 200) ]
            [ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 122 (of 200) ]
            [ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 121 (of 200) ]
            [ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 120 (of 200) ]
            [ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 119 (of 200) ]
            [ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 118 (of 200) ]
            [ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 117 (of 200) ]
            [ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 116 (of 200) ]
            [ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 115 (of 200) ]
            [ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 114 (of 200) ]
            [ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 113 (of 200) ]
            [ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 112 (of 200) ]
            [ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 111 (of 200) ]
            [ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 110 (of 200) ]
            [ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 109 (of 200) ]
            [ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 108 (of 200) ]
            [ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 107 (of 200) ]
            [ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 106 (of 200) ]
            [ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 105 (of 200) ]
            [ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 104 (of 200) ]
            [ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 103 (of 200) ]
            [ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 102 (of 200) ]
            [ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 101 (of 200) ]
            [ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 100 (of 200) ]
            [ time 100 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 99 (of 200) ]
            [ time 101 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 98 (of 200) ]
            [ time 102 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 97 (of 200) ]
            [ time 103 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 96 (of 200) ]
            [ time 104 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 95 (of 200) ]
            [ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 94 (of 200) ]
            [ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 93 (of 200) ]
            [ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 92 (of 200) ]
            [ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 91 (of 200) ]
            [ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 90 (of 200) ]
            [ time 110 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 89 (of 200) ]
            [ time 111 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 88 (of 200) ]
            [ time 112 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 87 (of 200) ]
            [ time 113 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 86 (of 200) ]
            [ time 114 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 85 (of 200) ]
            [ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 84 (of 200) ]
            [ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 83 (of 200) ]
            [ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 82 (of 200) ]
            [ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 81 (of 200) ]
            [ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 80 (of 200) ]
            [ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 79 (of 200) ]
            [ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 78 (of 200) ]
            [ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 77 (of 200) ]
            [ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 76 (of 200) ]
            [ time 124 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 75 (of 200) ]
            [ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 74 (of 200) ]
            [ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 73 (of 200) ]
            [ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 72 (of 200) ]
            [ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 71 (of 200) ]
            [ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 70 (of 200) ]
            [ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 69 (of 200) ]
            [ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 68 (of 200) ]
            [ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 67 (of 200) ]
            [ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 66 (of 200) ]
            [ time 134 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 65 (of 200) ]
            [ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 64 (of 200) ]
            [ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 63 (of 200) ]
            [ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 62 (of 200) ]
            [ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 61 (of 200) ]
            [ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 60 (of 200) ]
            [ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 200) ]
            [ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 200) ]
            [ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 200) ]
            [ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 200) ]
            [ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 200) ]
            [ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 200) ]
            [ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 200) ]
            [ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 200) ]
            [ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 200) ]
            [ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 200) ]
            [ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 49 (of 200) ]
            [ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 48 (of 200) ]
            [ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 47 (of 200) ]
            [ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 46 (of 200) ]
            [ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 45 (of 200) ]
            [ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 44 (of 200) ]
            [ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 43 (of 200) ]
            [ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 42 (of 200) ]
            [ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 41 (of 200) ]
            [ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 40 (of 200) ]
            [ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 39 (of 200) ]
            [ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 38 (of 200) ]
            [ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 37 (of 200) ]
            [ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 36 (of 200) ]
            [ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 35 (of 200) ]
            [ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 34 (of 200) ]
            [ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 33 (of 200) ]
            [ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 32 (of 200) ]
            [ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 31 (of 200) ]
            [ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 30 (of 200) ]
            [ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 200) ]
            [ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 200) ]
            [ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 200) ]
            [ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 200) ]
            [ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 200) ]
            [ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 200) ]
            [ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 200) ]
            [ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 200) ]
            [ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 200) ]
            [ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 200) ]
            [ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 200) ]
            [ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 200) ]
            [ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 200) ]
            [ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 200) ]
            [ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 200) ]
            [ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 200) ]
            [ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 200) ]
            [ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 200) ]
            [ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 200) ]
            [ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 200) ]
            [ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 200) ]
            [ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 200) ]
            [ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 200) ]
            [ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 200) ]
            [ time 194 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 200) ]
            [ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 200) ]
            [ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 200) ]
            [ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 200) ]
            [ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 200) ]
            [ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 200) ]
            [ time 200 ] FINISHED JOB 0

            Final statistics:
            Job  0: startTime   0 - response   0 - turnaround 200

            Avg  0: startTime n/a - response 0.00 - turnaround 200.00
            ```

        - Example 2: Same setup for number of queues, quantum and allotment, but there are two jobs: first of them is cpu-intensive, it's length is 180; the second one arrives at T = 100 and its length is 20.

            ```sh
            prompt> ./mlfq.py -n 3 -l 0,180,0:100,20,0 -q 10 -a 1 -c
            Here is the list of inputs:
            OPTIONS jobs 2
            OPTIONS queues 3
            OPTIONS allotments for queue  2 is   1
            OPTIONS quantum length for queue  2 is  10
            OPTIONS allotments for queue  1 is   1
            OPTIONS quantum length for queue  1 is  10
            OPTIONS allotments for queue  0 is   1
            OPTIONS quantum length for queue  0 is  10
            OPTIONS boost 0
            OPTIONS ioTime 5
            OPTIONS stayAfterIO False
            OPTIONS iobump False


            For each job, three defining characteristics are given:
            startTime : at what time does the job enter the system
            runTime   : the total CPU time needed by the job to finish
            ioFreq    : every ioFreq time units, the job issues an I/O
                        (the I/O takes ioTime units to complete)

            Job List:
            Job  0: startTime   0 - runTime 180 - ioFreq   0
            Job  1: startTime 100 - runTime  20 - ioFreq   0


            Execution Trace:

            [ time 0 ] JOB BEGINS by JOB 0
            [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 179 (of 180) ]
            [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 178 (of 180) ]
            [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 177 (of 180) ]
            [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 176 (of 180) ]
            [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 175 (of 180) ]
            [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 174 (of 180) ]
            [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 173 (of 180) ]
            [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 172 (of 180) ]
            [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 171 (of 180) ]
            [ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 170 (of 180) ]
            [ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 169 (of 180) ]
            [ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 168 (of 180) ]
            [ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 167 (of 180) ]
            [ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 166 (of 180) ]
            [ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 165 (of 180) ]
            [ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 164 (of 180) ]
            [ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 163 (of 180) ]
            [ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 162 (of 180) ]
            [ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 161 (of 180) ]
            [ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 160 (of 180) ]
            [ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 159 (of 180) ]
            [ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 158 (of 180) ]
            [ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 157 (of 180) ]
            [ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 156 (of 180) ]
            [ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 155 (of 180) ]
            [ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 154 (of 180) ]
            [ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 153 (of 180) ]
            [ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 152 (of 180) ]
            [ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 151 (of 180) ]
            [ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 150 (of 180) ]
            [ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 149 (of 180) ]
            [ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 148 (of 180) ]
            [ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 147 (of 180) ]
            [ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 146 (of 180) ]
            [ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 145 (of 180) ]
            [ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 144 (of 180) ]
            [ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 143 (of 180) ]
            [ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 142 (of 180) ]
            [ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 141 (of 180) ]
            [ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 140 (of 180) ]
            [ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 139 (of 180) ]
            [ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 138 (of 180) ]
            [ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 137 (of 180) ]
            [ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 136 (of 180) ]
            [ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 135 (of 180) ]
            [ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 134 (of 180) ]
            [ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 133 (of 180) ]
            [ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 132 (of 180) ]
            [ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 131 (of 180) ]
            [ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 130 (of 180) ]
            [ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 129 (of 180) ]
            [ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 128 (of 180) ]
            [ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 127 (of 180) ]
            [ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 126 (of 180) ]
            [ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 125 (of 180) ]
            [ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 124 (of 180) ]
            [ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 123 (of 180) ]
            [ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 122 (of 180) ]
            [ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 121 (of 180) ]
            [ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 120 (of 180) ]
            [ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 119 (of 180) ]
            [ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 118 (of 180) ]
            [ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 117 (of 180) ]
            [ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 116 (of 180) ]
            [ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 115 (of 180) ]
            [ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 114 (of 180) ]
            [ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 113 (of 180) ]
            [ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 112 (of 180) ]
            [ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 111 (of 180) ]
            [ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 110 (of 180) ]
            [ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 109 (of 180) ]
            [ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 108 (of 180) ]
            [ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 107 (of 180) ]
            [ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 106 (of 180) ]
            [ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 105 (of 180) ]
            [ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 104 (of 180) ]
            [ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 103 (of 180) ]
            [ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 102 (of 180) ]
            [ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 101 (of 180) ]
            [ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 100 (of 180) ]
            [ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 99 (of 180) ]
            [ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 98 (of 180) ]
            [ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 97 (of 180) ]
            [ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 96 (of 180) ]
            [ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 95 (of 180) ]
            [ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 94 (of 180) ]
            [ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 93 (of 180) ]
            [ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 92 (of 180) ]
            [ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 91 (of 180) ]
            [ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 90 (of 180) ]
            [ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 89 (of 180) ]
            [ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 88 (of 180) ]
            [ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 87 (of 180) ]
            [ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 86 (of 180) ]
            [ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 85 (of 180) ]
            [ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 84 (of 180) ]
            [ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 83 (of 180) ]
            [ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 82 (of 180) ]
            [ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 81 (of 180) ]
            [ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 80 (of 180) ]
            [ time 100 ] JOB BEGINS by JOB 1
            [ time 100 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 19 (of 20) ]
            [ time 101 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 18 (of 20) ]
            [ time 102 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 17 (of 20) ]
            [ time 103 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 16 (of 20) ]
            [ time 104 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 15 (of 20) ]
            [ time 105 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 14 (of 20) ]
            [ time 106 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 13 (of 20) ]
            [ time 107 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 12 (of 20) ]
            [ time 108 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 11 (of 20) ]
            [ time 109 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 10 (of 20) ]
            [ time 110 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 9 (of 20) ]
            [ time 111 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 8 (of 20) ]
            [ time 112 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 7 (of 20) ]
            [ time 113 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 6 (of 20) ]
            [ time 114 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 5 (of 20) ]
            [ time 115 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 4 (of 20) ]
            [ time 116 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 3 (of 20) ]
            [ time 117 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 2 (of 20) ]
            [ time 118 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 1 (of 20) ]
            [ time 119 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 0 (of 20) ]
            [ time 120 ] FINISHED JOB 1
            [ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 79 (of 180) ]
            [ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 78 (of 180) ]
            [ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 77 (of 180) ]
            [ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 76 (of 180) ]
            [ time 124 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 75 (of 180) ]
            [ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 74 (of 180) ]
            [ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 73 (of 180) ]
            [ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 72 (of 180) ]
            [ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 71 (of 180) ]
            [ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 70 (of 180) ]
            [ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 69 (of 180) ]
            [ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 68 (of 180) ]
            [ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 67 (of 180) ]
            [ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 66 (of 180) ]
            [ time 134 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 65 (of 180) ]
            [ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 64 (of 180) ]
            [ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 63 (of 180) ]
            [ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 62 (of 180) ]
            [ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 61 (of 180) ]
            [ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 60 (of 180) ]
            [ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 180) ]
            [ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 180) ]
            [ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 180) ]
            [ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 180) ]
            [ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 180) ]
            [ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 180) ]
            [ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 180) ]
            [ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 180) ]
            [ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 180) ]
            [ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 180) ]
            [ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 49 (of 180) ]
            [ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 48 (of 180) ]
            [ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 47 (of 180) ]
            [ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 46 (of 180) ]
            [ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 45 (of 180) ]
            [ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 44 (of 180) ]
            [ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 43 (of 180) ]
            [ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 42 (of 180) ]
            [ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 41 (of 180) ]
            [ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 40 (of 180) ]
            [ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 39 (of 180) ]
            [ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 38 (of 180) ]
            [ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 37 (of 180) ]
            [ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 36 (of 180) ]
            [ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 35 (of 180) ]
            [ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 34 (of 180) ]
            [ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 33 (of 180) ]
            [ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 32 (of 180) ]
            [ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 31 (of 180) ]
            [ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 30 (of 180) ]
            [ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 180) ]
            [ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 180) ]
            [ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 180) ]
            [ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 180) ]
            [ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 180) ]
            [ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 180) ]
            [ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 180) ]
            [ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 180) ]
            [ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 180) ]
            [ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 180) ]
            [ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 180) ]
            [ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 180) ]
            [ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 180) ]
            [ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 180) ]
            [ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 180) ]
            [ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 180) ]
            [ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 180) ]
            [ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 180) ]
            [ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 180) ]
            [ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 180) ]
            [ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 180) ]
            [ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 180) ]
            [ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 180) ]
            [ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 180) ]
            [ time 194 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 180) ]
            [ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 180) ]
            [ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 180) ]
            [ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 180) ]
            [ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 180) ]
            [ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 180) ]
            [ time 200 ] FINISHED JOB 0

            Final statistics:
            Job  0: startTime   0 - response   0 - turnaround 200
            Job  1: startTime 100 - response   0 - turnaround  20

            Avg  1: startTime n/a - response 0.00 - turnaround 110.00
            ```

        - Example 3: the same setup as in the previous example, but the second task arrives at the T = 50 and performs IO after every 1ms of execution on the CPU, while its length is 25. It's important to specify the simulator that we use the rule of staying at the same priority if the current task's cpu usage is less than alotment and running IO happens.

            ```sh
            prompt> ./mlfq.py -n 3 -l 0,175,0:50,25,1 -S -q 10 -a 1 -c
            Here is the list of inputs:
            OPTIONS jobs 2
            OPTIONS queues 3
            OPTIONS allotments for queue  2 is   1
            OPTIONS quantum length for queue  2 is  10
            OPTIONS allotments for queue  1 is   1
            OPTIONS quantum length for queue  1 is  10
            OPTIONS allotments for queue  0 is   1
            OPTIONS quantum length for queue  0 is  10
            OPTIONS boost 0
            OPTIONS ioTime 5
            OPTIONS stayAfterIO True
            OPTIONS iobump False


            For each job, three defining characteristics are given:
            startTime : at what time does the job enter the system
            runTime   : the total CPU time needed by the job to finish
            ioFreq    : every ioFreq time units, the job issues an I/O
                        (the I/O takes ioTime units to complete)

            Job List:
            Job  0: startTime   0 - runTime 175 - ioFreq   0
            Job  1: startTime  50 - runTime  25 - ioFreq   1


            Execution Trace:

            [ time 0 ] JOB BEGINS by JOB 0
            [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 174 (of 175) ]
            [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 173 (of 175) ]
            [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 172 (of 175) ]
            [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 171 (of 175) ]
            [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 170 (of 175) ]
            [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 169 (of 175) ]
            [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 168 (of 175) ]
            [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 167 (of 175) ]
            [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 166 (of 175) ]
            [ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 165 (of 175) ]
            [ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 164 (of 175) ]
            [ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 163 (of 175) ]
            [ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 162 (of 175) ]
            [ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 161 (of 175) ]
            [ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 160 (of 175) ]
            [ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 159 (of 175) ]
            [ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 158 (of 175) ]
            [ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 157 (of 175) ]
            [ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 156 (of 175) ]
            [ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 155 (of 175) ]
            [ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 154 (of 175) ]
            [ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 153 (of 175) ]
            [ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 152 (of 175) ]
            [ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 151 (of 175) ]
            [ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 150 (of 175) ]
            [ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 149 (of 175) ]
            [ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 148 (of 175) ]
            [ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 147 (of 175) ]
            [ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 146 (of 175) ]
            [ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 145 (of 175) ]
            [ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 144 (of 175) ]
            [ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 143 (of 175) ]
            [ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 142 (of 175) ]
            [ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 141 (of 175) ]
            [ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 140 (of 175) ]
            [ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 139 (of 175) ]
            [ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 138 (of 175) ]
            [ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 137 (of 175) ]
            [ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 136 (of 175) ]
            [ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 135 (of 175) ]
            [ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 134 (of 175) ]
            [ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 133 (of 175) ]
            [ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 132 (of 175) ]
            [ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 131 (of 175) ]
            [ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 130 (of 175) ]
            [ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 129 (of 175) ]
            [ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 128 (of 175) ]
            [ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 127 (of 175) ]
            [ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 126 (of 175) ]
            [ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 125 (of 175) ]
            [ time 50 ] JOB BEGINS by JOB 1
            [ time 50 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 24 (of 25) ]
            [ time 51 ] IO_START by JOB 1
            IO DONE
            [ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 124 (of 175) ]
            [ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 123 (of 175) ]
            [ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 122 (of 175) ]
            [ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 121 (of 175) ]
            [ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 120 (of 175) ]
            [ time 56 ] IO_DONE by JOB 1
            [ time 56 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 23 (of 25) ]
            [ time 57 ] IO_START by JOB 1
            IO DONE
            [ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 119 (of 175) ]
            [ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 118 (of 175) ]
            [ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 117 (of 175) ]
            [ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 116 (of 175) ]
            [ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 115 (of 175) ]
            [ time 62 ] IO_DONE by JOB 1
            [ time 62 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 22 (of 25) ]
            [ time 63 ] IO_START by JOB 1
            IO DONE
            [ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 114 (of 175) ]
            [ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 113 (of 175) ]
            [ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 112 (of 175) ]
            [ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 111 (of 175) ]
            [ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 110 (of 175) ]
            [ time 68 ] IO_DONE by JOB 1
            [ time 68 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 21 (of 25) ]
            [ time 69 ] IO_START by JOB 1
            IO DONE
            [ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 109 (of 175) ]
            [ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 108 (of 175) ]
            [ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 107 (of 175) ]
            [ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 106 (of 175) ]
            [ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 105 (of 175) ]
            [ time 74 ] IO_DONE by JOB 1
            [ time 74 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 20 (of 25) ]
            [ time 75 ] IO_START by JOB 1
            IO DONE
            [ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 104 (of 175) ]
            [ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 103 (of 175) ]
            [ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 102 (of 175) ]
            [ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 101 (of 175) ]
            [ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 100 (of 175) ]
            [ time 80 ] IO_DONE by JOB 1
            [ time 80 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 19 (of 25) ]
            [ time 81 ] IO_START by JOB 1
            IO DONE
            [ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 99 (of 175) ]
            [ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 98 (of 175) ]
            [ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 97 (of 175) ]
            [ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 96 (of 175) ]
            [ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 95 (of 175) ]
            [ time 86 ] IO_DONE by JOB 1
            [ time 86 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 18 (of 25) ]
            [ time 87 ] IO_START by JOB 1
            IO DONE
            [ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 94 (of 175) ]
            [ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 93 (of 175) ]
            [ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 92 (of 175) ]
            [ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 91 (of 175) ]
            [ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 90 (of 175) ]
            [ time 92 ] IO_DONE by JOB 1
            [ time 92 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 17 (of 25) ]
            [ time 93 ] IO_START by JOB 1
            IO DONE
            [ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 89 (of 175) ]
            [ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 88 (of 175) ]
            [ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 87 (of 175) ]
            [ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 86 (of 175) ]
            [ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 85 (of 175) ]
            [ time 98 ] IO_DONE by JOB 1
            [ time 98 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 16 (of 25) ]
            [ time 99 ] IO_START by JOB 1
            IO DONE
            [ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 84 (of 175) ]
            [ time 100 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 83 (of 175) ]
            [ time 101 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 82 (of 175) ]
            [ time 102 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 81 (of 175) ]
            [ time 103 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 80 (of 175) ]
            [ time 104 ] IO_DONE by JOB 1
            [ time 104 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 15 (of 25) ]
            [ time 105 ] IO_START by JOB 1
            IO DONE
            [ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 79 (of 175) ]
            [ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 78 (of 175) ]
            [ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 77 (of 175) ]
            [ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 76 (of 175) ]
            [ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 75 (of 175) ]
            [ time 110 ] IO_DONE by JOB 1
            [ time 110 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 14 (of 25) ]
            [ time 111 ] IO_START by JOB 1
            IO DONE
            [ time 111 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 74 (of 175) ]
            [ time 112 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 73 (of 175) ]
            [ time 113 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 72 (of 175) ]
            [ time 114 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 71 (of 175) ]
            [ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 70 (of 175) ]
            [ time 116 ] IO_DONE by JOB 1
            [ time 116 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 13 (of 25) ]
            [ time 117 ] IO_START by JOB 1
            IO DONE
            [ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 69 (of 175) ]
            [ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 68 (of 175) ]
            [ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 67 (of 175) ]
            [ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 66 (of 175) ]
            [ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 65 (of 175) ]
            [ time 122 ] IO_DONE by JOB 1
            [ time 122 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 12 (of 25) ]
            [ time 123 ] IO_START by JOB 1
            IO DONE
            [ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 64 (of 175) ]
            [ time 124 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 63 (of 175) ]
            [ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 62 (of 175) ]
            [ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 61 (of 175) ]
            [ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 60 (of 175) ]
            [ time 128 ] IO_DONE by JOB 1
            [ time 128 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 11 (of 25) ]
            [ time 129 ] IO_START by JOB 1
            IO DONE
            [ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 59 (of 175) ]
            [ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 58 (of 175) ]
            [ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 57 (of 175) ]
            [ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 56 (of 175) ]
            [ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 55 (of 175) ]
            [ time 134 ] IO_DONE by JOB 1
            [ time 134 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 10 (of 25) ]
            [ time 135 ] IO_START by JOB 1
            IO DONE
            [ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 54 (of 175) ]
            [ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 53 (of 175) ]
            [ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 52 (of 175) ]
            [ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 51 (of 175) ]
            [ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 50 (of 175) ]
            [ time 140 ] IO_DONE by JOB 1
            [ time 140 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 9 (of 25) ]
            [ time 141 ] IO_START by JOB 1
            IO DONE
            [ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 49 (of 175) ]
            [ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 48 (of 175) ]
            [ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 47 (of 175) ]
            [ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 46 (of 175) ]
            [ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 45 (of 175) ]
            [ time 146 ] IO_DONE by JOB 1
            [ time 146 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 8 (of 25) ]
            [ time 147 ] IO_START by JOB 1
            IO DONE
            [ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 44 (of 175) ]
            [ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 43 (of 175) ]
            [ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 42 (of 175) ]
            [ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 41 (of 175) ]
            [ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 40 (of 175) ]
            [ time 152 ] IO_DONE by JOB 1
            [ time 152 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 7 (of 25) ]
            [ time 153 ] IO_START by JOB 1
            IO DONE
            [ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 39 (of 175) ]
            [ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 38 (of 175) ]
            [ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 37 (of 175) ]
            [ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 36 (of 175) ]
            [ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 35 (of 175) ]
            [ time 158 ] IO_DONE by JOB 1
            [ time 158 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 6 (of 25) ]
            [ time 159 ] IO_START by JOB 1
            IO DONE
            [ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 34 (of 175) ]
            [ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 33 (of 175) ]
            [ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 32 (of 175) ]
            [ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 31 (of 175) ]
            [ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 30 (of 175) ]
            [ time 164 ] IO_DONE by JOB 1
            [ time 164 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 5 (of 25) ]
            [ time 165 ] IO_START by JOB 1
            IO DONE
            [ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 29 (of 175) ]
            [ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 28 (of 175) ]
            [ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 27 (of 175) ]
            [ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 26 (of 175) ]
            [ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 25 (of 175) ]
            [ time 170 ] IO_DONE by JOB 1
            [ time 170 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 4 (of 25) ]
            [ time 171 ] IO_START by JOB 1
            IO DONE
            [ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 24 (of 175) ]
            [ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 23 (of 175) ]
            [ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 22 (of 175) ]
            [ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 21 (of 175) ]
            [ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 20 (of 175) ]
            [ time 176 ] IO_DONE by JOB 1
            [ time 176 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 3 (of 25) ]
            [ time 177 ] IO_START by JOB 1
            IO DONE
            [ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 19 (of 175) ]
            [ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 18 (of 175) ]
            [ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 17 (of 175) ]
            [ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 16 (of 175) ]
            [ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 15 (of 175) ]
            [ time 182 ] IO_DONE by JOB 1
            [ time 182 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 2 (of 25) ]
            [ time 183 ] IO_START by JOB 1
            IO DONE
            [ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 14 (of 175) ]
            [ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 13 (of 175) ]
            [ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 12 (of 175) ]
            [ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 11 (of 175) ]
            [ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 10 (of 175) ]
            [ time 188 ] IO_DONE by JOB 1
            [ time 188 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 1 (of 25) ]
            [ time 189 ] IO_START by JOB 1
            IO DONE
            [ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 9 (of 175) ]
            [ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 8 (of 175) ]
            [ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 7 (of 175) ]
            [ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 6 (of 175) ]
            [ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 5 (of 175) ]
            [ time 194 ] IO_DONE by JOB 1
            [ time 194 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 0 (of 25) ]
            [ time 195 ] FINISHED JOB 1
            [ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 4 (of 175) ]
            [ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 3 (of 175) ]
            [ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 2 (of 175) ]
            [ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 1 (of 175) ]
            [ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 0 (of 175) ]
            [ time 200 ] FINISHED JOB 0

            Final statistics:
            Job  0: startTime   0 - response   0 - turnaround 200
            Job  1: startTime  50 - response   0 - turnaround 145

            Avg  1: startTime n/a - response 0.00 - turnaround 172.50
            ```

        - Example 4: one cpu-intensive task with length 100 and two io-bound tasks, both of length 50, executing IO every 2ms, IO-time is also 2ms; both arrive at T = 100.

            ```sh
            prompt> ./mlfq.py -n 3 -l 0,100,0:100,50,2:100,50,2 -S -i 2 -q 10 -a 1 -c
            Here is the list of inputs:
            OPTIONS jobs 3
            OPTIONS queues 3
            OPTIONS allotments for queue  2 is   1
            OPTIONS quantum length for queue  2 is  10
            OPTIONS allotments for queue  1 is   1
            OPTIONS quantum length for queue  1 is  10
            OPTIONS allotments for queue  0 is   1
            OPTIONS quantum length for queue  0 is  10
            OPTIONS boost 0
            OPTIONS ioTime 2
            OPTIONS stayAfterIO True
            OPTIONS iobump False


            For each job, three defining characteristics are given:
            startTime : at what time does the job enter the system
            runTime   : the total CPU time needed by the job to finish
            ioFreq    : every ioFreq time units, the job issues an I/O
                        (the I/O takes ioTime units to complete)

            Job List:
            Job  0: startTime   0 - runTime 100 - ioFreq   0
            Job  1: startTime 100 - runTime  50 - ioFreq   2
            Job  2: startTime 100 - runTime  50 - ioFreq   2


            Execution Trace:

            [ time 0 ] JOB BEGINS by JOB 0
            [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
            [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
            [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
            [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
            [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
            [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 94 (of 100) ]
            [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 93 (of 100) ]
            [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 92 (of 100) ]
            [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 91 (of 100) ]
            [ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 90 (of 100) ]
            [ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 89 (of 100) ]
            [ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 88 (of 100) ]
            [ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 87 (of 100) ]
            [ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 86 (of 100) ]
            [ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 85 (of 100) ]
            [ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 84 (of 100) ]
            [ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 83 (of 100) ]
            [ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 82 (of 100) ]
            [ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 81 (of 100) ]
            [ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 80 (of 100) ]
            [ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 79 (of 100) ]
            [ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 78 (of 100) ]
            [ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 77 (of 100) ]
            [ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 76 (of 100) ]
            [ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 75 (of 100) ]
            [ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 74 (of 100) ]
            [ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 73 (of 100) ]
            [ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 72 (of 100) ]
            [ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 71 (of 100) ]
            [ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 70 (of 100) ]
            [ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 69 (of 100) ]
            [ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 68 (of 100) ]
            [ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 67 (of 100) ]
            [ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 66 (of 100) ]
            [ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 65 (of 100) ]
            [ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 64 (of 100) ]
            [ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 63 (of 100) ]
            [ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 62 (of 100) ]
            [ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 61 (of 100) ]
            [ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 60 (of 100) ]
            [ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 100) ]
            [ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 100) ]
            [ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 100) ]
            [ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 100) ]
            [ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 100) ]
            [ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 100) ]
            [ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 100) ]
            [ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 100) ]
            [ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 100) ]
            [ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 100) ]
            [ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 49 (of 100) ]
            [ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 48 (of 100) ]
            [ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 47 (of 100) ]
            [ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 46 (of 100) ]
            [ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 45 (of 100) ]
            [ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 44 (of 100) ]
            [ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 43 (of 100) ]
            [ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 42 (of 100) ]
            [ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 41 (of 100) ]
            [ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 40 (of 100) ]
            [ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 39 (of 100) ]
            [ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 38 (of 100) ]
            [ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 37 (of 100) ]
            [ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 36 (of 100) ]
            [ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 35 (of 100) ]
            [ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 34 (of 100) ]
            [ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 33 (of 100) ]
            [ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 32 (of 100) ]
            [ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 31 (of 100) ]
            [ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 30 (of 100) ]
            [ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 100) ]
            [ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 100) ]
            [ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 100) ]
            [ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 100) ]
            [ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 100) ]
            [ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 100) ]
            [ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 100) ]
            [ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 100) ]
            [ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 100) ]
            [ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 100) ]
            [ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 100) ]
            [ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 100) ]
            [ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 100) ]
            [ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 100) ]
            [ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 100) ]
            [ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 100) ]
            [ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 100) ]
            [ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 100) ]
            [ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 100) ]
            [ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 100) ]
            [ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 100) ]
            [ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 100) ]
            [ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 100) ]
            [ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 100) ]
            [ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 100) ]
            [ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 100) ]
            [ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 100) ]
            [ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 100) ]
            [ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 100) ]
            [ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 100) ]
            [ time 100 ] FINISHED JOB 0
            [ time 100 ] JOB BEGINS by JOB 1
            [ time 100 ] JOB BEGINS by JOB 2
            [ time 100 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 49 (of 50) ]
            [ time 101 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 48 (of 50) ]
            [ time 102 ] IO_START by JOB 1
            IO DONE
            [ time 102 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 49 (of 50) ]
            [ time 103 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 48 (of 50) ]
            [ time 104 ] IO_START by JOB 2
            IO DONE
            [ time 104 ] IO_DONE by JOB 1
            [ time 104 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 47 (of 50) ]
            [ time 105 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 46 (of 50) ]
            [ time 106 ] IO_START by JOB 1
            IO DONE
            [ time 106 ] IO_DONE by JOB 2
            [ time 106 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 47 (of 50) ]
            [ time 107 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 46 (of 50) ]
            [ time 108 ] IO_START by JOB 2
            IO DONE
            [ time 108 ] IO_DONE by JOB 1
            [ time 108 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 45 (of 50) ]
            [ time 109 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 44 (of 50) ]
            [ time 110 ] IO_START by JOB 1
            IO DONE
            [ time 110 ] IO_DONE by JOB 2
            [ time 110 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 45 (of 50) ]
            [ time 111 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 44 (of 50) ]
            [ time 112 ] IO_START by JOB 2
            IO DONE
            [ time 112 ] IO_DONE by JOB 1
            [ time 112 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 43 (of 50) ]
            [ time 113 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 42 (of 50) ]
            [ time 114 ] IO_START by JOB 1
            IO DONE
            [ time 114 ] IO_DONE by JOB 2
            [ time 114 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 43 (of 50) ]
            [ time 115 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 42 (of 50) ]
            [ time 116 ] IO_START by JOB 2
            IO DONE
            [ time 116 ] IO_DONE by JOB 1
            [ time 116 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 41 (of 50) ]
            [ time 117 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 40 (of 50) ]
            [ time 118 ] IO_START by JOB 1
            IO DONE
            [ time 118 ] IO_DONE by JOB 2
            [ time 118 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 41 (of 50) ]
            [ time 119 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 40 (of 50) ]
            [ time 120 ] IO_START by JOB 2
            IO DONE
            [ time 120 ] IO_DONE by JOB 1
            [ time 120 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 39 (of 50) ]
            [ time 121 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 38 (of 50) ]
            [ time 122 ] IO_START by JOB 1
            IO DONE
            [ time 122 ] IO_DONE by JOB 2
            [ time 122 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 39 (of 50) ]
            [ time 123 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 38 (of 50) ]
            [ time 124 ] IO_START by JOB 2
            IO DONE
            [ time 124 ] IO_DONE by JOB 1
            [ time 124 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 37 (of 50) ]
            [ time 125 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 36 (of 50) ]
            [ time 126 ] IO_START by JOB 1
            IO DONE
            [ time 126 ] IO_DONE by JOB 2
            [ time 126 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 37 (of 50) ]
            [ time 127 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 36 (of 50) ]
            [ time 128 ] IO_START by JOB 2
            IO DONE
            [ time 128 ] IO_DONE by JOB 1
            [ time 128 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 35 (of 50) ]
            [ time 129 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 34 (of 50) ]
            [ time 130 ] IO_START by JOB 1
            IO DONE
            [ time 130 ] IO_DONE by JOB 2
            [ time 130 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 35 (of 50) ]
            [ time 131 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 34 (of 50) ]
            [ time 132 ] IO_START by JOB 2
            IO DONE
            [ time 132 ] IO_DONE by JOB 1
            [ time 132 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 33 (of 50) ]
            [ time 133 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 32 (of 50) ]
            [ time 134 ] IO_START by JOB 1
            IO DONE
            [ time 134 ] IO_DONE by JOB 2
            [ time 134 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 33 (of 50) ]
            [ time 135 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 32 (of 50) ]
            [ time 136 ] IO_START by JOB 2
            IO DONE
            [ time 136 ] IO_DONE by JOB 1
            [ time 136 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 31 (of 50) ]
            [ time 137 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 30 (of 50) ]
            [ time 138 ] IO_START by JOB 1
            IO DONE
            [ time 138 ] IO_DONE by JOB 2
            [ time 138 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 31 (of 50) ]
            [ time 139 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 30 (of 50) ]
            [ time 140 ] IO_START by JOB 2
            IO DONE
            [ time 140 ] IO_DONE by JOB 1
            [ time 140 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 29 (of 50) ]
            [ time 141 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 28 (of 50) ]
            [ time 142 ] IO_START by JOB 1
            IO DONE
            [ time 142 ] IO_DONE by JOB 2
            [ time 142 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 29 (of 50) ]
            [ time 143 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 28 (of 50) ]
            [ time 144 ] IO_START by JOB 2
            IO DONE
            [ time 144 ] IO_DONE by JOB 1
            [ time 144 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 27 (of 50) ]
            [ time 145 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 26 (of 50) ]
            [ time 146 ] IO_START by JOB 1
            IO DONE
            [ time 146 ] IO_DONE by JOB 2
            [ time 146 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 27 (of 50) ]
            [ time 147 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 26 (of 50) ]
            [ time 148 ] IO_START by JOB 2
            IO DONE
            [ time 148 ] IO_DONE by JOB 1
            [ time 148 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 25 (of 50) ]
            [ time 149 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 24 (of 50) ]
            [ time 150 ] IO_START by JOB 1
            IO DONE
            [ time 150 ] IO_DONE by JOB 2
            [ time 150 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 25 (of 50) ]
            [ time 151 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 24 (of 50) ]
            [ time 152 ] IO_START by JOB 2
            IO DONE
            [ time 152 ] IO_DONE by JOB 1
            [ time 152 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 23 (of 50) ]
            [ time 153 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 22 (of 50) ]
            [ time 154 ] IO_START by JOB 1
            IO DONE
            [ time 154 ] IO_DONE by JOB 2
            [ time 154 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 23 (of 50) ]
            [ time 155 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 22 (of 50) ]
            [ time 156 ] IO_START by JOB 2
            IO DONE
            [ time 156 ] IO_DONE by JOB 1
            [ time 156 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 21 (of 50) ]
            [ time 157 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 20 (of 50) ]
            [ time 158 ] IO_START by JOB 1
            IO DONE
            [ time 158 ] IO_DONE by JOB 2
            [ time 158 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 21 (of 50) ]
            [ time 159 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 20 (of 50) ]
            [ time 160 ] IO_START by JOB 2
            IO DONE
            [ time 160 ] IO_DONE by JOB 1
            [ time 160 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 19 (of 50) ]
            [ time 161 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 18 (of 50) ]
            [ time 162 ] IO_START by JOB 1
            IO DONE
            [ time 162 ] IO_DONE by JOB 2
            [ time 162 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 19 (of 50) ]
            [ time 163 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 18 (of 50) ]
            [ time 164 ] IO_START by JOB 2
            IO DONE
            [ time 164 ] IO_DONE by JOB 1
            [ time 164 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 17 (of 50) ]
            [ time 165 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 16 (of 50) ]
            [ time 166 ] IO_START by JOB 1
            IO DONE
            [ time 166 ] IO_DONE by JOB 2
            [ time 166 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 17 (of 50) ]
            [ time 167 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 16 (of 50) ]
            [ time 168 ] IO_START by JOB 2
            IO DONE
            [ time 168 ] IO_DONE by JOB 1
            [ time 168 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 15 (of 50) ]
            [ time 169 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 14 (of 50) ]
            [ time 170 ] IO_START by JOB 1
            IO DONE
            [ time 170 ] IO_DONE by JOB 2
            [ time 170 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 15 (of 50) ]
            [ time 171 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 14 (of 50) ]
            [ time 172 ] IO_START by JOB 2
            IO DONE
            [ time 172 ] IO_DONE by JOB 1
            [ time 172 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 13 (of 50) ]
            [ time 173 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 12 (of 50) ]
            [ time 174 ] IO_START by JOB 1
            IO DONE
            [ time 174 ] IO_DONE by JOB 2
            [ time 174 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 13 (of 50) ]
            [ time 175 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 12 (of 50) ]
            [ time 176 ] IO_START by JOB 2
            IO DONE
            [ time 176 ] IO_DONE by JOB 1
            [ time 176 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 11 (of 50) ]
            [ time 177 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 10 (of 50) ]
            [ time 178 ] IO_START by JOB 1
            IO DONE
            [ time 178 ] IO_DONE by JOB 2
            [ time 178 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 11 (of 50) ]
            [ time 179 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 10 (of 50) ]
            [ time 180 ] IO_START by JOB 2
            IO DONE
            [ time 180 ] IO_DONE by JOB 1
            [ time 180 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 9 (of 50) ]
            [ time 181 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 8 (of 50) ]
            [ time 182 ] IO_START by JOB 1
            IO DONE
            [ time 182 ] IO_DONE by JOB 2
            [ time 182 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 9 (of 50) ]
            [ time 183 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 8 (of 50) ]
            [ time 184 ] IO_START by JOB 2
            IO DONE
            [ time 184 ] IO_DONE by JOB 1
            [ time 184 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 7 (of 50) ]
            [ time 185 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 6 (of 50) ]
            [ time 186 ] IO_START by JOB 1
            IO DONE
            [ time 186 ] IO_DONE by JOB 2
            [ time 186 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 7 (of 50) ]
            [ time 187 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 6 (of 50) ]
            [ time 188 ] IO_START by JOB 2
            IO DONE
            [ time 188 ] IO_DONE by JOB 1
            [ time 188 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 5 (of 50) ]
            [ time 189 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 4 (of 50) ]
            [ time 190 ] IO_START by JOB 1
            IO DONE
            [ time 190 ] IO_DONE by JOB 2
            [ time 190 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 5 (of 50) ]
            [ time 191 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 4 (of 50) ]
            [ time 192 ] IO_START by JOB 2
            IO DONE
            [ time 192 ] IO_DONE by JOB 1
            [ time 192 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 3 (of 50) ]
            [ time 193 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 2 (of 50) ]
            [ time 194 ] IO_START by JOB 1
            IO DONE
            [ time 194 ] IO_DONE by JOB 2
            [ time 194 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 3 (of 50) ]
            [ time 195 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 2 (of 50) ]
            [ time 196 ] IO_START by JOB 2
            IO DONE
            [ time 196 ] IO_DONE by JOB 1
            [ time 196 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 1 (of 50) ]
            [ time 197 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 0 (of 50) ]
            [ time 198 ] FINISHED JOB 1
            [ time 198 ] IO_DONE by JOB 2
            [ time 198 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 1 (of 50) ]
            [ time 199 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 0 (of 50) ]
            [ time 200 ] FINISHED JOB 2

            Final statistics:
            Job  0: startTime   0 - response   0 - turnaround 100
            Job  1: startTime 100 - response   0 - turnaround  98
            Job  2: startTime 100 - response   2 - turnaround 100

            Avg  2: startTime n/a - response 0.67 - turnaround 99.33
            ```

        - Example 5: one cpu-intensive task of length 130 and two short-lasting tasks both of length 30 with io-call every 2ms; task-boost after 100ms. My verdict is that this setup is impossible to simulate in our environment, because it's clear from the book that after boosting cpu-intensive task it remains at the highest priority level after 3 10ms cycles which is impossible, since priority drop must happen. And io-bound tasks reset their allotment after io-calls, but if this happens, cpu-bound task will never run until both io-bound tasks finish.

3.  - Q: How would you configure the scheduler parameters to behave just
like a round-robin scheduler?

    - A: To implement Round Robin scheduling we should limit number of queues to 1.

4.  - Q: Craft a workload with two jobs and scheduler parameters so that
one job takes advantage of the older Rules 4a and 4b (turned on
with the -S flag) to game the scheduler and obtain 99% of the CPU
over a particular time interval.

    - A: Consider a scheduler with zero IO-length, quantum size 10 and two jobs of size 100, one of them requests IO every 9ms. If `-S` flag is provided, the first task run for the first 9 time ticks, then the second one runs for the whole allotment interval of 10, it's priority decreases, then the first task comes back consuming cpu resources until it's complete.
    
        ```sh
        prompt> ./mlfq.py -n 3 -l 0,100,9:0,100,0 -i 0 -S -q 10 -a 1 -c   
        Here is the list of inputs:
        OPTIONS jobs 2
        OPTIONS queues 3
        OPTIONS allotments for queue  2 is   1
        OPTIONS quantum length for queue  2 is  10
        OPTIONS allotments for queue  1 is   1
        OPTIONS quantum length for queue  1 is  10
        OPTIONS allotments for queue  0 is   1
        OPTIONS quantum length for queue  0 is  10
        OPTIONS boost 0
        OPTIONS ioTime 0
        OPTIONS stayAfterIO True
        OPTIONS iobump False


        For each job, three defining characteristics are given:
        startTime : at what time does the job enter the system
        runTime   : the total CPU time needed by the job to finish
        ioFreq    : every ioFreq time units, the job issues an I/O
                    (the I/O takes ioTime units to complete)

        Job List:
        Job  0: startTime   0 - runTime 100 - ioFreq   9
        Job  1: startTime   0 - runTime 100 - ioFreq   0


        Execution Trace:

        [ time 0 ] JOB BEGINS by JOB 0
        [ time 0 ] JOB BEGINS by JOB 1
        [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
        [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
        [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
        [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
        [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
        [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 94 (of 100) ]
        [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 93 (of 100) ]
        [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 92 (of 100) ]
        [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 91 (of 100) ]
        [ time 9 ] IO_START by JOB 0
        IO DONE
        [ time 9 ] IO_DONE by JOB 0
        [ time 9 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
        [ time 10 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
        [ time 11 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
        [ time 12 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
        [ time 13 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
        [ time 14 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 94 (of 100) ]
        [ time 15 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 93 (of 100) ]
        [ time 16 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 92 (of 100) ]
        [ time 17 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 91 (of 100) ]
        [ time 18 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 90 (of 100) ]
        [ time 19 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 90 (of 100) ]
        [ time 20 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 89 (of 100) ]
        [ time 21 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 88 (of 100) ]
        [ time 22 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 87 (of 100) ]
        [ time 23 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 86 (of 100) ]
        [ time 24 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 85 (of 100) ]
        [ time 25 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 84 (of 100) ]
        [ time 26 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 83 (of 100) ]
        [ time 27 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 82 (of 100) ]
        [ time 28 ] IO_START by JOB 0
        IO DONE
        [ time 28 ] IO_DONE by JOB 0
        [ time 28 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 81 (of 100) ]
        [ time 29 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 80 (of 100) ]
        [ time 30 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 79 (of 100) ]
        [ time 31 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 78 (of 100) ]
        [ time 32 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 77 (of 100) ]
        [ time 33 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 76 (of 100) ]
        [ time 34 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 75 (of 100) ]
        [ time 35 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 74 (of 100) ]
        [ time 36 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 73 (of 100) ]
        [ time 37 ] IO_START by JOB 0
        IO DONE
        [ time 37 ] IO_DONE by JOB 0
        [ time 37 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 72 (of 100) ]
        [ time 38 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 71 (of 100) ]
        [ time 39 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 70 (of 100) ]
        [ time 40 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 69 (of 100) ]
        [ time 41 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 68 (of 100) ]
        [ time 42 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 67 (of 100) ]
        [ time 43 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 66 (of 100) ]
        [ time 44 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 65 (of 100) ]
        [ time 45 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 64 (of 100) ]
        [ time 46 ] IO_START by JOB 0
        IO DONE
        [ time 46 ] IO_DONE by JOB 0
        [ time 46 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 63 (of 100) ]
        [ time 47 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 62 (of 100) ]
        [ time 48 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 61 (of 100) ]
        [ time 49 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 60 (of 100) ]
        [ time 50 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 59 (of 100) ]
        [ time 51 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 58 (of 100) ]
        [ time 52 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 57 (of 100) ]
        [ time 53 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 56 (of 100) ]
        [ time 54 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 55 (of 100) ]
        [ time 55 ] IO_START by JOB 0
        IO DONE
        [ time 55 ] IO_DONE by JOB 0
        [ time 55 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 54 (of 100) ]
        [ time 56 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 53 (of 100) ]
        [ time 57 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 52 (of 100) ]
        [ time 58 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 51 (of 100) ]
        [ time 59 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 50 (of 100) ]
        [ time 60 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 49 (of 100) ]
        [ time 61 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 48 (of 100) ]
        [ time 62 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 47 (of 100) ]
        [ time 63 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 46 (of 100) ]
        [ time 64 ] IO_START by JOB 0
        IO DONE
        [ time 64 ] IO_DONE by JOB 0
        [ time 64 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 45 (of 100) ]
        [ time 65 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 44 (of 100) ]
        [ time 66 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 43 (of 100) ]
        [ time 67 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 42 (of 100) ]
        [ time 68 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 41 (of 100) ]
        [ time 69 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 40 (of 100) ]
        [ time 70 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 39 (of 100) ]
        [ time 71 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 38 (of 100) ]
        [ time 72 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 37 (of 100) ]
        [ time 73 ] IO_START by JOB 0
        IO DONE
        [ time 73 ] IO_DONE by JOB 0
        [ time 73 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 36 (of 100) ]
        [ time 74 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 35 (of 100) ]
        [ time 75 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 34 (of 100) ]
        [ time 76 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 33 (of 100) ]
        [ time 77 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 32 (of 100) ]
        [ time 78 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 31 (of 100) ]
        [ time 79 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 30 (of 100) ]
        [ time 80 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 29 (of 100) ]
        [ time 81 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 28 (of 100) ]
        [ time 82 ] IO_START by JOB 0
        IO DONE
        [ time 82 ] IO_DONE by JOB 0
        [ time 82 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 27 (of 100) ]
        [ time 83 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 26 (of 100) ]
        [ time 84 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 25 (of 100) ]
        [ time 85 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 24 (of 100) ]
        [ time 86 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 23 (of 100) ]
        [ time 87 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 22 (of 100) ]
        [ time 88 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 21 (of 100) ]
        [ time 89 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 20 (of 100) ]
        [ time 90 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 19 (of 100) ]
        [ time 91 ] IO_START by JOB 0
        IO DONE
        [ time 91 ] IO_DONE by JOB 0
        [ time 91 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 18 (of 100) ]
        [ time 92 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 17 (of 100) ]
        [ time 93 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 16 (of 100) ]
        [ time 94 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 15 (of 100) ]
        [ time 95 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 14 (of 100) ]
        [ time 96 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 13 (of 100) ]
        [ time 97 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 12 (of 100) ]
        [ time 98 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 11 (of 100) ]
        [ time 99 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 10 (of 100) ]
        [ time 100 ] IO_START by JOB 0
        IO DONE
        [ time 100 ] IO_DONE by JOB 0
        [ time 100 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 9 (of 100) ]
        [ time 101 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 8 (of 100) ]
        [ time 102 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 7 (of 100) ]
        [ time 103 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 6 (of 100) ]
        [ time 104 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 5 (of 100) ]
        [ time 105 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 4 (of 100) ]
        [ time 106 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 3 (of 100) ]
        [ time 107 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 2 (of 100) ]
        [ time 108 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 1 (of 100) ]
        [ time 109 ] IO_START by JOB 0
        IO DONE
        [ time 109 ] IO_DONE by JOB 0
        [ time 109 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 0 (of 100) ]
        [ time 110 ] FINISHED JOB 0
        [ time 110 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 89 (of 100) ]
        [ time 111 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 88 (of 100) ]
        [ time 112 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 87 (of 100) ]
        [ time 113 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 86 (of 100) ]
        [ time 114 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 85 (of 100) ]
        [ time 115 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 84 (of 100) ]
        [ time 116 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 83 (of 100) ]
        [ time 117 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 82 (of 100) ]
        [ time 118 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 81 (of 100) ]
        [ time 119 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 80 (of 100) ]
        [ time 120 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 79 (of 100) ]
        [ time 121 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 78 (of 100) ]
        [ time 122 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 77 (of 100) ]
        [ time 123 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 76 (of 100) ]
        [ time 124 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 75 (of 100) ]
        [ time 125 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 74 (of 100) ]
        [ time 126 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 73 (of 100) ]
        [ time 127 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 72 (of 100) ]
        [ time 128 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 71 (of 100) ]
        [ time 129 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 70 (of 100) ]
        [ time 130 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 69 (of 100) ]
        [ time 131 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 68 (of 100) ]
        [ time 132 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 67 (of 100) ]
        [ time 133 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 66 (of 100) ]
        [ time 134 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 65 (of 100) ]
        [ time 135 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 64 (of 100) ]
        [ time 136 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 63 (of 100) ]
        [ time 137 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 62 (of 100) ]
        [ time 138 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 61 (of 100) ]
        [ time 139 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 60 (of 100) ]
        [ time 140 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 100) ]
        [ time 141 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 100) ]
        [ time 142 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 100) ]
        [ time 143 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 100) ]
        [ time 144 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 100) ]
        [ time 145 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 100) ]
        [ time 146 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 100) ]
        [ time 147 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 100) ]
        [ time 148 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 100) ]
        [ time 149 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 100) ]
        [ time 150 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 49 (of 100) ]
        [ time 151 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 48 (of 100) ]
        [ time 152 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 47 (of 100) ]
        [ time 153 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 46 (of 100) ]
        [ time 154 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 45 (of 100) ]
        [ time 155 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 44 (of 100) ]
        [ time 156 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 43 (of 100) ]
        [ time 157 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 42 (of 100) ]
        [ time 158 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 41 (of 100) ]
        [ time 159 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 40 (of 100) ]
        [ time 160 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 39 (of 100) ]
        [ time 161 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 38 (of 100) ]
        [ time 162 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 37 (of 100) ]
        [ time 163 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 36 (of 100) ]
        [ time 164 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 35 (of 100) ]
        [ time 165 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 34 (of 100) ]
        [ time 166 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 33 (of 100) ]
        [ time 167 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 32 (of 100) ]
        [ time 168 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 31 (of 100) ]
        [ time 169 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 30 (of 100) ]
        [ time 170 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 100) ]
        [ time 171 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 100) ]
        [ time 172 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 100) ]
        [ time 173 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 100) ]
        [ time 174 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 100) ]
        [ time 175 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 100) ]
        [ time 176 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 100) ]
        [ time 177 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 100) ]
        [ time 178 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 100) ]
        [ time 179 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 100) ]
        [ time 180 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 100) ]
        [ time 181 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 100) ]
        [ time 182 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 100) ]
        [ time 183 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 100) ]
        [ time 184 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 100) ]
        [ time 185 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 100) ]
        [ time 186 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 100) ]
        [ time 187 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 100) ]
        [ time 188 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 100) ]
        [ time 189 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 100) ]
        [ time 190 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 100) ]
        [ time 191 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 100) ]
        [ time 192 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 100) ]
        [ time 193 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 100) ]
        [ time 194 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 100) ]
        [ time 195 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 100) ]
        [ time 196 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 100) ]
        [ time 197 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 100) ]
        [ time 198 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 100) ]
        [ time 199 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 100) ]
        [ time 200 ] FINISHED JOB 1

        Final statistics:
        Job  0: startTime   0 - response   0 - turnaround 110
        Job  1: startTime   0 - response   9 - turnaround 200

        Avg  1: startTime n/a - response 4.50 - turnaround 155.00
        ```

5.  - Q: Given a system with a quantum length of 10 ms in its highest queue,
how often would you have to boost jobs back to the highest priority
level (with the -B flag) in order to guarantee that a single longrunning (and potentially-starving) job gets at least 5% of the CPU?

    - A: We can execute a task for 10ms continuously and it's a 5% of 200ms interval, so we can boost a task every 200ms to provide a 5% guarantee.

6.  - Q: One question that arises in scheduling is which end of a queue to
add a job that just finished I/O; the -I flag changes this behavior
for this scheduling simulator. Play around with some workloads
and see if you can see the effect of this flag.

    - A: I think moving finished I/O task to the end of current queue is more fair policy since the opposite strategy can lead to scheduler gaming within the scope of a single queue level.
