# Multithreading in C

within a process, a thread can be thought of as a single stream of execution.
because the threads posses some properties of processes, they are sometimes
referred to as "lightweight processes". within a process, threads are NOT
independent from each other. amongst themselves they share their code sections,
data section, and OS resources such as open files and signals. they however keep
their own program counter, register set, and stack space separate.

multithreading is a programming technique wherein a process is divided in to
multiple smaller units known as threads that run simultaneously.

in `C` the POSIX `pthreads` library is used to implement this

# Creating a Thread

```c
pthreadS_create(
	thread,  // pointer to a pthread_t wherein the thread ID is stored
	attr,    // pointer to a thread attributes object which defines a threads
			 // properties. NULL specifies defaults
	routine, // pointer to a function that the thread will execute. must return
			 // `void *` and accept a `void *` argument
	args     // the single argument passed to the `routine` function. NULL
			 // specifies no arguments. by passing a `struct` or a pointer, one
			 // may pass multiple arguments
);
```

# Waiting for a Thread to Finish

the possibility that a main thread ends before the execution of it's sub-threads
do, may lead to unexpected behavior. therefore, there exist a function to wait
on particular threads

`pthread_join()` allows one thread to wait for the termination of another. this
synchronizes execution

# Explicitly Terminate Thread

`pthread_exit()` allows a thread to terminate its own execution explicitly. it
can optionally return a value to any other threads waiting on it.

# Requesting Cancellation of a Thread

`pthread_cancel()` sends a cancellation request to a target thread, but the
actual termination depends on whether the thread is in a _cancellable_ state if
handles cancellation.

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* myThreadFunc(void* arg) {
	while(1) {
		printf("Thread is running...\n");
		sleep(1);
	}
	return NULL;
}

int main() {
	pthread_t thread;

	pthread_create(&thread, NULL, myThreadFunc, NULL);
	sleep(5);
	pthread_cancel(thread);     //Requesting to cancel the thread after 5 seconds.
	pthread_join(thread, NULL); // Wait for the thread to terminate
	printf("Main thread finished.\n");

	return 0;
}
```

# Getting a Thread's ID

`pthread_self()` returns the thread ID of the calling thread.

```c
#include <pthread.h>
#include <stdio.h>

void* foo(void* arg) {
	pthread_t thisThread = pthread_self(); // Get current thread ID
	printf("Current thread ID: %lu\n", (unsigned long)thisThread);
	return NULL;
}

int main() {pthread_t thread1;
	pthread_create(&thread1, NULL, foo, NULL);
	pthread_join(thread1, NULL);
	return 0;
}
```

# Common Issues In Multithreading

although multithreading improves performance by running multiple task
simultaneously, several pitfalls arise that need to be handled properly to
ensure desirable behavior.

## Race Conditions

this occurs when multiple threads attempt to access the same resource
simultaneously and behavior depends on the order in which threads are executed.
this results in unpredictable behavior, generating different results each
execution.

## Deadlocks

this occurs when multiple threads are perpetually blocked waiting on each other
to release a mutually desired resources.

this typically arises when separate threads acquire initial resources and then
request more resources midway through their execution, leading to a _cycle of
dependencies_

## Starvation

this occurs whenever a thread is denied access to its desired resources for an
indefinite amount of time. commonly this occurs with biased priority-based
scheduling algorithms, such as when a low priority threads is left waiting on
continuously available higher priority threads

# Thread Synchronization

are a class of techniques used to ensure multiple threads can work with shared
resources without causing issues. these control how threads interact with shared
resources and ensure critical sections are executed in a controlled manner.

## Mutex-Based Synchronization

this is the most basic mechanism. it ensures only one thread at a time can
access a shared resource, thereby preventing race conditions.

## Semaphores

this is a signaling mechanism that controls access to a shared resource by using
a counter. it may be either binary or counting semaphore, allowing multiple
threads to access a resource simultaneously up to a specified limit.

## Conditional Variables

these allow threads to wait on certain conditions to be met before proceeding.
these are always used along with a `mutex` lock. when a thread waits on a
condition it releases its `mutex` and not until notified by another thread does
it regain it.

## Barriers

with these threads can be synchronized at specific locations in execution. they
block any threads reaching a specified point until all threads in a group have
reach it. only then will they proceed forward.

## Read-Write Locks

these kind of locks allow multiple threads to read a shared resource
simultaneously, while ensuring that only one thread, at a time, can write to the
resource. this improves performance when more readers than writers exist

# Utility of Multithreading

multithreading enhances cpu utilization, reduces idle time, and make programs
faster and more responsive.

## Advantages

- **performance improvement**
- **cpu utilization**
- **responsiveness**
- **efficient resource sharing**
- **scalability**

## Limitations

- **programming complexity**
- **concurrency pitfalls**
- **increased overhead and thread management**
- **increased risk of bugs**
