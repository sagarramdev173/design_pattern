# Singleton

- Creational pattern: one class instance, accessed globally.

## Checklist

- Make the default constructor private.
- Make the copy constructor private or delete it.
- Make the copy assignment operator private or delete it.
- Store one static instance in the class.
- Provide a static `getInstance()` method that returns that instance.

## Instance creation

- **Eager instance:** create the singleton before `main()` starts. Simple and
  thread-safe during initialization.

  ```cpp
  static logger m_instance;
  logger &logger::getInstance() { return m_instance; }
  ```

- **Lazy instance:** create the singleton on the first `getInstance()` call.
  In C++11 and later, a function-local static is initialized safely once.

  ```cpp
  logger &logger::getInstance() {
    static logger instance;
    return instance;
  }
  ```

## Logger problem

- `problem/` creates one `logger` in each of three threads.
- Every logger opens the same `dummy_log.txt` file.
- Opening with `"w+"` truncates earlier logs.
- Multiple `FILE *` streams and thread scheduling make output unreliable.
- Reading an uninitialized `m_logFileStream` is undefined behavior and can
  segfault.

## Solution-1

- `Solution-1/` has one private static `logger` instance.
- `getInstance()` returns that shared instance.
- Only one logger opens and owns the log file.
- This fixes repeated file creation/truncation.
- Shared `tag` and file access are still not thread-safe.
- Solution-2 will add synchronization with a mutex.

## Solution-2: eager instance

- Directory: `Solution-2 (eager instance)/`.
- `static logger m_instace;` is created before `main()`.
- `getInstance()` returns that already-created object.
- Its destructor runs automatically at program exit.

## Solution-2: lazy instance

- Directory: `Solution-2 (lazy instance)/`.
- `static logger *m_instace = nullptr;` starts empty.
- `getInstance()` creates it with `new logger{}` on the first call.
- The current code never calls `delete`, so the destructor is not called.
- Register cleanup with `std::atexit()` to delete the lazy instance at exit.
- The lazy creation check also needs synchronization before multiple threads
  call `getInstance()`.

## View the log file

```sh
cat 'Solution-2 (eager instance)/dummy_log.txt'
cat 'Solution-2 (lazy instance)/dummy_log.txt'
```

- `dummy_log.txt` contains the messages written during the most recent run.
