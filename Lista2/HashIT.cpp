#include <iostream>
#include <string>
using namespace std;

class Hashtable {
    struct Entry {
        string value;
        bool isEmpty = true;
    };

    int tableSize;
    int tableOccupation;
    Entry *table;

    int hash(string it, int j) {
        int h = 0;
        for (int i = 0; i < it.length(); i++) {
            h += it[i] * (i + 1);
        }
        return (h * 19 % tableSize + j * j + 23 * j) % tableSize;
    }

    int findItem(string it) {
        for (int j = 0; j < 20; j++) {
            int idx = hash(it, j);
            if (!table[idx].isEmpty && table[idx].value == it) {
                return idx;
            }
        }
        return -1;
    }

public:
    Hashtable() {
        tableOccupation = 0;
        tableSize = 101;
        table = new Entry[tableSize];
    }

    ~Hashtable() {
        delete[] table;
    }

    int addItem(string it) {
        int itemPos = findItem(it);
        if (itemPos != -1) return itemPos;

        for (int j = 0; j < 20; j++) {
            int idx = hash(it, j);
            if (table[idx].isEmpty) {
                table[idx].value = it;
                table[idx].isEmpty = false;
                tableOccupation++;
                return idx;
            }
        }
        return -1;
    }

    int removeItem(string it) {
        int itemPos = findItem(it);
        if (itemPos != -1) {
            table[itemPos].isEmpty = true;
            tableOccupation--;
        }
        return itemPos;
    }

    void printout() {
        cout << tableOccupation << endl;
        for (int i = 0; i < tableSize; i++) {
            const Entry &item = table[i];
            if (!item.isEmpty) {
                cout << i << ":" << item.value << endl;
            }
        }
    }
};

int main() {
    int cases;
    cin >> cases;

    while (cases > 0) {
        Hashtable *ht = new Hashtable;
        int tasks;
        cin >> tasks;
        while (tasks > 0) {
            string input, task, key;
            cin >> input;
            for (auto i = 0; i < input.size(); i++) {
                if (i < 3) {
                    task += input[i];
                } else if (i > 3) {
                    key += input[i];
                }
            }
            if (task == "ADD") {
                ht->addItem(key);
            } else {
                ht->removeItem(key);
            }
            tasks--;
        }
        ht->printout();
        delete ht;
        cases--;
    }
    return 0;
}
