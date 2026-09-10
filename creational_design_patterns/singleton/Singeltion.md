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
- Raw pointer starts empty: `static logger *m_instance = nullptr;`.
- `getInstance()` allocates it with `new logger{}` on the first call.
- The constructor registers `std::atexit([] { delete m_instance; });`.
- At normal program exit, `delete` calls `~logger()` and closes the log file.
- The commented `std::unique_ptr<logger>` approach is an RAII alternative;
  then manual `delete` is not needed.
- This raw-pointer check is still not thread-safe: two threads can both see
  `nullptr` and create two objects.

## Lazy singleton interview points

- **Why initialize the raw pointer to `nullptr`?** It means “no instance yet”.
- **Why use a non-capturing lambda with `atexit`?** It converts to the
  function pointer required by `std::atexit`.
- **Why is `atexit` needed here?** A `new`-allocated singleton is not deleted
  automatically when `main()` returns.
- **What does cleanup do?** `delete m_instance` calls the logger destructor,
  which calls `fclose()`.
- **What is the safer ownership choice?** `std::unique_ptr`, because it owns
  deletion through RAII.
- **Is this implementation thread-safe?** No. Lock or use a C++11
  function-local static before allowing concurrent `getInstance()` calls.

## Double-checked locking

- Current code in `Solution-2 (lazy instance)/logger_singleton.cpp`:

```cpp
if (m_instance == nullptr) { // read without mtx
  mtx.lock();
  if (m_instance == nullptr)
    m_instance = new logger{}; // write while mtx is held
  mtx.unlock();
}
```

- **Issue:** another thread can read `m_instance` while this code writes it.
  That is a data race; it can see a non-null pointer before construction is
  fully visible.
- **Preferred resolution:** use the **Meyers Singleton**: a C++11
  function-local static.

  ```cpp
  logger &logger::getInstance() {
    static logger instance;
    return instance;
  }
  ```

- The C++ standard makes concurrent callers wait until local-static
  initialization completes: [static local initialization reference](https://eel.is/c++draft/stmt.dcl#3).
- Prefer this over `std::call_once` here: it is less code, has no raw pointer,
  needs no `atexit` cleanup, and destroys the logger automatically.
- It needs no manual `delete` or `atexit` cleanup: its destructor runs
  automatically at normal program exit, after `main()` returns.

### Alternative: `std::call_once` (Solution-3)

From `Solution-3 (lazy instance)/logger_singleton.cpp`:

```cpp
logger *logger::m_instance = nullptr;
std::once_flag flag;

logger &logger::getInstance() {
  std::call_once(flag, []() { m_instance = new logger{}; });
  return *m_instance;
}
```

- `std::call_once` lets exactly one thread allocate `m_instance` and safely
  publishes it to the other threads.
- `Solution-3` currently has no cleanup. Because it uses `new`, its destructor
  does not run when `main()` returns; the OS reclaims memory, but does not call
  `~logger()` or `fclose()`.
- Add this in the constructor to run the destructor at normal program exit:

  ```cpp
  std::atexit([] { delete m_instance; });
  ```

- A `std::unique_ptr` also provides automatic ownership, but the Meyers
  Singleton is the smallest solution for this logger.
- Reference: [C++ `std::call_once`](https://eel.is/c++draft/thread.once.callonce).

## Meyers Singleton vs `std::call_once`

| Topic | Meyers Singleton | `std::call_once` + raw pointer |
| --- | --- | --- |
| Creation | Function-local `static logger instance` | `new logger{}` in a once callback |
| Thread safety | C++11 one-time initialization | `std::call_once` runs one callback |
| Cleanup | Destructor runs automatically at normal exit | Needs `delete`/`atexit` or smart-pointer ownership |
| Use here | Preferred: smallest solution | Use when a local static cannot work |

## CRTP Singleton

- Directory: `signleton_using_crtp_idom/`.
- Put the shared Meyers-style `getInstance()` in `BaseSingleton<T>`.
- Derive the concrete type: `class logger : public BaseSingleton<logger>`.
- Keep the derived constructor private and make `BaseSingleton<logger>` a
  friend, so only the base can create `logger`.
- Delete the derived copy constructor and assignment operator.

```cpp
template <typename T>
class BaseSingleton {
protected:
  BaseSingleton() = default;

public:
  static T &getInstance() {
    static T instance;
    return instance;
  }
};

class logger : public BaseSingleton<logger> {
  friend class BaseSingleton<logger>;
  logger();
};
```

- Use CRTP when several classes need the same singleton implementation.
- For one class, a direct Meyers Singleton is simpler.

## View the log file

```sh
cat 'Solution-2 (eager instance)/dummy_log.txt'
cat 'Solution-2 (lazy instance)/dummy_log.txt'
```

- `dummy_log.txt` contains the messages written during the most recent run.
