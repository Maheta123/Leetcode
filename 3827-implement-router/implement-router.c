#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_SIZE 200925

typedef struct Packet {
    int source;
    int destination;
    int timestamp;
    struct Packet* next;
} Packet;

typedef struct KeyNode {
    char* key;
    struct KeyNode* next;
} KeyNode;

typedef struct DestInfo {
    int* timestamps;
    int size;
    int capacity;
} DestInfo;

typedef struct Router {
    int memoryLimit;
    int size;
    Packet* head;
    Packet* tail;
    KeyNode* packetSet[HASH_SIZE];
    DestInfo* destMap[HASH_SIZE];
} Router;

unsigned int hashStr(const char* s) {
    unsigned int h = 0;
    while (*s) h = h * 31 + (unsigned char)(*s++);
    return h % HASH_SIZE;
}

unsigned int hashInt(int x) {
    return ((unsigned int)x) % HASH_SIZE;
}

char* makeKey(int source, int dest, int ts) {
    char* key = malloc(32);
    sprintf(key, "%d-%d-%d", source, dest, ts);
    return key;
}

bool keyExists(Router* obj, const char* key) {
    unsigned int h = hashStr(key);
    KeyNode* cur = obj -> packetSet[h];
    while (cur) {
        if (strcmp(cur -> key, key) == 0) return true;
        cur = cur -> next;
    }
    return false;
}

void keyInsert(Router* obj, char* key) {
    unsigned int h = hashStr(key);
    KeyNode* node = malloc(sizeof(KeyNode));
    node -> key = key;
    node -> next = obj -> packetSet[h];
    obj -> packetSet[h] = node;
}

void keyRemove(Router* obj, const char* key) {
    unsigned int h = hashStr(key);
    KeyNode *cur = obj -> packetSet[h], *prev = NULL;
    while (cur) {
        if (strcmp(cur -> key, key) == 0) {
            if (prev) prev -> next = cur -> next;
            else obj -> packetSet[h] = cur -> next;
            free(cur -> key);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur -> next;
    }
}

DestInfo* getDest(Router* obj, int dest) {
    unsigned int h = hashInt(dest);
    return obj -> destMap[h];
}

DestInfo* createDest() {
    DestInfo* d = malloc(sizeof(DestInfo));
    d -> timestamps = malloc(8 * sizeof(int));
    d -> size = 0;
    d -> capacity = 8;
    return d;
}

void addDestTimestamp(Router* obj, int dest, int ts) {
    unsigned int h = hashInt(dest);
    DestInfo* d = obj -> destMap[h];
    if (!d) {
        d = createDest();
        obj -> destMap[h] = d;
    }
    if (d -> size == d -> capacity) {
        d -> capacity *= 2;
        d -> timestamps = realloc(d -> timestamps, d -> capacity * sizeof(int));
    }
    d -> timestamps[d -> size++] = ts;
}

void removeDestTimestamp(Router* obj, int dest, int ts) {
    unsigned int h = hashInt(dest);
    DestInfo* d = obj -> destMap[h];
    if (!d) return;
    int i;
    for (i = 0; i < d -> size; i++) {
        if (d -> timestamps[i] == ts) break;
    }
    if (i == d -> size) return;
    for (int j = i; j < d -> size - 1; j++) d -> timestamps[j] = d -> timestamps[j + 1];
    d -> size--;
    if (d -> size == 0) {
        free(d -> timestamps);
        free(d);
        obj -> destMap[h] = NULL;
    }
}

int lower_bound(int* arr, int n, int target) {
    int l = 0, r = n;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (arr[m] < target) l = m + 1;
        else r = m;
    }
    return l;
}

int upper_bound(int* arr, int n, int target) {
    int l = 0, r = n;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (arr[m] <= target) l = m + 1;
        else r = m;
    }
    return l;
}

Router* routerCreate(int memoryLimit) {
    Router* obj = malloc(sizeof(Router));
    obj -> memoryLimit = memoryLimit;
    obj -> size = 0;
    obj -> head = obj -> tail = NULL;
    memset(obj -> packetSet, 0, sizeof(obj -> packetSet));
    memset(obj -> destMap, 0, sizeof(obj -> destMap));
    return obj;
}

bool routerAddPacket(Router* obj, int source, int dest, int ts) {
    char* key = makeKey(source, dest, ts);
    if (keyExists(obj, key)) {
        free(key);
        return false;
    }

    if (obj -> size == obj -> memoryLimit) {
        Packet* old = obj -> head;
        obj -> head = old -> next;
        if (!obj -> head) obj -> tail = NULL;
        obj -> size--;
        char* oldKey = makeKey(old -> source, old -> destination, old -> timestamp);
        keyRemove(obj, oldKey);
        free(oldKey);
        removeDestTimestamp(obj, old -> destination, old -> timestamp);
        free(old);
    }

    Packet* p = malloc(sizeof(Packet));
    p -> source = source;
    p -> destination = dest;
    p -> timestamp = ts;
    p -> next = NULL;
    if (!obj -> tail) obj -> head = obj -> tail = p;
    else obj -> tail -> next = p, obj -> tail = p;
    obj -> size++;

    keyInsert(obj, key);
    addDestTimestamp(obj, dest, ts);
    return true;
}

int* routerForwardPacket(Router* obj, int* retSize) {
    if (!obj -> head) {
        *retSize = 0;
        return NULL;
    }
    Packet* p = obj -> head;
    obj -> head = p -> next;
    if (!obj -> head) obj -> tail = NULL;
    obj -> size--;

    char* key = makeKey(p -> source, p -> destination, p -> timestamp);
    keyRemove(obj, key);
    free(key);

    removeDestTimestamp(obj, p -> destination, p -> timestamp);

    int* res = malloc(3 * sizeof(int));
    res[0] = p -> source;
    res[1] = p -> destination;
    res[2] = p -> timestamp;
    *retSize = 3;
    free(p);
    return res;
}

int routerGetCount(Router* obj, int dest, int startTime, int endTime) {
    unsigned int h = hashInt(dest);
    DestInfo* d = obj -> destMap[h];
    if (!d) return 0;
    int l = lower_bound(d -> timestamps, d -> size, startTime);
    int r = upper_bound(d -> timestamps, d -> size, endTime);
    return r - l;
}

void routerFree(Router* obj) {
    while (obj -> head) {
        Packet* tmp = obj -> head;
        obj -> head = obj -> head -> next;
        free(tmp);
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        KeyNode* k = obj -> packetSet[i];
        while (k) {
            KeyNode* t = k;
            k = k -> next;
            free(t -> key);
            free(t);
        }
        DestInfo* d = obj -> destMap[i];
        if (d) {
            free(d -> timestamps);
            free(d);
        }
    }
    free(obj);
}