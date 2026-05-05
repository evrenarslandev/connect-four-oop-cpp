# Connect Four - Object Oriented C++ Implementation

A robust implementation of the classic Connect Four game using advanced **C++ Object-Oriented Programming (OOP)** principles. The game features various modes (Plus, Diag, Undo) and supports User vs. User and User vs. PC gameplay.

## 🏗️ Core OOP Features
- **Abstract Base Classes:** Utilizes `ConnectFourAbstract` as a blueprint for different game variants, ensuring a modular and scalable architecture.
- **Inheritance & Polymorphism:** Specific game modes like `ConnectFourPlus`, `ConnectFourDiag`, and `ConnectFourPlusUndo` inherit from the abstract base, overriding win conditions and gameplay logic.
- **Operator Overloading:** Extensive use of operator overloading (`++`, `--`, `==`, `<<`, `>>`) for the `Cell` and `Board` classes to create intuitive and readable code.
- **Dynamic Memory Management:** Custom implementation of 2D dynamic arrays with deep copy and destructor management to prevent memory leaks.
- **Encapsulation:** Strong use of access modifiers (public/private/protected) and namespaces to maintain high-quality code standards.

## 🎮 Game Modes
- **Plus Mode:** Traditional horizontal and vertical win conditions.
- **Diag Mode:** Diagonal-only win conditions for a strategic challenge.
- **Undo Mode:** Supports a move-history stack, allowing players to revert their turns.

## 🛠️ How to Compile and Run
Since the project consists of multiple source files, compile them all together using `g++`:
  g++ *.cpp -o connect4
  ./connect4

## 📜 Key Technical Concepts Covered
-Polymorphic behavior with pointers (gamePtr)
-File I/O for loading game states from text files
-Exception handling and input validation
-Recursion and stack-based undo logic
