1.  - Q: Run ./fork.py -s 10 and see which actions are taken. Can you
predict what the process tree looks like at each step? Use the -c
flag to check your answers. Try some different random seeds (-s)
or add more actions (-a) to get the hang of it.

    - A: Let's generate some sequence of actions (forks and exits)

        ```sh
        prompt> ./fork.py -s 10

        ARG seed 10
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree False
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False

                                Process Tree:
                                    a

        Action: a forks b
        Process Tree?
        Action: a forks c
        Process Tree?
        Action: c EXITS
        Process Tree?
        Action: a forks d
        Process Tree?
        Action: a forks e
        Process Tree?
        ```
        Process Trees at every step should look like this

        Step 1:
        ```
        a
        └──b
        ```
        Step 2:
        ```
        a
        ├── b
        └── c
        ```
        Step 3:
        ```
        a
        └──b
        ```
        Step 4:
        ```
        a
        ├── b
        └── d
        ```
        Step 5:
        ```
        a
        ├── b
        ├── d
        └── e
        ```

2.  - Q: One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next
action is a fork; the lower it is, the more likely the action is an
exit. Run the simulator with a large number of actions (e.g., -a
100) and vary the fork percentage from 0.1 to 0.9. What do you
think the resulting final process trees will look like as the percentage changes? Check your answer with -c.
    
    - A: The higher the value of parameter -f, the more number of nodes in resulting Process Tree, since it is a probability of another node is created versus probability of exiting the process.

3.  - Q: Now, switch the output by using the -t flag (e.g., run ./fork.py
-t). Given a set of process trees, can you tell which actions were
taken?

    - A: Let's consider inverted problem
   
        ```sh
        prompt> ./fork.py -s 11 -t           

        ARG seed 11
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree True
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False

                                Process Tree:
                                    a

        Action?
                                    a
                                    └── b
        Action?
                                    a
                                    └── b
                                        └── c
        Action?
                                    a
                                    └── b
                                        ├── c
                                        └── d
        Action?
                                    a
                                    └── b
                                        ├── c
                                        └── d
                                            └── e
        Action?
                                    a
                                    └── b
                                        ├── c
                                        ├── d
                                        │   └── e
                                        └── f
        ```
        Step 1: a forks b

        Step 2: b forks c
        
        Step 3: b forks d
        
        Step 4: d forks e
        
        Step 5: b forks f

4.  - Q: One interesting thing to note is what happens when a child exits;
what happens to its children in the process tree? To study this, let’s
create a specific example: ./fork.py -A a+b,b+c,c+d,c+e,c-.
This example has process ’a’ create ’b’, which in turn creates ’c’,
which then creates ’d’ and ’e’. However, then, ’c’ exits. What do
you think the process tree should like after the exit? What if you
use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.

    - A: After c exits, all of its successors become childs of a root process a. If flag -R is used, meaning reparenting, then, c's nearest childs becomes childs of c's predecessor and original structure of processes remains the same except missing of c.

        ```sh
        prompt> ./fork.py -A a+b,b+c,c+d,c+e,c- -c

        ARG seed -1
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list a+b,b+c,c+d,c+e,c-
        ARG show_tree False
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve True

                                Process Tree:
                                    a

        Action: a forks b
                                    a
                                    └── b
        Action: b forks c
                                    a
                                    └── b
                                        └── c
        Action: c forks d
                                    a
                                    └── b
                                        └── c
                                            └── d
        Action: c forks e
                                    a
                                    └── b
                                        └── c
                                            ├── d
                                            └── e
        Action: c EXITS
                                    a
                                    ├── b
                                    ├── d
                                    └── e
        ```

        ```sh
        prompt> ./fork.py -A a+b,b+c,c+d,c+e,c- -R -c

        ARG seed -1
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list a+b,b+c,c+d,c+e,c-
        ARG show_tree False
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent True
        ARG print_style fancy
        ARG solve True

                                Process Tree:
                                    a

        Action: a forks b
                                    a
                                    └── b
        Action: b forks c
                                    a
                                    └── b
                                        └── c
        Action: c forks d
                                    a
                                    └── b
                                        └── c
                                            └── d
        Action: c forks e
                                    a
                                    └── b
                                        └── c
                                            ├── d
                                            └── e
        Action: c EXITS
                                    a
                                    └── b
                                        ├── d
                                        └── e
        ```

5.  - Q: One last flag to explore is the -F flag, which skips intermediate
steps and only asks to fill in the final process tree. Run ./fork.py
-F and see if you can write down the final tree by looking at the
series of actions generated. Use different random seeds to try this a
few times.

    - A: Let's try few random seeds

        ```sh
        prompt> ./fork.py -s 10 -F

        ARG seed 10
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree False
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False

                                Process Tree:
                                    a

        Action: a forks b
        Action: a forks c
        Action: c EXITS
        Action: a forks d
        Action: a forks e

                                Final Process Tree?
        ```

        Final tree should look like this

        ```sh
        a
        ├── b
        ├── d
        └── e
        ```

        ```sh
        prompt> ./fork.py -s 11 -F   

        ARG seed 11
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree False
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False

                                Process Tree:
                                    a

        Action: a forks b
        Action: b forks c
        Action: b forks d
        Action: d forks e
        Action: b forks f

                        Final Process Tree?
        ```

        Final tree should look like this

        ```sh
        a
        └── b
            ├── c
            ├── d
            │   └── e
            └── f
        ```

6.  - Q: Finally, use both -t and -F together. This shows the final process
tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place?
In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.

    - A: If a number of forked nodes is equal to number of actions, the resulting set can be resolved uniquely. Toу explore the other cases, let's try few random seeds:

        ```sh
        prompt> ./fork.py -s 10 -t -F

        ARG seed 10
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree True
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False

                                Process Tree:
                                    a

        Action?
        Action?
        Action?
        Action?
        Action?

                                Final Process Tree:
                                    a
                                    ├── b
                                    ├── d
                                    └── e
        ```

        I can assume that set of actions was like this:
        
        ```sh
        Action: a forks b
        Action: b forks c
        Action: c EXITS
        Action: a forks d
        Action: a forks e
        ```

        I say assume because the order of action `c EXITS` may be different. Another option is a tree set from question #4: `a+b,b+c,c+d,c+e,c-`. It results with the same final process tree. To sum up, if there was at least one 'EXITS` action (i.e. number of actions is greater than number of forked nodes in a resulting set), there may be a problem to solve a situation in exactly single way.
        But there are cases when it's possible to resolve the action set:

        ```sh
        prompt> ./fork.py -s 0 -t -F

        ARG seed 0
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree True
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False

                                Process Tree:
                                    a

        Action?
        Action?
        Action?
        Action?
        Action?

                                Final Process Tree:
                                    a
                                    └── b
                                        └── d
                                            └── e
        ```

        The resulting set is:

        ```sh
        Action: a forks b
        Action: a forks c
        Action: c exits
        Action: b forks d
        Action: d forks e
        ```
