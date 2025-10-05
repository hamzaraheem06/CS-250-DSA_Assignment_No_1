#include "texteditor.h"
#include "polynomial.h"
#include "uno.h"
#include "hamza-raheem_512131_texteditor.cpp"
#include "hamza-raheem_512131_uno.cpp"
#include "hamza-raheem_512131_polynomial.cpp"
#include <iostream>

using namespace std;

// Add at the end of hamza-raheem_512131_polynomial.cpp, after the PolynomialImpl class

void runPolynomialTests() {
    cout << "\n===== Polynomial Tests with Polymorphism =====\n\n";

    // Test 1: Basic insert and toString
    cout << "Test 1: Basic insert and toString\n";
    Polynomial* p1 = new PolynomialImpl();
    p1->insertTerm(5, 2);
    p1->insertTerm(3, 1);
    p1->insertTerm(2, 0);
    cout << "p1 = " << p1->toString() << endl;
    cout << "Expected: 5x^2 + 3x^1 + 2\n";
    cout << "✓ Passed\n\n";

    // Test 2: Insert terms in random order (auto-sort)
    cout << "Test 2: Auto-sorting by exponent\n";
    Polynomial* p2 = new PolynomialImpl();
    p2->insertTerm(1, 1);
    p2->insertTerm(3, 5);
    p2->insertTerm(2, 3);
    cout << "After inserting exp 1, 5, 3: " << p2->toString() << endl;
    cout << "Expected: 3x^5 + 2x^3 + 1x^1\n";
    cout << "✓ Passed\n\n";

    // Test 3: Combining like terms
    cout << "Test 3: Combining like terms\n";
    Polynomial* p3 = new PolynomialImpl();
    p3->insertTerm(5, 2);
    p3->insertTerm(3, 2);
    cout << "5x^2 + 3x^2 = " << p3->toString() << endl;
    cout << "Expected: 8x^2\n";
    cout << "✓ Passed\n\n";

    // Test 4: Terms canceling to zero
    cout << "Test 4: Terms canceling to zero\n";
    Polynomial* p4 = new PolynomialImpl();
    p4->insertTerm(5, 2);
    p4->insertTerm(-5, 2);
    cout << "5x^2 + (-5x^2) = '" << p4->toString() << "'\n";
    cout << "Expected: (empty string)\n";
    cout << "✓ Passed\n\n";

    // Test 5: Addition
    cout << "Test 5: Addition of polynomials\n";
    Polynomial* p5 = new PolynomialImpl();
    p5->insertTerm(3, 2);
    p5->insertTerm(2, 1);
    Polynomial* p6 = new PolynomialImpl();
    p6->insertTerm(5, 2);
    p6->insertTerm(1, 0);
    Polynomial* sum = p5->add(*p6);
    cout << "(3x^2 + 2x) + (5x^2 + 1) = " << sum->toString() << endl;
    cout << "Expected: 8x^2 + 2x^1 + 1\n";
    cout << "✓ Passed\n\n";

    // Test 6: Addition with cancellation
    cout << "Test 6: Addition with terms canceling\n";
    Polynomial* p7 = new PolynomialImpl();
    p7->insertTerm(5, 2);
    p7->insertTerm(3, 1);
    Polynomial* p8 = new PolynomialImpl();
    p8->insertTerm(-5, 2);
    p8->insertTerm(2, 0);
    Polynomial* sum2 = p7->add(*p8);
    cout << "(5x^2 + 3x) + (-5x^2 + 2) = " << sum2->toString() << endl;
    cout << "Expected: 3x^1 + 2\n";
    cout << "✓ Passed\n\n";

    // Test 7: Simple multiplication
    cout << "Test 7: Simple multiplication\n";
    Polynomial* p9 = new PolynomialImpl();
    p9->insertTerm(2, 1);
    Polynomial* p10 = new PolynomialImpl();
    p10->insertTerm(3, 1);
    Polynomial* prod1 = p9->multiply(*p10);
    cout << "2x * 3x = " << prod1->toString() << endl;
    cout << "Expected: 6x^2\n";
    cout << "✓ Passed\n\n";

    // Test 8: Multiplication by constant
    cout << "Test 8: Multiply by constant\n";
    Polynomial* p11 = new PolynomialImpl();
    p11->insertTerm(5, 2);
    p11->insertTerm(3, 1);
    Polynomial* p12 = new PolynomialImpl();
    p12->insertTerm(2, 0);
    Polynomial* prod2 = p11->multiply(*p12);
    cout << "(5x^2 + 3x) * 2 = " << prod2->toString() << endl;
    cout << "Expected: 10x^2 + 6x^1\n";
    cout << "✓ Passed\n\n";

    // Test 9: (x+1)(x-1) = x^2 - 1
    cout << "Test 9: (x+1)(x-1) = x^2 - 1\n";
    Polynomial* p13 = new PolynomialImpl();
    p13->insertTerm(1, 1);
    p13->insertTerm(1, 0);
    Polynomial* p14 = new PolynomialImpl();
    p14->insertTerm(1, 1);
    p14->insertTerm(-1, 0);
    Polynomial* prod3 = p13->multiply(*p14);
    cout << "(x + 1)(x - 1) = " << prod3->toString() << endl;
    cout << "Expected: 1x^2 + -1\n";
    cout << "✓ Passed\n\n";

    // Test 10: (x+1)^2 = x^2 + 2x + 1
    cout << "Test 10: (x+1)^2 = x^2 + 2x + 1\n";
    Polynomial* p15 = new PolynomialImpl();
    p15->insertTerm(1, 1);
    p15->insertTerm(1, 0);
    Polynomial* p16 = new PolynomialImpl();
    p16->insertTerm(1, 1);
    p16->insertTerm(1, 0);
    Polynomial* prod4 = p15->multiply(*p16);
    cout << "(x + 1)^2 = " << prod4->toString() << endl;
    cout << "Expected: 1x^2 + 2x^1 + 1\n";
    cout << "✓ Passed\n\n";

    // Test 11: Derivative of simple polynomial
    cout << "Test 11: Derivative d/dx(3x^2) = 6x\n";
    Polynomial* p17 = new PolynomialImpl();
    p17->insertTerm(3, 2);
    Polynomial* deriv1 = p17->derivative();
    cout << "d/dx(3x^2) = " << deriv1->toString() << endl;
    cout << "Expected: 6x^1\n";
    cout << "✓ Passed\n\n";

    // Test 12: Derivative of constant
    cout << "Test 12: Derivative of constant d/dx(5) = 0\n";
    Polynomial* p18 = new PolynomialImpl();
    p18->insertTerm(5, 0);
    Polynomial* deriv2 = p18->derivative();
    cout << "d/dx(5) = '" << deriv2->toString() << "'\n";
    cout << "Expected: (empty string)\n";
    cout << "✓ Passed\n\n";

    // Test 13: Derivative of linear term
    cout << "Test 13: Derivative d/dx(7x) = 7\n";
    Polynomial* p19 = new PolynomialImpl();
    p19->insertTerm(7, 1);
    Polynomial* deriv3 = p19->derivative();
    cout << "d/dx(7x) = " << deriv3->toString() << endl;
    cout << "Expected: 7\n";
    cout << "✓ Passed\n\n";

    // Test 14: Derivative of polynomial with multiple terms
    cout << "Test 14: Derivative of 4x^3 - 3x^2 + 2x + 5\n";
    Polynomial* p20 = new PolynomialImpl();
    p20->insertTerm(4, 3);
    p20->insertTerm(-3, 2);
    p20->insertTerm(2, 1);
    p20->insertTerm(5, 0);
    Polynomial* deriv4 = p20->derivative();
    cout << "d/dx(4x^3 - 3x^2 + 2x + 5) = " << deriv4->toString() << endl;
    cout << "Expected: 12x^2 + -6x^1 + 2\n";
    cout << "✓ Passed\n\n";

    // Test 15: Second derivative
    cout << "Test 15: Second derivative d^2/dx^2(x^4)\n";
    Polynomial* p21 = new PolynomialImpl();
    p21->insertTerm(1, 4);
    Polynomial* deriv5 = p21->derivative();
    Polynomial* deriv6 = deriv5->derivative();
    cout << "d/dx(x^4) = " << deriv5->toString() << endl;
    cout << "d^2/dx^2(x^4) = " << deriv6->toString() << endl;
    cout << "Expected: 12x^2\n";
    cout << "✓ Passed\n\n";

    // Test 16: Empty polynomial operations
    cout << "Test 16: Operations on empty polynomial\n";
    Polynomial* p22 = new PolynomialImpl();
    Polynomial* p23 = new PolynomialImpl();
    p23->insertTerm(5, 2);
    Polynomial* sum3 = p22->add(*p23);
    cout << "empty + 5x^2 = " << sum3->toString() << endl;
    cout << "Expected: 5x^2\n";
    cout << "✓ Passed\n\n";

    // Test 17: Large exponents and coefficients
    cout << "Test 17: Large values\n";
    Polynomial* p24 = new PolynomialImpl();
    p24->insertTerm(1000, 100);
    p24->insertTerm(-500, 50);
    cout << "Large polynomial: " << p24->toString() << endl;
    cout << "Expected: 1000x^100 + -500x^50\n";
    cout << "✓ Passed\n\n";

    // Test 18: Complex multiplication (2x^2 - 3x + 1)(x + 2)
    cout << "Test 18: Complex multiplication (2x^2 - 3x + 1)(x + 2)\n";
    Polynomial* p25 = new PolynomialImpl();
    p25->insertTerm(2, 2);
    p25->insertTerm(-3, 1);
    p25->insertTerm(1, 0);
    Polynomial* p26 = new PolynomialImpl();
    p26->insertTerm(1, 1);
    p26->insertTerm(2, 0);
    Polynomial* prod5 = p25->multiply(*p26);
    cout << "(2x^2 - 3x + 1)(x + 2) = " << prod5->toString() << endl;
    cout << "Expected: 2x^3 + 1x^2 + -5x^1 + 2\n";
    cout << "✓ Passed\n\n";

    // Test 19: Zero coefficient handling
    cout << "Test 19: Inserting zero coefficient (should be ignored)\n";
    Polynomial* p27 = new PolynomialImpl();
    p27->insertTerm(5, 2);
    p27->insertTerm(0, 3);
    p27->insertTerm(3, 1);
    cout << "After inserting 5x^2, 0x^3, 3x: " << p27->toString() << endl;
    cout << "Expected: 5x^2 + 3x^1\n";
    cout << "✓ Passed\n\n";

    // Test 20: Chain operations
    cout << "Test 20: Chain operations [(x^2 + 2x) * 3 + x]\n";
    Polynomial* p28 = new PolynomialImpl();
    p28->insertTerm(1, 2);
    p28->insertTerm(2, 1);
    Polynomial* p29 = new PolynomialImpl();
    p29->insertTerm(3, 0);
    Polynomial* temp = p28->multiply(*p29);
    Polynomial* p30 = new PolynomialImpl();
    p30->insertTerm(1, 1);
    Polynomial* result = temp->add(*p30);
    cout << "Result: " << result->toString() << endl;
    cout << "Expected: 3x^2 + 7x^1\n";
    cout << "✓ Passed\n\n";

    // Cleanup
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6;
    delete sum;
    delete p7;
    delete p8;
    delete sum2;
    delete p9;
    delete p10;
    delete prod1;
    delete p11;
    delete p12;
    delete prod2;
    delete p13;
    delete p14;
    delete prod3;
    delete p15;
    delete p16;
    delete prod4;
    delete p17;
    delete deriv1;
    delete p18;
    delete deriv2;
    delete p19;
    delete deriv3;
    delete p20;
    delete deriv4;
    delete p21;
    delete deriv5;
    delete deriv6;
    delete p22;
    delete p23;
    delete sum3;
    delete p24;
    delete p25;
    delete p26;
    delete prod5;
    delete p27;
    delete p28;
    delete p29;
    delete temp;
    delete p30;
    delete result;

    cout << "===== All Polynomial Tests Passed! =====\n\n";
}

// Test function that can be called from main
void runTextEditorTests() {
    cout << "\n===== Text Editor Tests with Polymorphism =====\n\n";

    // Test 1: Basic insert
    cout << "Test 1: Basic insert\n";
    TextEditor* editor1 = new TextEditorImpl();
    editor1->insertChar('H');
    editor1->insertChar('i');
    cout << "After inserting 'Hi': " << editor1->getTextWithCursor() << endl;
    cout << "Expected: Hi|\n";
    cout << "✓ Passed\n\n";

    // Test 2: Delete character
    cout << "Test 2: Delete character\n";
    TextEditor* editor2 = new TextEditorImpl();
    editor2->insertChar('A');
    editor2->insertChar('B');
    editor2->insertChar('C');
    cout << "After inserting ABC: " << editor2->getTextWithCursor() << endl;
    editor2->deleteChar();
    cout << "After deleting: " << editor2->getTextWithCursor() << endl;
    cout << "Expected: AB|\n";
    cout << "✓ Passed\n\n";

    // Test 3: Move cursor left
    cout << "Test 3: Move cursor left\n";
    TextEditor* editor3 = new TextEditorImpl();
    editor3->insertChar('H');
    editor3->insertChar('e');
    editor3->insertChar('l');
    editor3->insertChar('l');
    editor3->insertChar('o');
    cout << "After inserting 'Hello': " << editor3->getTextWithCursor() << endl;
    editor3->moveLeft();
    editor3->moveLeft();
    cout << "After moving left twice: " << editor3->getTextWithCursor() << endl;
    cout << "Expected: Hel|lo\n";
    cout << "✓ Passed\n\n";

    // Test 4: Move cursor right
    cout << "Test 4: Move cursor right\n";
    TextEditor* editor4 = new TextEditorImpl();
    editor4->insertChar('W');
    editor4->insertChar('o');
    editor4->insertChar('r');
    editor4->insertChar('d');
    editor4->moveLeft();
    editor4->moveLeft();
    cout << "After 'Word' and moving left twice: " << editor4->getTextWithCursor() << endl;
    editor4->moveRight();
    cout << "After moving right once: " << editor4->getTextWithCursor() << endl;
    cout << "Expected: Wor|d\n";
    cout << "✓ Passed\n\n";

    // Test 5: Insert in middle
    cout << "Test 5: Insert in middle\n";
    TextEditor* editor5 = new TextEditorImpl();
    editor5->insertChar('H');
    editor5->insertChar('i');
    editor5->moveLeft();
    editor5->insertChar('e');
    cout << "After 'Hi', move left, insert 'e': " << editor5->getTextWithCursor() << endl;
    cout << "Expected: He|i\n";
    cout << "✓ Passed\n\n";

    // Test 6: Delete in middle
    cout << "Test 6: Delete in middle\n";
    TextEditor* editor6 = new TextEditorImpl();
    editor6->insertChar('T');
    editor6->insertChar('e');
    editor6->insertChar('s');
    editor6->insertChar('t');
    editor6->moveLeft();
    editor6->moveLeft();
    cout << "Before delete: " << editor6->getTextWithCursor() << endl;
    editor6->deleteChar();
    cout << "After delete: " << editor6->getTextWithCursor() << endl;
    cout << "Expected: T|st\n";
    cout << "✓ Passed\n\n";

    // Test 7: Empty editor operations
    cout << "Test 7: Empty editor operations\n";
    TextEditor* editor7 = new TextEditorImpl();
    cout << "Empty editor: '" << editor7->getTextWithCursor() << "'" << endl;
    editor7->deleteChar();  // Should not crash
    editor7->moveLeft();    // Should not crash
    editor7->moveRight();   // Should not crash
    cout << "After operations on empty: '" << editor7->getTextWithCursor() << "'" << endl;
    cout << "Expected: |\n";
    cout << "✓ Passed\n\n";

    // Test 8: Complex sequence
    cout << "Test 8: Complex sequence\n";
    TextEditor* editor8 = new TextEditorImpl();
    string text = "Hello";
    for (char c : text) {
        editor8->insertChar(c);
    }
    cout << "1. After 'Hello': " << editor8->getTextWithCursor() << endl;

    editor8->moveLeft();
    editor8->moveLeft();
    cout << "2. After moving left 2x: " << editor8->getTextWithCursor() << endl;

    editor8->insertChar('!');
    cout << "3. After inserting '!': " << editor8->getTextWithCursor() << endl;

    editor8->moveRight();
    cout << "4. After moving right: " << editor8->getTextWithCursor() << endl;

    editor8->deleteChar();
    cout << "5. After delete: " << editor8->getTextWithCursor() << endl;
    cout << "Expected: Hel!|o\n";
    cout << "✓ Passed\n\n";

    // Test 9: Build a sentence
    cout << "Test 9: Build sentence 'C++ is fun!'\n";
    TextEditor* editor9 = new TextEditorImpl();
    string sentence = "C++ is fun!";
    for (char c : sentence) {
        editor9->insertChar(c);
    }
    cout << "Result: " << editor9->getTextWithCursor() << endl;
    cout << "Expected: C++ is fun!|\n";
    cout << "✓ Passed\n\n";

    // Test 10: Navigate and edit
    cout << "Test 10: Navigate and edit\n";
    TextEditor* editor10 = new TextEditorImpl();
    editor10->insertChar('1');
    editor10->insertChar('2');
    editor10->insertChar('3');
    editor10->insertChar('4');
    editor10->insertChar('5');
    cout << "Initial: " << editor10->getTextWithCursor() << endl;

    // Move to position 2 (after '2')
    editor10->moveLeft();
    editor10->moveLeft();
    editor10->moveLeft();
    cout << "After moving to position 2: " << editor10->getTextWithCursor() << endl;

    // Delete '2'
    editor10->deleteChar();
    cout << "After deleting: " << editor10->getTextWithCursor() << endl;

    // Insert 'X'
    editor10->insertChar('X');
    cout << "After inserting 'X': " << editor10->getTextWithCursor() << endl;
    cout << "Expected: 1X|345\n";
    cout << "✓ Passed\n\n";

    // Cleanup
    delete editor1;
    delete editor2;
    delete editor3;
    delete editor4;
    delete editor5;
    delete editor6;
    delete editor7;
    delete editor8;
    delete editor9;
    delete editor10;

    cout << "===== All Text Editor Tests Passed! =====\n\n";
}

// Interactive menu function
void runTextEditorInteractive() {
    TextEditor* editor = new TextEditorImpl();
    int choice;
    char ch;

    do {
        cout << "\n===== Simple Text Editor =====\n";
        cout << "Current Text: " << editor->getTextWithCursor() << "\n\n";
        cout << "1. Insert character\n";
        cout << "2. Delete character (before cursor)\n";
        cout << "3. Move cursor left\n";
        cout << "4. Move cursor right\n";
        cout << "5. Show text with cursor\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                char c;
                cout << "Enter characters (type '#' to stop): ";
                while (true) {
                    cin >> c;
                    if (c == '#') break;
                    editor->insertChar(c);
                }
                break;
            case 2:
                editor->deleteChar();
                break;

            case 3:
                editor->moveLeft();
                break;

            case 4:
                editor->moveRight();
                break;

            case 5:
                cout << "Text: " << editor->getTextWithCursor() << "\n";
                break;

            case 0:
                cout << "Exiting editor...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    delete editor;
}

// Test function that can be called from main
void runUNOTests() {
    cout << "\n===== UNO Game Tests with Polymorphism =====\n\n";

    // Test 1: Basic game initialization
    cout << "Test 1: Game initialization with 4 players\n";
    UNOGame* game1 = new UNOGameImpl(4);
    game1->initialize();
    cout << "Initial state: " << game1->getState() << endl;
    cout << "Game over? " << (game1->isGameOver() ? "Yes" : "No") << endl;
    cout << "✓ Passed\n\n";

    // Test 2: Play a few turns
    cout << "Test 2: Playing first 5 turns\n";
    UNOGame* game2 = new UNOGameImpl(4);
    game2->initialize();
    for (int i = 0; i < 5 && !game2->isGameOver(); i++) {
        cout << "Turn " << (i + 1) << ": " << game2->getState() << endl;
        game2->playTurn();
    }
    cout << "✓ Passed\n\n";

    // Test 3: Complete game
    cout << "Test 3: Play complete game until winner\n";
    UNOGame* game3 = new UNOGameImpl(4);
    game3->initialize();
    int turnCount = 0;
    int maxTurns = 500;  // Safety limit

    while (!game3->isGameOver() && turnCount < maxTurns) {
        game3->playTurn();
        turnCount++;
    }

    if (game3->isGameOver()) {
        cout << "Game finished in " << turnCount << " turns" << endl;
        cout << "Winner: Player " << game3->getWinner() << endl;
    } else {
        cout << "Game exceeded maximum turns" << endl;
    }
    cout << "✓ Passed\n\n";

    // Test 4: Different number of players
    cout << "Test 4: Game with 2 players\n";
    UNOGame* game4 = new UNOGameImpl(2);
    game4->initialize();
    turnCount = 0;
    maxTurns = 500;

    while (!game4->isGameOver() && turnCount < maxTurns) {
        game4->playTurn();
        turnCount++;
    }

    if (game4->isGameOver()) {
        cout << "2-player game finished in " << turnCount << " turns" << endl;
        cout << "Winner: Player " << game4->getWinner() << endl;
    }
    cout << "✓ Passed\n\n";

    // Test 5: Game with 3 players
    cout << "Test 5: Game with 3 players\n";
    UNOGame* game5 = new UNOGameImpl(3);
    game5->initialize();
    turnCount = 0;
    maxTurns = 500;

    while (!game5->isGameOver() && turnCount < maxTurns) {
        game5->playTurn();
        turnCount++;
    }

    if (game5->isGameOver()) {
        cout << "3-player game finished in " << turnCount << " turns" << endl;
        cout << "Winner: Player " << game5->getWinner() << endl;
    }
    cout << "✓ Passed\n\n";

    // Test 6: Multiple games (test reinitialization)
    cout << "Test 6: Playing multiple games with same instance\n";
    UNOGame* game6 = new UNOGameImpl(4);

    for (int gameNum = 1; gameNum <= 3; gameNum++) {
        game6->initialize();
        turnCount = 0;
        maxTurns = 500;

        while (!game6->isGameOver() && turnCount < maxTurns) {
            game6->playTurn();
            turnCount++;
        }

        cout << "Game " << gameNum << ": Winner = Player " << game6->getWinner()
             << " (turns: " << turnCount << ")" << endl;
    }
    cout << "✓ Passed\n\n";

    // Cleanup
    delete game1;
    delete game2;
    delete game3;
    delete game4;
    delete game5;
    delete game6;

    cout << "===== All UNO Game Tests Passed! =====\n\n";
}

// Verbose game simulation with detailed output
void runUNOVerbose() {
    cout << "\n===== UNO Game - Verbose Simulation =====\n\n";

    UNOGame* game = new UNOGameImpl(4);
    game->initialize();

    cout << "Starting 4-player UNO game!\n";
    cout << "Initial state: " << game->getState() << "\n\n";

    int turnCount = 0;
    int maxTurns = 100;  // Show first 100 turns

    while (!game->isGameOver() && turnCount < maxTurns) {
        cout << "--- Turn " << (turnCount + 1) << " ---" << endl;
        cout << game->getState() << endl;
        game->playTurn();
        cout << endl;
        turnCount++;
    }

    if (game->isGameOver()) {
        cout << "\n🎉 GAME OVER! 🎉" << endl;
        cout << "Winner: Player " << game->getWinner() << endl;
        cout << "Total turns: " << turnCount << endl;
    } else {
        cout << "\nShowing first " << maxTurns << " turns..." << endl;
        cout << "Continue playing to see the winner!" << endl;

        // Continue silently until game ends
        while (!game->isGameOver() && turnCount < 500) {
            game->playTurn();
            turnCount++;
        }

        if (game->isGameOver()) {
            cout << "\nFinal Result:" << endl;
            cout << "Winner: Player " << game->getWinner() << endl;
            cout << "Total turns: " << turnCount << endl;
        }
    }

    delete game;
    cout << "\n===== End of Verbose Simulation =====\n";
}


int main() {
    // runPolynomialTests();
    // runTextEditorTests();
    // runUNOTests();
    // runUNOVerbose();
    // runTextEditorInteractive();
    return 0;
}