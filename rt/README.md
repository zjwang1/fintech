# Pthread Priority and Scheduling

## Description
Scheduler policy and priority is used to determine which thread will run when a choice must be made between two or more runnable threads.

If your high priority thread blocks in read(), then it is not eligible to run, and a lower priority thread that is runnable will get a chance to run instead. What the priority means is that even all of the available CPU cores are running lower priority threads at the moment when data arrives from the network for the higher priority thread, a lower priority thread will be immediately pre-empted so that the higher priority thread can run.

If you want to see the effect of priority, have a lower-priority thread do lots of work so that it is almost always using the CPU: your higher-priority thread should still respond immediately to network input.

(But if you do this, either use a non-realtime priority level for the lower-priority threads, or make sure you have a shell open that is running at an elevated realtime priority, so that the lower-priority thread doesn't block your shell from running when you need it).

## demo usage
```bash
./build.sh
sudo ./demo
```