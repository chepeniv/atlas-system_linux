# Multithreaded Programming
# `POSIX` Thread Tutorial

it is imperative to carefully analyze the problem and design the solution
before multithreaded programming

## Threads

### analogy

one may think of sewing needles as the processors and the threads of a
program as the thread fiber

### definition

in order to formally define threads, we must understand the boundaries of where
a thread operates first

a computer program becomes a process when it is loaded from storage into
memory and begins execution

any process may be executed by a processor or a set of processors

a thread is a sequence of instructions within a program that may be executed
independently of other code

threads existing within the same process address space, share much of the
information

the stack, registers, and thread specific information cannot be replicated.
this information is necessary to allow threads to be scheduled and operate
independently of each other and the master thread.

explicit OS support is required to run multithreaded programs and they may use
differing mechanisms to implement MT support.

### terminology

- **lightweight process** (LWP, **kernel thread**) - in effect, a virtual CPU
whenever the number of LWPs is typically greater than number of CPUs in the
system. thread libraries communicate with LWPs to schedule threads
- **X-to-Y** - a model which maps kernel threads to cpu threads. this varies
from 1:1, X:1, and X:Y depending on the OS implementation and user-level thread
library in use. kernels typically use 1:1, user-level threading commonly use
X:1 as the underlying kernel doesn't have any knowledge of user level threads.
- **contention scope** - this is how threads compete for system resources
  such as scheduling
- **bound threads** - these have system-wide contention scope -- that is,
  they contend with other processes on the entire system
- **unbound threads** - these have process contention scope
- **thread-safe** - wherein the program protects shared data, possibly through
  mutual exclusion.
- **re-entrant** - is code which a program can execute concurrently on multiple
 threads
- **async-safe** - is a reentrant function that handles signals thereby
can be called from a signal handler

#### **concurrency vs parallelism**

these are not the same. parallelism means simultaneously executed code
(not strictly possible on uni-processors), while concurrency is
where many task can be ran in any order

### Amdahl's Law and the Pareto Principle

for the right applications, threads provide significant benefits. this must be
determined beforehand.

with the premise that a program is _strongly scaled_ (operates on fixed problem
size), the theoretic maximum improvement possible under parallelisation is
"limited by the fraction of time that the improvement is actually implemented"
-- in other words, the "speedup due to parallelization can be no larger than
the inverse of the portion of the program that is immutably sequential".  most
interesting problems tend to have limitations in the amount of parallelism that
can be thrown at them.

example: if 1/2 of a program is not parallelizable, then the maximum speed up
possible is 2x.

it is said that roughly, "90% of cycles are spent of on 10% of the code" and
this is where we must be focus on and optimize. this is the realm of code
profiling and analysis.

## Thread Design Pattern

different ways to use threads within a program exist. which to use depends on
what a program is intended to handle and in what context

### 1. thread pool (boss/worker)

one thread dispatches others to do work within a worker thread pool which
is preallocated before the master thread begins delegation. although
threads are lightweight, they still incur overhead when created

### 2. peer (workcrew)

this is similar to the thread pool model except there isn't really a master,
only peers

### 3. pipeline

similar to pipelining in a processor, each thread is part of a chain in a
processing factory. each thread operates on data processed by the previous
thread before handling it over to the next. carefully distribute work equally
and take extra precautions to ensure non-blocking behavior to prevent pipeline
"stalls"

## protecting shared resources

threads may operate on either disparate or overlapping data. some mechanism
defining a protocol for safe access must be put in place prevent
concurrent access to overlapping data. threads must be instructed to
block when other threads may be accessing the same resources.

### mutual exclusion (mutex)

this is a method of serializing access to shared resources -- this prevents
things like 'dirty reads' wherein a variable is being updated by one thread while
another thread reads its old value.

mutex allows a programmer to create a protocol for serializing
access to shared resources. in effect, it is a lock virtually attached to some
resource. if a thread must first obtain this lock before it can access or
modify that shared resource. once done, the thread then releases the
lock. this protocol must be enforced manually since there's nothing
preventing a programmer from implementing flawed serialization.

code between `mutex` lock and unlock calls is referred to as the **critical
section**, and minimizing the time spent within it allows for greater
concurrency, by reducing the amount of time other threads wait for a freed
lock.

### mutex types

-- **recursive** : permits the thread holding the lock to acquire it again
within a recursive algorithm
-- **queuing** : allows for _fairness_ in lock acquisition via FIFO ordering
of request. these `mutex`es may be slower due to the overhead needed and
possibly waking of sleeping threads
-- **reader/writer** : allows multiple readers to acquire a lock
simultaneously. a writer request will block until all readers have freed their
lock. this may lead to "writer starvation"
-- **scoped** : "resource allocation is initialization" (RAII) style semantics
regarding lock acquisition and unlocking

POSIX pthreads allows recursive and reader/writer style locks


### mutex pitfalls

a deadlock can occur if multiple threads have stopped execution are
permanently spinning. to prevent this ensure threads access locks in a
predetermined order (preservation of lock ordering).

a race condition is where non-deterministic behavior results from threads
accessing shared resources without following a predefined synchronization
scheme for serializing access. this may result in erroneous outcomes leading
to failure or inconsistent behavior. race conditions are notoriously
difficult to debug. outside library calls are common culprits as well. most man
pages contain information about the thread safety of a particular
function as well as alternatives.

contention for a mutex can lead to **priority inversion** wherein a higher
priority thread waits behind a lower priority thread that's holding a lock it
desires. this may be reduced or entirely eliminated by limiting the
number of shared mutexes between threads of differing priority.

### atomic operations

this approach allows for concurrent algorithms and access to certain shared
data types without the use of mutexes. given the adequate compiler and
system support, a variable can be modified within a threaded context without
having to go through a locking protocol. many atomic calls are specific to
their host system and thereby non-portable.

lock-free algorithms can provide highly concurrent and scalable
operations. however these may be more complex than their lock-based
counterparts, potentially incurring substantial overhead which may induce
unwanted cache effects along with other issues

## thread synchronization primitives

other mechanisms exist for both coordinating access to shared resources and for
synchronizing threads as well.

### join

a thread join is protocol that allows relevant threads to be be collected at a
logical synchronization point. for fork-join parallelism, threads are
spawned to handle parallel task and then join back up with the master thread
after completion. a thread which executes a join terminates execution of its
thread function.

### condition variables

these allow threads to synchronize to a value of a shared resource. this is
in effect a notification system between threads.

here one may use a broadcast mechanism to `signal` to all threads waiting
the condition variable to wake up.

because of spurious wakeups, waiting on condition variables should take place
within a loop and not in a simple `if` statement. it is not guaranteed that
if a thread wakes up it is the result of a `signal` or broadcast call

### barriers

this method synchronizes threads at a select point by having all participating
pause at the barrier until all threads have called the barrier function.
this blocks all participating threads until the slowest thread reaches
the barrier call

### spinlocks

these are locks that _spin_ on mutexes. this refers to continuously
polling until a condition has been satisfied. here if a thread cannot
obtain a mutex it will keep polling until it's freed. this keeps the thread
active preventing sleep-wait. this setup can perform better in certain cases
than the typical block-sleep-wait approach. mutexes which are heavily contended
are very poor candidates for spinlocks.

this should be avoided on uniprocessor context.

### semaphores

this kind of synchronization primitive comes in two forms: binary and
counting. binary semaphores act much like simple mutexe. counting
semaphores can behave as recursive mutexes and can be initialized to
an arbitrary value dependent on how many resources are available for the
shared asset. many threads may obtain the lock simultaneously until the limit
is reached -- this is known as the **lock depth**

this is common in multiprocessor programming, typically used as a sync
primitive between processes

## POSIX `pthreads`

this implementation can be found in most modern POSIX-compliant OS

### preliminaries

1. add `#include <pthread.h>`
2. with `gcc` specify `-pthread`
3. some compilers may require defining
   `_POSIX_PTHREAD_SEMANTICS` for certain function calls

### creating `pthreads`

```c
int pthread_create(
	pthread_t *thread, // a thread object containing pthread_id
	pthread_attr_t *attr, // attributes to apply to this thread, may
						  // be NULL to indicate default attributes
	void *(*start_routine)(void *), // function executed by this thread
	void *arg); // arguments to pass to start_routine
```

two more important thread functions

```c
void pthread_exit(void *value_ptr);
int pthread_join(pthread_t thread, void **value_ptr);
```
`pthread_exit()` terminates the thread and provides `*value_ptr`
available for any `pthread_join()`

`pthread_join()` suspends the calling thread to wait for successful
termination of the thread specified by the first argument along with an
optional `*value_tr` data passed from the terminating threads call to
`pthread_exit()`

- ensure you check the return of all important functions
- defaults vary depending on system and `pthread` implementation
- keeping separate `pthread_join()` from `pthread_create()` avoids waiting on
  created threads
- it is good practice to explicitly call `pthread_exit()` at the end of a
thread function, although not mandated, in order to return some value back
to the caller (via `pthread_join`)

### `pthreads` attributes

at the time of creation, threads may be assigned various attributes. this
is determined by the second argument to `pthread_create()`

a `pthread_attr_t` type variable must first be passed through
```c
int pthread_attr_init(pthread_attr_t *attr);
```

some of the attributes that can be setup:
```c
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
int pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched);
int pthread_attr_setschedparam( pthread_attr_t *attr,
								const struct sched_param *param);
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
int pthread_attr_setscope(pthread_attr_t *attr, int contentionscope);
int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stackaddr);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
```

attributes can then be retrieved via complimentary `get` functions.

### `pthread` mutexes

pthread mutexes are created with
```c
int pthread_mutex_init(pthread_mutex_t *mutex,
					   const pthread_mutexattr_t *mutexattr0;
```
attributes for the mutex are given through the second parameter, which
if NULL specifies default attributes.

alternatively, a macro may be use to initialize a mutex
```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
```

mutex locking and unlocking is achieved with:
```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
the difference between `_lock` and `_trylock` is that the former blocks
while the later is _non-blocking_ -- meaning that it returns immediately
regardless of success. it is imperative to check the return of `_trylock` to
determine acquisition

### `pthread` condition variables

creating `pthread` condition variables:
```c
int pthread_cond_init(pthread_cond_t     *cond,
					  pthread_condattr_t *cond_attr);

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```

as in mutex initialization, non-default attributes are given through the
second parameter. to keep the defaults pass NULL as the second param or use the
init macro instead.

threads act upon condition variables in three ways:
```c
int pthread_cond_wait(pthread_cond_t  *cond,
					  pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
```

the `_wait` function puts the current thread to sleep, and requires a mutex
of the associated shared resource.

`_signal` signals one thread to wakeup out of the sleeping thread set.

`_broadcast` signals to all threads to waiting on the condition
variable to wakeup

### `pthread` barrier

`pthreads` can participate in a barrier to synchronize on some point in
time. before a barrier can be called, a `pthread_barrier_t` object must be
initialized.
```c
int pthread_barrier_init(pthread_barrier_t *barrier,
						 pthread_barrierattr_t *barrier_attr,
						 unsigned int count);

pthread_barrier_t barrier = PTHREAD_BARRIER_INITIALIZER(count);
```

the `count` parameter defines the number of threads that must join the barrier
to complete and unblock all threads waiting it

within thread code:
```c
int pthread_barrier_wait(pthread_barrier_t *barrier);
```
once `count` number of threads have called this function then the barrier
condition is met and all threads are unblocked and continue

### miscellaneous

- check all return values of important `pthread` functions
```c
pthread_kill();  // can be used to deliver signals to specific threads
pthread_self();  // returns a handle on the calling thread
pthread_equal(); // checks equality between two thread ids
pthread_once();  // ensures an initializing function within a thread only runs
				 //once
```
- consult the `pthreads` man pages for more useful functions

## performance considerations

when done properly and within the right context, performance gains from using
threads can be substantial.

### potential bottlenecks

- **lock granularity** - the more fine grained locks are, the
more concurrency can be extracted, but at the cost of more overhead and
potential deadlocks
- **lock ordering** - ensure and enforce a predefined lock access order
- **lock frequency** - reducing the frequency of locks as well as at
unnecessary occasions is crucial for fully exploiting concurrency and reducing
synchronization overhead
- **critical sections** - minimize the critical sections of your codebase
- **worker thread pool** - in the manager/personnel thread model preallocate
  all needed threads instead of creating threads on demand
- **contention scope** - here only experimentation can determine if
threads perform better when they are in contention with all system processes
or when individually scheduled by the thread library ?
- **scheduling class** - changing the thread scheduling class from FIFO to
Round Robin (RR) may give better response times, yet this may still be
undesired
- **thread count** - only experimentation here can determine at what point
does performance diminish due to too many threads

### multiprocess and shared memory

to perform cross-process synchronization, one would use some form of IPC:
pipes, semaphores, message queues, or shared memory. herein, shared memory is
typically the fastest (excluding doors). when dealing with cross process
resource management, IPC, and synchronization, you can use `mmap()` and
`shm_open()` semantics.

### `OpenMP`

this is a portable interface for implementing fork-join parallelism on
shared memory multiprocessor machines.

### `MPI`

the de-facto standard for distributed memory parallel processing is the Message
Passing Interface. data can be passed around among distinct computing machines
with support for vectored i/o, synchronization, and collectives

programs exist which are both multithreaded and contain MPI calls
