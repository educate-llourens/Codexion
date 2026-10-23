*This project has been created as part of the 42 curriculum by leloren*

# Description


# Instructions
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

# Resources
[Markdown tables generator](https://www.tablesgenerator.com/markdown_tables)


# Blocking cases handled
*section describing all the concurrency issues addressed in your solution (e.g., deadlock prevention and Coffman’s conditions, starvation prevention, cooldown handling, precise burnout detection, and log serialization).*

# Thread synchronization mechanisms
*Section explaining the specific threading primitives used in your implementation (pthread_mutex_t thread_cond_t, custom event implementation) and how they coordinate access to shared resources (dongles, logging, monitor state). Include examples of how race conditions are prevented and how thread-safe communication is achieved between coders and the monitor*

# What I would improve
1. Return the actual error code and not just ERROR.