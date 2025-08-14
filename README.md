# TestInterpreter

A lightweight C++ interpreter for a small, expression-oriented language. 
This project is inspired by *Crafting Interpreters* but uses modern C++ features 
like `std::variant`, smart pointers, and RAII for safety and clarity.

## Features

### Implemented
- **Lexical Analysis** (`lexer.h` / `lexer.cpp`)
  - Tokenizes input source into a `Token` stream.
  - Supports identifiers, keywords, numbers, operators, and braces.
- **Parsing** (`parser.h` / `parser.cpp`)
  - Recursive descent parser with clear operator precedence.
  - Handles expressions, variable declarations, blocks, and `if`/`else` statements.
- **AST Evaluation** (`expr.h` / `expr.cpp`, `stmt.h`)
  - Expression nodes: literals, variables, assignments, unary, binary.
  - Statement nodes: expression statements, variable declarations, blocks, conditionals.
- **Environments / Scopes** (`environment.h` / `environment.cpp`)
  - Lexical scoping with nested environments.
  - Variable definition, lookup, and assignment.
- **REPL & File Execution** (`main.cpp`)
  - Interactive mode for quick experiments.
  - Script mode for running `.txt` or `.lox`-style files.

### Planned / Incomplete
- String literal parsing.
- `print` statement instead of hardcoded expression output.
- Grouping expression AST node.
- Error recovery (currently stops at first error).
- Better number formatting.
- Removal of unused `TokenType::NUMBER_LITERAL`.

## Example

### Source
```
var b = 1;
if (b > 5) {
  b = 99;
} else {
  b = -1;
}
b;
```

### Output
```
--- TOKENS ---
Type: VAR  Lexeme: 'var'
...
----------------
Result : -1
```

## Build Instructions

### Prerequisites
- CMake >= 3.10
- C++17 compatible compiler (GCC, Clang, MSVC)

### Steps
```bash
git clone https://github.com/luckyayush777/TestInterpreter.git
cd TestInterpreter
mkdir build && cd build
cmake ..
make
```

### Run
Interactive REPL:
```bash
./TestInterpreter
```

Run script file:
```bash
./TestInterpreter path/to/script.txt
```

## Project Structure
```
TestInterpreter/
├── CMakeLists.txt
├── include/
│   ├── environment.h
│   ├── expr.h
│   ├── lexer.h
│   ├── parser.h
│   ├── stmt.h
│   ├── token.h
│   └── util.h
├── src/
│   ├── environment.cpp
│   ├── expr.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   ├── parser.cpp
│   ├── stmt.cpp
│   └── util.cpp
├── test.txt
└── README.md
```

## License
MIT License — free to use, modify, and distribute.
