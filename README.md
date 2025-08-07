# TestInterpreter

A lightweight C++ expression interpreter — designed to parse and evaluate simple programs with ease, now with a clean CMake-based build system and project structure.

## Features

- **Lexical Analysis**: Tokenizes input using `lexer.h` / `lexer.cpp`.
- **Parsing**: Builds ASTs and supports statements via `parser.h` / `parser.cpp`.
- **Expression Evaluation**: Evaluates expressions and executes statements (`expr.h`, `stmt.h`, and `stmt.cpp`).
- **Block Statements**: Supports `{ ... }` with nested statements.
- **Test Support**: Add test files with their own `main()` functions.
- **CMake Build System**: Simplifies compilation across platforms.

## Folder Structure

```
TestInterpreter/
├── CMakeLists.txt
├── include/
│   ├── expr.h
│   ├── lexer.h
│   ├── parser.h
│   ├── stmt.h
│   └── token.h
├── src/
│   ├── main.cpp       # Entry point for interpreter
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── stmt.cpp
│   ├── expr.cpp
│   └── tests.cpp      # Optional: Test file (exclude or isolate to avoid duplicate 'main')
├── build/             # Auto-generated build folder
└── .gitignore
```

## Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/luckyayush777/TestInterpreter.git
   cd TestInterpreter
   ```

2. **Build the project with CMake**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the interpreter**
   ```bash
   ./TestInterpreter
   ```

4. **Testing**
   - If `tests.cpp` has a `main()`, create a separate CMake target for it.
   - Or temporarily exclude it when building the main interpreter.

## Example Input

```
{ 1 + 2; 3 * (4 + 5); }
```
Produces:
```
Result : 3
Result : 27
```

## Contributing

Feel free to open issues or submit pull requests with suggestions or improvements.

## License

MIT License – feel free to build and adapt as you like.