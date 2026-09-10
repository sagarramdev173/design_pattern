# Singleton: Pros and Cons

## When to use Singleton

- Exactly one shared object is required, such as application configuration or
  a process-wide logger.
- Multiple objects would conflict over one resource, such as one log file or
  one hardware connection.
- The shared object has clear lifetime and ownership for the whole program.
- Prefer dependency injection instead when unit tests need to replace it with
  a mock or fake.

## Meyers Singleton

```cpp
static logger &getInstance() {
  static logger instance;
  return instance;
}
```

Pros:

- Smallest implementation.
- Lazy creation: object is made on first use.
- Thread-safe initialization in C++11 and later.
- Destructor runs automatically at normal program exit.

Cons:

- Global shared state makes unit tests and mocking harder.
- Destruction order can be a problem if other static objects use it during exit.

## Lazy Singleton with Raw Pointer

```cpp
static logger *m_instance = nullptr;
```

Pros:

- Object is created only when needed.
- Can control exactly when creation and deletion happen.

Cons:

- `if (m_instance == nullptr)` is unsafe with multiple threads.
- Needs `delete` or `std::atexit`; otherwise destructor does not run.
- Easy to create leaks, double deletion, or double-checked-locking bugs.

## Lazy Singleton with `std::unique_ptr`

```cpp
static std::unique_ptr<logger> m_instance;
```

Pros:

- Smart pointer owns deletion; no manual `delete`.
- Destructor runs when the owning `unique_ptr` is destroyed.
- Safer lifetime management than a raw pointer.

Cons:

- It does not make initialization thread-safe by itself.
- Still use `std::call_once` or a mutex for concurrent first access.
- More code than a Meyers Singleton.

## Monostate (Borg)

```cpp
class logger {
  static std::string tag;
};
```

Pros:

- Many `logger` objects can be created, but they share one static state.
- Easier to pass an object than calling a global `getInstance()` everywhere.

Cons:

- It is still global shared state, so tests can affect each other.
- Object identity is misleading: different objects hold the same data.
- Shared state needs synchronization when multiple threads modify it.

## Monolithic Design

Pros:

- Simple to start: one application and one deployment unit.
- Direct function calls; no network communication between modules.
- Easier to debug for a small project.

Cons:

- Logger implementation, routing, and application code can become tightly
  coupled.
- A change in one area can require rebuilding and redeploying everything.
- Harder to scale or test parts independently as the project grows.

## Quick choice

| Need | Prefer |
| --- | --- |
| Normal C++11+ singleton | Meyers Singleton |
| Custom creation/lifetime control | `std::unique_ptr` with `std::call_once` |
| Learning pointer/lifetime pitfalls | Raw lazy pointer |
| Multiple objects with shared state | Monostate |
| Small single deployment | Monolithic design |
