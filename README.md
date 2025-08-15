# TestInterpreter

A modern C++17 interpreter for a small, dynamically typed, expression-oriented language.  
Inspired by *Crafting Interpreters* but reimplemented with **RAII**, `std::variant`, smart pointers, and idiomatic STL usage for memory safety and clarity.

## Features

### ✅ Implemented
- **Lexical Analysis** (`lexer.h` / `lexer.cpp`)
  - Tokenizes source into a stream of `Token` objects.
  - Supports identifiers, keywords, numbers, strings, operators, grouping, and blocks.
  - Recognizes reserved keywords (`if`, `else`, `while`, `fun`, `return`, `var`, `print`, etc.).
- **Parser** (`parser.h` / `parser.cpp`)
  - Recursive descent parser with correct operator precedence.
  - Handles:
    - Literals (number, string, `true`, `false`, `nil`)
    - Unary/binary operations (`-`, `+`, `*`, `/`, `!`, comparisons, equality)
    - Variable declarations & assignments
    - Blocks and nested scopes
    - Conditional statements (`if` / `else`)
    - Loops (`while`)
    - Function declarations and calls (with closures)
    - `return` statements
    - `print` statements
- **AST Evaluation** (`expr.*`, `stmt.*`)
  - Expression and statement execution with runtime type checks.
  - Supports first-class functions with lexical scoping.
- **Environments** (`environment.*`)
  - Lexical scoping via chained environments.
  - Variable definition, lookup, and reassignment.
- **REPL & File Execution** (`main.cpp`)
  - Interactive prompt for quick experimentation.
  - Script execution from file.

### 🚧 Planned
- Better error recovery (currently halts on first error).
- Grouping expression AST node.
- More built-in functions.
- Improved number formatting.

---

## Example

### Source
```lox
fun my_fun() {
  var a = "inner";
  print a;
}

var a = "outer";
my_fun();
print a;
```

### Output
```
Tokens:
Type: FUNCTION   Lexeme: 'fun'
...
true
outer
```

---

## Build Instructions

### Prerequisites
- **CMake** ≥ 3.10
- **C++17** compiler (GCC, Clang, or MSVC)

### Steps
```bash
git clone https://github.com/luckyayush777/TestInterpreter.git
cd TestInterpreter
mkdir build && cd build
cmake ..
make
```

---

## Running

### Interactive Mode (REPL)
```bash
./TestInterpreter
```

### Run from File
```bash
./TestInterpreter path/to/script.txt
```

---

## Project Structure
```
TestInterpreter/
├── CMakeLists.txt
├── include/
│   ├── callable.h
│   ├── environment.h
│   ├── expr.h
│   ├── function.h
│   ├── lexer.h
│   ├── parser.h
│   ├── stmt.h
│   ├── token.h
│   └── util.h
├── src/
│   ├── environment.cpp
│   ├── expr.cpp
│   ├── function.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   ├── parser.cpp
│   ├── stmt.cpp
│   └── util.cpp
├── test.txt
└── README.md
```

---

## License
MIT License — free to use, modify, and distribute.
