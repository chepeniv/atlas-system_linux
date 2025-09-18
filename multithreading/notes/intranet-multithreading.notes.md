# multithreading

# process vs. thread

a process can have subprocesses. threads belong to a process. threads of the
same process run in the same shared memory space, while processes run in
separate memory spaces.

# utility of threads

parallelism is a great way to separate logical components

the two most prominent cases for using threads are time sensitivity and time
consuming

## time sensitivity

a task that is time sensitive cannot afford to wait on another task whether or
not it is time consuming

## time consuming

any task that takes any considerable amount of time can be run in a separate
thread or a pool of threads

this all depends on whether or not a series of steps can be run independently of
each other without effecting the final result

# limitations and Amdahl's law

there's a limitation to the number of threads a computer can handle before
efficiency begins to drop. too many threads can be just as hindering as too few

# shared resources and mutual exclusion

threads within a process share the same address space -- that is they have
access to the same data. if data is modifiable then there needs to be a
mechanism in place to allow safe and reliable access to it

## mutual exclusion

`mutex` is a method for serializing access to shared resources. basically a lock
attached to a resource. whenever a thread wants to gain access or modify a
resources it must first obtain the lock (`mutex`). once this is so, operations
on the resource are guaranteed to behave as expected since no other thread is
allowed access. once done, the `mutex` must be released to permit usage by
another thread

### deadlock limitation

this is common problem occurring whenever a program stops execution or hangs
indefinitely due to _conflicting_ `mutex` locking. to illustrate, one thread `T`
obtains lock `l` and another thread `Q` obtains lock `m` but then they each want
access to each others locks without first releasing the locks they already
posses -- that is `T` waits on `m` and `Q` waits on `l`, instant deadlock.
another ways is simply if threads do not unlock their `mutex`s properly

a preventive measure is to ensure threads acquire locks in a predetermined order
(lock order preservation)

### race condition limitation

this is a result of poorly implemented parallel execution where at some point
two or more threads simultaneously aim to access the same resource. which one
will is impossible to determine. these are particularly hard to debug as they
are quite specific to _your_ case. to best avoid these, define some sort of
sequential protocol
