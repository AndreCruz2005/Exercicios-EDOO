#include <iostream>
#include <string>
using namespace std;

class Queue {
    string *arr;
    size_t currentSize;
    size_t maxSize;

public:
    Queue() {
        currentSize = 0;
        maxSize = 301;
        arr = new string[301];
    }

    ~Queue() {
        delete[] arr;
    }

    void add(string &name, size_t idx) {
        if (idx > currentSize) { idx = currentSize; }
        for (size_t i = currentSize; i > idx; i--) {
            arr[i] = arr[i - 1];
        }

        arr[idx] = name;
        currentSize++;
    }

    void remove() {
        if (currentSize == 0) return;
        for (size_t i = 0; i < currentSize; i++) {
            arr[i] = arr[i + 1];
        }

        currentSize--;
    }

    string &operator[](size_t idx) {
        return arr[idx];
    }

    void status() {
        for (size_t i = 0; i < currentSize; i++) {
            string name = operator[](i);
            if (i == currentSize - 1) {
                cout << name << endl;
                return;
            }

            cout << name << ", ";
        }
        cout << "---" << endl;
    }

    size_t len() {
        return currentSize;
    }
};

class Parser {
public:
    string input;
    string action;
    string name;
    string index;

    Parser(string &in) {
        input = in;
        action = "";
        name = "";
        index = "0";
    }

    void Parse() {
        int step = 1;
        for (char c: input) {
            string character = string(1, c);
            if (character == " ") {
                step++;
            } else if (step == 1) {
                action += c;
            } else if (step == 2) {
                try {
                    stoi(character);
                    index += character;
                } catch (const invalid_argument &) {
                    name += character;
                    step++;
                }
            } else if (step == 3) {
                name += character;
            }
        }
    }
};

int main() {
    int cases;
    cin >> cases;

    for (int c = 0; c < cases; c++) {
        int operations;
        cin >> operations;
        cout << "caso " << c + 1 << ":" << endl;
        cin.ignore();

        Queue fila;
        for (int op = 0; op < operations; op++) {
            string task;
            getline(cin, task);

            Parser p(task);
            p.Parse();

            if (p.action == "add") {
                fila.add(p.name,stoi(p.index)-1);
            } else if (p.action == "next") {
                fila.remove();
            } else if (p.action == "status") {
                fila.status();
            }
        }
    }
    return 0;
}
