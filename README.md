# TestInterpreter

A lightweight C++ expression interpreter — designed to parse and evaluate simple programs with ease.

##  Features

- **Lexical Analysis**: Tokenizes input using `lexer.h`/`lexer.cpp`.
- **Parsing**: Builds ASTs or direct parse structures via `parser.h`/`parser.cpp`.
- **Expression Evaluation**: Interprets expressions and statements (handled in `stmt.h`/`stmt.cpp` and `expr.h`).
- **Test Suite**: Validates functionality using `tests.cpp`, ensuring robust correctness.

##  Folder Structure

```
TestInterpreter/
├── expr.h
├── lexer.h / lexer.cpp
├── parser.h / parser.cpp
├── stmt.h / stmt.cpp
├── token.h
├── main.cpp      # Entry point
├── tests.cpp     # Self-contained tests
├── myprogram     # Example input or test file
└── .gitignore
```

##  Getting Started

1. **Clone the repository**  
   ```bash
   git clone https://github.com/luckyayush777/TestInterpreter.git
   cd TestInterpreter
   ```

2. **Build the project**  
   If you're using `g++`:
   ```bash
   g++ -std=c++17 main.cpp lexer.cpp parser.cpp stmt.cpp -o TestInterpreter
   ```

3. **Run the interpreter**  
   ```bash
   ./TestInterpreter myprogram
   ```

4. **Run tests**  
   ```bash
   ./TestInterpreter tests.cpp
   ```

##  Example Usage

- `myprogram`: A sample script to run through the interpreter.
- `tests.cpp`: Core test suite to validate parsing and interpretation logic.

##  Contributing

Feel free to open issues or submit pull requests with suggestions or improvements.

##  License

MIT License – feel free to build and adapt as you like
