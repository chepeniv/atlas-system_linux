# concurrency v parallelism

concurrency is wherein multiple tasks start, run, and finish in overlapping time
without regard to order. parallelism is wherein multiple tasks run
simultaneously in a multi-core processor. understanding the distinction between
the two is crucial

## concurrency

this is applicable whenever dealing with two or more tasks. a concurrent
application is capable of executing two or more tasks virtually -- this is why
concurrency may also be referred to as _virtual parallelism_.

although tasks may seem like they are running simultaneously this may not be the
case. what concurrency does is take advantage of cpu time-slicing provided by
the OS.

## parallelism

this doesn't require multiple task to exist. it _physically_ runs parts of a
task or multiple tasks at the same time by taking advantage of multi-core
infrastructure of a cpu wherein each core is assigned a part.

here a task may be split into subtasks across multiple cpu cores and then
computed in parallel. each such subtask partially contributes to the complete
solution of an assignment. in joining these, we obtain the full solution.

## differences

parallelism efficiency is measured in _latency_: amount of time needed to
complete a task

concurrency efficiency is measured in _throughput_: number of tasks that can be
solved at a time

