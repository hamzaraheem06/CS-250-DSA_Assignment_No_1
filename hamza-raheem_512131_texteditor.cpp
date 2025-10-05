#include "texteditor.h"
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Derived class that implements the TextEditor interface
class TextEditorImpl : public TextEditor {
private:
    stack<char> left;
    stack<char> right;

    // helper method for moveLeft
    static stack<char> insertAtBottom(stack<char> st, char c) {
        if (st.empty()) {
            st.push(c);
            return st;
        }

        char top = st.top();
        st.pop();
        stack<char> rest = insertAtBottom(st, c);

        rest.push(top);
        return rest;
    }

    // helper method for moveRight
    // Remove and return the bottom element of st (in-place recursion).
    // Returns '\0' if stack is empty.
    static char removeBottom(stack<char>& st) {
        if (st.empty()) return '\0';
        char top = st.top();
        st.pop();
        if (st.empty()) {
            // top was the only element -> it was the bottom
            return top;
        }
        // otherwise recurse to get bottom, then restore top
        char bottom = removeBottom(st);
        st.push(top);
        return bottom;
    }

public:
    TextEditorImpl() {}

    ~TextEditorImpl() override {}

    // Insert character at cursor
    void insertChar(char c) override {
        left.push(c);
    }

    // Delete character before cursor
    void deleteChar() override {
        if (left.empty()) return;
        left.pop();
    }

    // Move cursor one position left
    void moveLeft() override {
        if (left.empty()) return;

        char left_top = left.top();
        left.pop();
        right = insertAtBottom(right, left_top);
    }

    // Move cursor one position right
    void moveRight() override {
        if (right.empty()) return;

        char right_bottom = removeBottom(right);

        if (right_bottom != '\0') left.push(right_bottom);
    }

    // Return string with cursor position
    string getTextWithCursor() const override {
        stack<char> temp(left);
        string left_text = "";
        while(!temp.empty()) {
            char top = temp.top();
            left_text = top + left_text;
            temp.pop();
        }

        left_text = left_text + "|";

        temp = stack<char>(right);
        string right_text = "";
        while(!temp.empty()) {
            char top = temp.top();
            right_text = top + right_text;
            temp.pop();
        }

        return left_text + right_text;
    }
};