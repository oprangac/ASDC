#include <iostream>
#include <string>
#include <vector>

struct BucketNode {
    std::string key;
    int value;
    BucketNode* next;
};

struct HashTable {
    std::vector<BucketNode*> buckets;
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
    table->buckets.resize(capacity, nullptr);
    table->hashFunc = defaultHashFunc;
    return table;
}

void add(HashTable* table, const std::string& key, int value) {
    size_t index = table->hashFunc(key) % table->buckets.size();
    BucketNode* newNode = new BucketNode{key, value, nullptr};
    
    if (!table->buckets[index]) {
        table->buckets[index] = newNode;
    } else {
        BucketNode* current = table->buckets[index];
        while (current) {
            if (current->key == key) {
                current->value = value;
                delete newNode;
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode;
    }
}

int* find(HashTable* table, const std::string& key) {
    size_t index = table->hashFunc(key) % table->buckets.size();
    BucketNode* current = table->buckets[index];
    while (current) {
        if (current->key == key) {
            return &current->value;
        }
        current = current->next;
    }
    return nullptr;
}

void remove(HashTable* table, const std::string& key) {
    size_t index = table->hashFunc(key) % table->buckets.size();
    BucketNode* current = table->buckets[index];
    BucketNode* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void freeHashTable(HashTable* table) {
    for (auto& bucket : table->buckets) {
        BucketNode* current = bucket;
        while (current) {
            BucketNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
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
- Complexity of Add/Search:
Best Case: 
𝑂(1) if the hash function distributes keys evenly (ideal case).
Worst Case: 
𝑂(n), where n is the number of elements in a bucket (all keys map to the same bucket).

- Why Ideal Hash Functions Help:
An ideal hash function ensures uniform key distribution, minimizing collisions and maintaining 𝑂(1) complexity.

- Impact of a Poor Hash Function:
A poor hash function (e.g., always returning 0) leads to all keys being stored in a single bucket, degrading performance to 𝑂(n).

- Effect of the Number of Buckets:
More buckets reduce collisions, improving efficiency. However, too many buckets waste memory. Resizing balances this trade-off.
*/