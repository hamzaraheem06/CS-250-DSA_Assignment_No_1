#include "polynomial.h"
#include <iostream>
#include <string>

using namespace std;

// Term structure for linked list for polynomial terms
struct Term {
    int coeff;
    int exp;
    Term* next;

    Term(int cof, int exp) : coeff(cof), exp(exp), next(nullptr) {}
};

// Derived class that implements the Polynomial interface
class PolynomialImpl : public Polynomial {
private:
    Term* head;

public:
    PolynomialImpl() : head(nullptr) {}

    virtual ~PolynomialImpl() {
        while (head) {
            Term* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Copy constructor (deep copy)
    PolynomialImpl(const PolynomialImpl& other) : head(nullptr) {
        Term* otherTemp = other.head;
        if (!otherTemp) return;
        head = new Term(otherTemp->coeff, otherTemp->exp);
        Term* current = head;
        otherTemp = otherTemp->next;
        while (otherTemp) {
            current->next = new Term(otherTemp->coeff, otherTemp->exp);
            current = current->next;
            otherTemp = otherTemp->next;
        }
    }

    // Copy assignment operator (deep copy, handles self-assignment)
    PolynomialImpl& operator=(const PolynomialImpl& other) {
        if (this == &other) return *this;  // Self-assignment check
        // Delete existing list
        while (head) {
            Term* temp = head;
            head = head->next;
            delete temp;
        }
        // Deep copy new list
        head = nullptr;
        if (other.head) {
            head = new Term(other.head->coeff, other.head->exp);
            Term* current = head;
            Term* otherTemp = other.head->next;
            while (otherTemp) {
                current->next = new Term(otherTemp->coeff, otherTemp->exp);
                current = current->next;
                otherTemp = otherTemp->next;
            }
        }
        return *this;
    }

    // Insert a term into the polynomial
    virtual void insertTerm(int coefficient, int exponent) {
        // Early return for invalid inputs
        if (coefficient == 0 || exponent < 0) return;

        // Create new term
        Term* newTerm = new Term(coefficient, exponent);

        // handling empty list
        if (!head) {
            head = newTerm;
            return;
        }

        Term* prev = nullptr;
        Term* temp = head;

        // find correct insertion point.
        while(temp && temp->exp > exponent) {
            prev = temp;
            temp = temp->next;
        }

        // handling inserting at the head of the list
        if (!prev && (!temp || temp->exp < exponent)) {
            newTerm->next = temp;
            head = newTerm;
            return;
        }

        // handling insertion at the end of the list
        if (!temp) {
            prev->next = newTerm;
            return;
        }

        // Combine like terms if exponents match
        if (temp->exp == exponent) {
            temp->coeff += coefficient;
            if (temp->coeff == 0) {
                if (!prev) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
            }
            delete newTerm; // Free unused newTerm
            return;
        }

        // insertion at the middle of the list
        newTerm->next = prev->next;
        prev->next = newTerm;
        return;
    }

    // Return polynomial as a human-readable string
    virtual string toString() const {
        // initializing the traversal
        Term* temp = head;
        string result = ""; // output string
        bool isFirst = true; // track if it's the first term
        
        while(temp) {
            // Handle the sign and coefficient
            if (isFirst) {
                result += to_string(temp->coeff);
                isFirst = false;
            } else {
                if (temp->coeff > 0) {
                    result += " + " + to_string(temp->coeff);
                } else {
                    result += " - " + to_string(-temp->coeff);
                }
            }

            if (temp->exp != 0) result += "x^" + to_string(temp->exp);

            temp = temp->next; // advancing the pointer
        }
        return result;
    }

    // Return a new polynomial that is the sum of this and other
    virtual Polynomial* add(const Polynomial& other) const {
        // Try to safely convert other (which is a Polynomial) into a pointer to a PolynomialImpl.
        // If other is really a PolynomialImpl, return a valid pointer.
        // Otherwise, return nullptr.
        const PolynomialImpl* otherImpl = dynamic_cast<const PolynomialImpl*>(&other);
        if (!otherImpl) return nullptr;

        PolynomialImpl* result = new PolynomialImpl(); // resulting polynomial

        Term* h1 = head;
        Term* h2 = otherImpl->head;

        if (!h1 && !h2) {
            return result;
        }

        Term* dummy = new Term(0, 0); // a dummy node to keep track of the head of the result
        Term* it = dummy; // iterable node for result

        while(h1 && h2) { // while there are terms in both polynomials
            Term* newNode;
            if (h1->exp == h2->exp) { // if same exp, we add the coeffs
                int newCof = h1->coeff + h2->coeff;
                if (newCof == 0) { // if the newCoff is zero, we dont add the term
                    h1 = h1->next;
                    h2 = h2->next;
                    continue;
                }
                newNode = new Term(newCof, h1->exp);
                h1 = h1->next;
                h2 = h2->next;
            } else if (h1->exp > h2->exp) { // if the exponent of h1 is greater than h2, we add the h1 term
                newNode = new Term(h1->coeff, h1->exp);
                h1 = h1->next;
            } else { // we add the h2 term, if its exponent is greater than h1
                newNode = new Term(h2->coeff, h2->exp);
                h2 = h2->next;
            }
            it->next = newNode;
            it = newNode;
        }

        while(h1) { // add the remaining terms of h1
            Term* newNode = new Term(h1->coeff, h1->exp);
            h1 = h1->next;
            it->next = newNode;
            it = newNode;
        }

        while(h2) { // add the remaining terms of h2
            Term* newNode = new Term(h2->coeff, h2->exp);
            h2 = h2->next;
            it->next = newNode;
            it = newNode;
        }

        result->head = dummy->next; // reassign the head

        delete dummy; // freeing the dummy node memory
        return result;
    }

    // Return a new polynomial that is the product of this and other
    virtual Polynomial* multiply(const Polynomial& other) const {
        const PolynomialImpl* otherImpl = dynamic_cast<const PolynomialImpl*>(&other);
        if (!otherImpl) return nullptr;

        PolynomialImpl* result = new PolynomialImpl(); // resulting polynomial

        Term* h1 = head;

        if (!h1 || !otherImpl->head) {
            return result;
        }

        while(h1) {
            Term* h2 = otherImpl->head;  // Reset h2 for each h1
            while(h2) {
                int exp = h1->exp + h2->exp;
                int coff = h1->coeff * h2->coeff;

                result->insertTerm(coff, exp);
                h2 = h2->next;
            }
            h1 = h1->next;
        }

        return result;
    }

    // Return a new polynomial that is the derivative of this polynomial
    virtual Polynomial* derivative() const {
        PolynomialImpl* result = new PolynomialImpl();
        Term* cur = head;
        if (!cur) return result;

        while(cur) {
            int coeff = cur->coeff * cur->exp;
            int exp = cur->exp - 1;

            result->insertTerm(coeff, exp);

            cur = cur->next;
        }

        return result;
    }
};