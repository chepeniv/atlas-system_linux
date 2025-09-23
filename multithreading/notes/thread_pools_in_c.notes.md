# thread pools in C

## why thread pooling ?

creating threads can be quite expensive. if each thread is going to be doing the
same thing, reusing them is a good idea. since threads are so heavy, creating
and destroying them takes time away from one's aims.

thread pools keep a system from becoming overloaded. they set a limit to the
number of threads allowed. tasks are enqueued and only handled when a thread
becomes available.

## requirements

a thread pool keeps a set number of threads running and waiting to handle tasks.
they may be designed to scale with the amount of work needed. as a
rule-of-thumb, set the limit of threads to be number of total cores across all
processors plus one.

### object data

## implementation

### work data object

### worker function

### creating and destroying a pool

### adding to the work queue

### waiting on process completion

## testing

## further exploration
