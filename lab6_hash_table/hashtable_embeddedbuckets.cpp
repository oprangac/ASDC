#include <iostream>
#include <string>
#include <vector>

struct Bucket {
    bool occupied = false;
    std::string key;
    int value;
};

struct HashTable {
    std::vector<Bucket> buckets;
    size_t (*hashFunc)(const std::string&);
};

size_t defaultHashFunc(const std::string& key) {
    size_t hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;
    }
    return hash;
}

HashTable* createHashTable(size_t capacity) {
    HashTable* table = new HashTable;
    table->buckets.resize(capacity);
    table->hashFunc = defaultHashFunc;
    return table;
}

void add(HashTable* table, const std::string& key, int value) {
    size_t index = table->hashFunc(key) % table->buckets.size();
    size_t startIndex = index;

    while (table->buckets[index].occupied) {
        if (table->buckets[index].key == key) {
            table->buckets[index].value = value;
            return;
        }
        index = (index + 1) % table->buckets.size();
        if (index == startIndex) {
            std::cerr << "Error: Hash table is full!\n";
            return;
        }
    }

    table->buckets[index].occupied = true;
    table->buckets[index].key = key;
    table->buckets[index].value = value;
}

int* find(HashTable* table, const std::string& key) {
    size_t index = table->hashFunc(key) % table->buckets.size();
    size_t startIndex = index;

    while (table->buckets[index].occupied) {
        if (table->buckets[index].key == key) {
            return &table->buckets[index].value;
        }
        index = (index + 1) % table->buckets.size();
        if (index == startIndex) {
            break;
        }
    }
    return nullptr;
}

void remove(HashTable* table, const std::string& key) {
    size_t index = table->hashFunc(key) % table->buckets.size();
    size_t startIndex = index;

    while (table->buckets[index].occupied) {
        if (table->buckets[index].key == key) {
            table->buckets[index].occupied = false;
            return;
        }
        index = (index + 1) % table->buckets.size();
        if (index == startIndex) {
            break;
        }
    }
    std::cerr << "Error: Key not found for removal!\n";
}

void freeHashTable(HashTable* table) {
    delete table;
}

void demonstrateUsage() {
    HashTable* table = createHashTable(10);

    add(table, "abc", 123);
    add(table, "def", 456);
    add(table, "ghi", 789);

    int* value = find(table, "abc");
    if (value) {
        std::cout << "Found value for 'abc': " << *value << std::endl;
    } else {
        std::cout << "Key 'abc' not found" << std::endl;
    }

    remove(table, "abc");
    value = find(table, "abc");
    if (value) {
        std::cout << "Found value for 'abc': " << *value << std::endl;
    } else {
        std::cout << "Key 'abc' not found after removal" << std::endl;
    }

    freeHashTable(table);
}

int main() {
    demonstrateUsage();
    return 0;
}

/*
- Best Case (No Collisions):
Complexity: 𝑂(1)
Explanation: When there are no collisions, the key is hashed, and the corresponding bucket is directly found and used. Both adding and searching take constant time.

- Worst Case (High Collisions):

Complexity: 𝑂(n), where n is the number of buckets in the hash table.
Explanation: In the worst-case scenario (e.g., poor hash function or table nearly full), a search or insert operation might have to probe all buckets to find an empty spot or the key.

- Average Case:

Complexity: 𝑂(1) (if the load factor is low and the hash function is good).
*/