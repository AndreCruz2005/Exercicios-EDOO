#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class HashTable {
private:
    struct Entry {
        int key;
        string value;

        void set(int key, string &value) {
            this->key = key;
            this->value = value;
        }
    };

    typedef vector<Entry> Bucket;
    Bucket *table;
    size_t occupation;

    static int hashKey(int key) {
        return key % 10;
    }

public:
    HashTable() {
        table = new Bucket[10];
        occupation = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    void Add(int key, string value) {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                return;
            }
        }
        Entry newEntry;
        newEntry.set(key, value);
        bucket.push_back(newEntry);
        occupation++;
    }

    string Get(int key) {
        Bucket &bucket = table[hashKey(key)];
        for (const auto &entry: bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        return "";
    }

    void Remove(int key) {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                bucket.erase(bucket.begin() + i);
                occupation--;
            }
        }
    }

    void printout() {
        cout << "alpha = " << occupation << "/10" << endl;
        for (auto i = 0; i < 10; i++) {
            cout << i << ":";
            Bucket &bucket = table[i];
            for (size_t j = 0; j < bucket.size(); j++) {
                if (j == bucket.size() - 1)
                    cout << "(" << bucket[j].key << "," << bucket[j].value << ")";
                else
                    cout << "(" << bucket[j].key << "," << bucket[j].value << "),";
            }
            cout << endl;
        }
    }
};

int main() {
    int cases;
    cin >> cases;
    for (auto i = 1; i <= cases; i++) {
        cout << "caso " << i << ":" << endl;
        HashTable dict;

        int operation;
        cin >> operation;
        cin.ignore();
        while (operation--) {
            string command;
            getline(cin, command);
            istringstream parsing(command);

            vector<string> tokens;
            string token;
            while (parsing >> token)
                tokens.push_back(token);

            if (tokens.size() == 3)
                dict.Add(stoi(tokens[1]), tokens[2]);
            else if (tokens.size() == 2)
                dict.Remove(stoi(tokens[1]));
        }
        dict.printout();
    }
    return 0;
}
