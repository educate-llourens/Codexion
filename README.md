*This project has been created as part of the 42 curriculum by leloren*

# Description

Codexion is a multithreaded C simulation (POSIX threads) of a dining-philosophers variant.

A number of coders sit in a circle with one USB dongle between each pair of neighbours. A coder needs **two** dongles to compile. After compiling, the coder puts both dongles back and then debugs, refactors, and tries to compile again. The simulation ends when every coder has compiled the required number of times, or as soon as one coder burns out (does not start a compile within `time_to_burnout` ms of the start of their previous compile, or of the simulation).

Two rules make it harder than the classic problem:

- **Dongle cooldown:** a released dongle cannot be taken again until `dongle_cooldown` ms have passed.
- **Scheduler:** when several coders want the same dongle, a scheduler decides who gets it, either `fifo` (longest wait first) or `edf` (Earliest Deadline First, the coder closest to burnout goes first).

Each coder runs in its own thread. One extra monitor thread watches for burnout and for the end of the simulation. Every state change is printed as `timestamp_in_ms coder_id action`.

# Instructions

## Build

```
make        # builds ./codexion
make re     # full rebuild (needed after changing a header)
```

The project is compiled with `-Wall -Wextra -Werror -pthread`.

## Usage

```
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

| Argument                      | Description                                                    |
|-------------------------------|----------------------------------------------------------------|
| number_of_coders              | Number of coders, and of dongles (1 to 200)                    |
| time_to_burnout               | Max ms between the start of two compiles before burnout        |
| time_to_compile               | Duration of a compile in ms                                    |
| time_to_debug                 | Duration of debugging in ms                                    |
| time_to_refactor              | Duration of refactoring in ms                                  |
| number_of_compiles_required   | Compiles each coder must complete for the simulation to end    |
| dongle_cooldown               | ms a dongle stays unavailable after being released             |
| scheduler                     | Exactly `fifo` or `edf`                                        |

All numeric arguments must be non-negative integers that fit in an `int`. The whole argument list may also be passed as one quoted string.

## Examples

```
./codexion 4 2000 100 100 100 3 5 edf       # everyone finishes, no burnout
./codexion 5 800 200 200 200 3 10 fifo      # tight timings, still finishes
./codexion 5 100 200 200 200 3 10 fifo      # burnout shorter than a compile
./codexion 1 800 200 200 200 3 10 fifo      # one dongle, one coder: burns out at 800
```

## Output

```
timestamp_in_ms coder_id has taken a dongle
timestamp_in_ms coder_id is compiling
timestamp_in_ms coder_id is debugging
timestamp_in_ms coder_id is refactoring
timestamp_in_ms coder_id burned out
```

No line is printed after `burned out`.

## Error codes

| Error code    | Int | Descritption                                                 |
|---------------|-----|--------------------------------------------------------------|
| ERROR         | -1  | Catch all error code                                         |
| MALLOC_FAIL   | -2  | Memory fails to malloc                                       |
| PARSING_ERROR | -3  | Bad input or failure to process information                  |
| THREAD_ERROR  | -4  | Failure to create or destroy threads and/or their conditions |
| MUTEX_ERROR   | -5  | Failure to create, lock or unlock a mutex                    |
| BURNOUT       | -9  | A coder burnt out                                            |
| OK            |  0  | Successfully executed with no errors                         |
<br>

## Testing

- **Memory:** `valgrind --leak-check=full --show-leak-kinds=all ./codexion 4 2000 100 100 100 3 5 edf`
- **Data races:** `valgrind --tool=helgrind ./codexion 4 2000 100 100 100 3 5 edf`

Valgrind slows the program down a lot, so use generous timings when running these tools. Tight timings can cause burnouts that have nothing to do with a bug.

# Resources

- [Markdown tables generator](https://www.tablesgenerator.com/markdown_tables)
- `man 3 pthread_create`, `pthread_join`, `pthread_mutex_lock`, `pthread_mutex_init`, `pthread_cond_wait`, `gettimeofday`
- E. G. Coffman, M. J. Elphick, A. Shoshani, *System Deadlocks* (1971), for the four conditions for deadlock
- E. W. Dijkstra, the dining philosophers problem
- Valgrind manual: Helgrind and DRD (thread error detectors)

**Use of AI:** Claude (Anthropic) was used as a tutor and reviewer during this project: to explain pthread concepts (mutexes, condition variables, `pthread_create`/`join`), to help read Valgrind/Helgrind and gdb output. I integrated, tested and debugged everything myself and can explain every part of the code.

# Blocking cases handled

## Deadlock prevention and Coffman's conditions

A deadlock needs all four conditions at once. The solution breaks two of them:

| Condition           | Status                                                                                                                                                   |
|---------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------|
| Mutual exclusion    | Kept. A dongle can only be used by one coder at a time (`being_used`).                                                                                   |
| Hold and wait       | **Broken.** A coder never holds one dongle while waiting for the other. It waits holding nothing, and claims both dongles in one step or neither.        |
| No preemption       | Kept. A coder keeps its dongles until it has finished compiling.                                                                                         |
| Circular wait       | **Broken.** When a coder needs both of its dongles, it locks the dongle mutexes in a fixed global order (lower address first), so no cycle can form.     |

The naive approach (lock left, then right) deadlocks when all coders grab their left dongle at the same moment, and it also starves coders: a coder holding one dongle blocks its neighbours without making progress.

## Starvation prevention and scheduling

Every dongle has its own small priority queue (a binary heap, capacity 2, since only the two neighbours who share a dongle can ever wait for it). Coders join the queues of both of their dongles before they wait. The order is decided in one function, `goes_before`:

- **fifo:** the lower arrival ticket wins. Tickets come from one shared counter, protected by its own mutex, so each request gets one unique number across both queues.
- **edf:** the lower deadline wins, where deadline = `time_last_compiled + time_to_burnout`.
- **Tie-break:** the lower coder id wins, so the order is strict and deterministic.

A coder may only take its dongles when it is at the top of **both** queues, and both dongles are free and past their cooldown. Because all queues use the same global order, the best waiting coder is always at the top of both of its queues, so nobody is passed over indefinitely.

## Cooldown handling

The cooldown belongs to the dongle, not to the coder. On release, a coder does not sleep. It records `time_available = now + dongle_cooldown` on each dongle and moves straight on to debugging. The next coder to take a dongle checks `now >= time_available`. This keeps the `is debugging` timestamp exactly `time_to_compile` after `is compiling`, and a dongle nobody wants never costs anything.

## Precise burnout detection

A separate monitor thread loops over all coders about every 1 ms. For each coder that has not yet finished, it checks whether `now >= time_last_compiled + time_to_burnout`. Polling every millisecond keeps detection well inside the 10 ms requirement, no matter what a coder is doing at the time (compiling, sleeping, or waiting for a dongle). Coders that have completed all their compiles are skipped, so they cannot be reported as burnt out afterwards.

Only the monitor declares a burnout, so there can never be two `burned out` lines.

## Log serialization

All output goes through `log_activity`, which holds `print_mutex`, checks the stop flag, and prints. When the monitor declares a burnout it takes `print_mutex`, sets `is_burnt`, and prints `burned out` before releasing the lock. Since both the flag and the message are handled under the same lock, no other line can appear after the burnout message, and lines from different threads never interleave.

## Single coder

With one coder there is only one dongle, so the coder can never get a second one. A dedicated routine handles this case: the coder takes the dongle, logs it, and waits until it burns out at `time_to_burnout`. The normal path is skipped, because locking the same dongle twice would block the thread forever.

## Start of the simulation

`event_start_time` is written once, before any thread is created, so every timestamp and every burnout clock shares the same reference. Coder threads then wait on a gate flag (`simulation_started`, protected by `gate_mutex`) so that all coders begin competing together.

# Thread synchronization mechanisms

## Primitives used

| Primitive                 | Where                      | What it protects                                                                  |
|---------------------------|----------------------------|-----------------------------------------------------------------------------------|
| `pthread_t`               | coders, monitor            | One thread per coder plus one monitor, all joined by `main` before cleanup        |
| `pthread_mutex_t` (dongle)| each `t_dongle`            | `being_used`, `time_available`, and the dongle's waiting queue                    |
| `pthread_mutex_t` (coder) | each `t_coder`             | `time_last_compiled` and `nbr_times_compiled`, written by the coder, read by the monitor |
| `print_mutex`             | whiteboard                 | Output, so that lines never interleave and nothing prints after burnout           |
| `burnt_mutex`             | whiteboard                 | The `is_burnt` stop flag                                                          |
| `gate_mutex`              | whiteboard                 | The `simulation_started` flag                                                     |
| `ticket_mutex`            | whiteboard                 | The shared arrival-ticket counter used by FIFO                                    |

Each dongle also carries a `pthread_cond_t`, which is initialised and destroyed together with the dongle. The current implementation waits by polling (a short `usleep`, holding no locks) instead of using the condition variable, see *What I would improve*.

## Lock order

Locks are always taken in the same order, so two threads can never wait on each other in a cycle:

1. Dongle mutexes: lower address first, always both held together and released together.
2. `print_mutex`, then `burnt_mutex` (used by both `log_activity` and the monitor).
3. `coder_mutex` and `ticket_mutex` are leaf locks: nothing else is ever locked while holding them.

## How race conditions are prevented

- **Claiming dongles:** the check ("first in both queues, both free, both past cooldown") and the claim (`being_used = TRUE`, leave both queues) happen while holding both dongle mutexes, so two coders can never claim the same dongle.
- **Coder state read by the monitor:** the monitor reads `time_last_compiled` and `nbr_times_compiled` while coders write them. Both sides go through helper functions that take the coder's own mutex. Helgrind reports no race on them.
- **Stop flag:** `is_burnt` is only written under `burnt_mutex` and only read through a helper that takes the same mutex. Waiting coders check it on every pass, so they notice a burnout within about 1 ms and return without holding any locks.
- **Start gate:** `simulation_started` is written and read under `gate_mutex`. The start time is written before the threads are created, so thread creation itself guarantees they see it.

## Communication between coders and the monitor

The monitor never talks to coders directly. It reads their shared state through the helper functions, and it ends the simulation by setting `is_burnt`. Coders, including those waiting for a dongle, check that flag, return, and are joined by `main`. After all threads have been joined, nothing is running and no mutex is held, so all mutexes can be destroyed and all memory freed safely.

# What I would improve

1. Return the actual error code and not just ERROR.
2. Check the return value of every lock and unlock through one small helper, instead of ignoring them.
3. Approach this project with TDD. 