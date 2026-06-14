# rawlogger

A minimalistic, thread-safe, modular, C99 logging library designed with best open-source practices. Version 1.0.0.

## Features
- **Thread-Safety:** Output is protected against concurrent multi-thread accesses.
- **Multiple Sinks:** Add customizable destinations for logs. Includes `Console Sink` (with colored outputs) and `File Sink` out of the box.
- **Namespacing:** Adheres to standard C conventions using the `rawlog_` prefix to prevent collisions.
- **Time and Location:** Emits timestamps, source files, and lines.

## How to Build

Using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Example

After building:

```bash
./rawlogger_example
```

This will print colored logs to your terminal and also generate an `app.log` file in the execution directory.

## Integrating

Link against the static library `librawlogger.a` and include the header files in your target. See `CMakeLists.txt` for integration guidance.
