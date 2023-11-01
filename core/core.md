# iacOS core

The iacOS core regroups the basic building blocks of the OS



## Thread
A thread is an executing instance. The threads have their own stack and processor context.

## Scheduler
The scheduler will decide which thread is currently executing on the processor core. The decision will be made according to priority. 
The scheduler will always execute the highest priority thread that is ready.

## Event
Events are ways for a thread to wait on a specific situation. A thread can wait for an event and as soon as then event is signaled, all waiting 
threads are released.

## Delay
Delays are a wait for a thread to sleep for a certain ammount of time. 