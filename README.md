# Threads

## CPU core calculation

I used the sysconf function from the unistd library included in C.

## Time

Using the time function we tracked the time taken for varying amounts of Threshold and Number of Threads

| Number of Threads | Threshold | User Time | System Time |
| ----------------- | --------- | --------- | ----------- |
| 1                 | 1         | 0m0.575s  | 0m0.004s    |
| 1                 | 10        | 0m0.433s  | 0m0.003s    |
| 1                 | 100       | 0m0.437s  | 0m0.004s    |
| 1                 | 1000      | 0m0.421s  | 0m0.010s    |
| 10                | 1         | 0m2.372s  | 0m9.256s    |
| 10                | 10        | 0m1.962s  | 0m7.475s    |
| 10                | 100       | 0m1.880s  | 0m6.672s    |
| 10                | 1000      | 0m0.575s  | 0m0.004s    |
| 100               | 1         | 0m2.404s  | 0m12.401s   |
| 100               | 10        | 0m1.793s  | 0m7.988s    |
| 100               | 100       | 0m1.737s  | 0m7.137s    |
| 100               | 1000      | 0m1.764s  | 0m7.379s    |
| 1000              | 1         | 0m2.738s  | 0m20.026s   |
| 1000              | 10        | 0m1.916s  | 0m10.241s   |
| 1000              | 100       | 0m1.845s  | 0m6.936s    |
| 1000              | 1000      | 0m1.844s  | 0m7.060s    |

## Constant Number of Threads

![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME.png)![TIME-1](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-2.png)

![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-1.png)![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-3.png)



## Constant Threshold

![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-4.png)![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-5.png)

![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-6.png)![TIME](/Users/hideodaikoku/Documents/Spring 2019/Operating Systems/Threads/Images/TIME-7.png)

As we can see the optimum performance is achieved with 1 thread and a threshold of 10



