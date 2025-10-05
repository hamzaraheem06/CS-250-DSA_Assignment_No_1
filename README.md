# **Assignment No.01**

**Course:** CS250: Data Structures and Algorithms  
**Section:** BSDS-2  
**Semester:** Fall 2025  
**Student Name:** Hamza Raheem  
**Qalam ID:** 512131

---

## **Overview**

This assignment solution demonstrates the use of **Linked Lists** and other fundamental data structures to implement three practical simulations:

1. **Polynomial ADT** – Algebraic manipulation using linked term representation.
2. **Text Editor Simulation** – Cursor editing simulation using stacks.
3. **UNO Card Game Simulation** – Turn-based game logic with dynamic state updates.

Each problem emphasizes **modularity**, **error handling**, and **efficiency** in implementing core data structure operations.

---

## **Problem 1: Polynomial ADT**

### **Approach**

- Used a **singly linked list** to represent polynomial terms, where each node stores a coefficient and exponent.
- Implemented methods:
  - `insertTerm(coef, exp)` — Inserts a term in descendingly sorted order and merges like terms.
  - `add(const Polynomial& other)` — Creates a new polynomial by adding corresponding terms.
  - `multiply(const Polynomial& other)` — Computes the product polynomial using nested iteration.
  - `derivative()` — Returns the derivative by applying the power rule to each term.
  - `toString()` — Converts polynomial to a readable mathematical string (e.g., `3x^4 + 2x^2 - x + 5`).
- **Corner Cases Handled:**
  - Combining like terms.
  - Skipping zero coefficients.
  - Empty polynomials.

### **Data Structure Used**

- **Linked List of Terms** (`struct Term { int coeff, exp; Term* next; }`)

---

## **Problem 2: Text Editor Simulation**

### **Approach**

- Implemented using **two stacks** to efficiently manage cursor movements:
  - `left` stack holds characters to the left of the cursor.
  - `right` stack holds characters to the right.
- Supported operations:
  - `insertChar(char c)` — Pushes onto left stack.
  - `deleteChar()` — Pops from left stack (simulating backspace).
  - `moveLeft()` / `moveRight()` — Moves characters between stacks to simulate cursor movement.
  - `display()` — Combines both stacks to show text with a ‘|’ cursor indicator.
- **Example:**  
  `"ab|c"` means cursor is after `'b'`.

### **Data Structure Used**

- **Two Stacks (std::stack<char>)** for cursor-based text editing.

### **Corner Cases Handled**

- Prevent cursor from moving out of bounds.
- Deleting when cursor is at start does nothing.
- Displays consistent output after each operation.

---

## **Problem 3: UNO Game Simulation**

### **Approach**

- Implemented `UNOGameImpl` class inheriting from the provided `UNOGame` interface.
- Simulates a 2–4 player UNO game with deck, discard pile, player hands, and turn handling.
- Used `vector<Card>` for deck/piles and `vector<vector<Card>>` for player hands.
- Deck created with 76 cards (numbers + action cards) across 4 colors; shuffled with fixed seed `1234`.

### **Gameplay Logic:**

- Each player starts with 7 cards.
- A turn involves:
  - Playing a color/value/action-matching card.
  - Drawing one if none playable.
  - 50% chance to call “UNO”; failure results in a 2-card penalty.
- Handles Skip, Reverse, and Draw Two effects properly.
- Direction toggles with Reverse; skips and penalties applied correctly.
- Winner determined when a player’s hand is empty.

### **Data Structures:**

- **Vector** for deck and players’ hands, as well as UNO call status.

### **Corner Cases Handled**

- Detects UNO (1 card left).
- Handles empty deck draw attempts.
- Maintains correct direction and skips properly.

---

## **Challenges Faced**

- Managing linked list term merging in Polynomial ADT.
- Handling cursor movement efficiently without reconstructing the whole string.
- Implementing correct action card logic (especially Reverse and Skip) while maintaining direction.
- Ensuring reproducibility in UNO with a fixed random seed.

---

## **Repository Link**

🔗 [GitHub Repository (Public)](https://github.com/hamzaraheem06/CS-250-DSA_Assignment_No_1)

---

## **Compilation & Execution**

```bash
# Compile Polynomial
g++ hamza_raheem_512131_polynomial.cpp -o polynomial
./polynomial

# Compile Text Editor
g++ hamza_raheem_512131_texteditor.cpp -o texteditor
./texteditor

# Compile UNO Game
g++ hamza_raheem_512131_uno.cpp -o uno
./uno
```

---

**Note:** Please add the corresponding interface/function from `main.cpp` before compiling and running the particular application.
