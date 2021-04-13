# Timing

经常被问到关于计时的问题，因此想要仔细研究如何低延迟拿到时钟，精准计时的问题.

## linux clock_gettime
This function takes about 250ns on average to return
Don't get me wrong, this system call has many advantages: 
1. its relatively portable on Linux machines 
2. it is constant across multiple cores. 

However, if you want less latency for subsequent calls to the timer there are several other methods
## x86 rdstc
use CPU Time Stamp Counter (TSC).

1. In most modern processors, the cycles you're actually reading are from the bus, not the actual processor cycle ticks. So it's latency is about 20 ~ 50ns.
2. Realtime is about cpu instruction count and instruction clock time.That is frequency could influence timing. Turn off frequency scaling is good, but how to do it ?

when using a time stamp counter is that you are in fact taking a value from a single processor. What happens if the thread or process executing the time stamp instruction migrates to a different core.

To fix this problem the thread executing the time stamp instruction must be "pinned" to a single core. 

A good impl is : https://github.com/RaftLib/SystemClock