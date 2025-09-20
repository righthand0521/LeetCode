#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (1)
#define PACKET_HASH_SIZE (4096)
#define DEST_HASH_SIZE (4096)

typedef struct {
    int source;
    int destination;
    int timestamp;
} Packet;
typedef struct PacketSetNode {
    Packet packet;
    struct PacketSetNode* next;
} PacketSetNode;
typedef struct {
    PacketSetNode** table;
    int size;
} PacketSet;
unsigned int hashPacket(Packet* p, int mod) {
    unsigned int h = 17;
    h = h * 31 + p->source;
    h = h * 31 + p->destination;
    h = h * 31 + p->timestamp;
    return h % mod;
}
PacketSet* packetSetCreate(int size) {
    PacketSet* set = malloc(sizeof(PacketSet));
    set->size = size;
    set->table = calloc(size, sizeof(PacketSetNode*));
    return set;
}
bool packetSetContains(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = set->table[idx];
    while (node) {
        if (node->packet.source == p->source && node->packet.destination == p->destination &&
            node->packet.timestamp == p->timestamp)
            return true;
        node = node->next;
    }
    return false;
}
void packetSetAdd(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = malloc(sizeof(PacketSetNode));
    node->packet = *p;
    node->next = set->table[idx];
    set->table[idx] = node;
}
void packetSetRemove(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = set->table[idx];
    PacketSetNode* prev = NULL;
    while (node) {
        if (node->packet.source == p->source && node->packet.destination == p->destination &&
            node->packet.timestamp == p->timestamp) {
            if (prev)
                prev->next = node->next;
            else
                set->table[idx] = node->next;
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}
void packetSetFree(PacketSet* set) {
    for (int i = 0; i < set->size; i++) {
        PacketSetNode* node = set->table[i];
        while (node) {
            PacketSetNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(set->table);
    free(set);
}
#endif
#if (1)
typedef struct Pair {
    int* timestamps;
    int size;
    int capacity;
    int head;
} Pair;
typedef struct DestNode {
    int destination;
    Pair pair;
    struct DestNode* next;
} DestNode;
#endif
typedef struct {
    int memoryLimit;
    int packetCount;
    Packet* queue;
    int head;
    int tail;
    PacketSet* packetSet;
    DestNode** destTable;
} Router;
#if (1)
unsigned int hashDest(int destination) {
    //
    return destination % DEST_HASH_SIZE;
}
Pair* getPair(Router* obj, int destination) {
    unsigned int idx = hashDest(destination);
    DestNode* node = obj->destTable[idx];
    while (node) {
        if (node->destination == destination) {
            return &node->pair;
        }
        node = node->next;
    }
    node = malloc(sizeof(DestNode));
    node->destination = destination;
    node->pair.timestamps = NULL;
    node->pair.size = 0;
    node->pair.capacity = 0;
    node->pair.head = 0;
    node->next = obj->destTable[idx];
    obj->destTable[idx] = node;

    return &node->pair;
}
int lowerBound(int* nums, int size, int target, int left) {
    int right = size;

    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return right;
}
#endif
Router* routerCreate(int memoryLimit) {
    Router* pObj = NULL;

    pObj = (Router*)malloc(sizeof(Router));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->memoryLimit = memoryLimit;
    pObj->packetCount = 0;
    pObj->queue = malloc(sizeof(Packet) * memoryLimit);
    pObj->head = pObj->tail = 0;
    pObj->packetSet = packetSetCreate(PACKET_HASH_SIZE);
    pObj->destTable = calloc(DEST_HASH_SIZE, sizeof(DestNode*));

    return pObj;
}
int* routerForwardPacket(Router* obj, int* retSize) {
    int* pRetVal = NULL;

    (*retSize) = 0;
    if (obj->packetCount == 0) {
        return pRetVal;
    }

    Packet packet = obj->queue[obj->head];
    obj->head = (obj->head + 1) % obj->memoryLimit;
    obj->packetCount--;

    packetSetRemove(obj->packetSet, &packet);

    Pair* pair = getPair(obj, packet.destination);
    pair->head++;

    pRetVal = malloc(sizeof(int) * 3);
    pRetVal[0] = packet.source;
    pRetVal[1] = packet.destination;
    pRetVal[2] = packet.timestamp;
    (*retSize) = 3;

    return pRetVal;
}
bool routerAddPacket(Router* obj, int source, int destination, int timestamp) {
    bool retVal = false;

    Packet p = {source, destination, timestamp};

    if (packetSetContains(obj->packetSet, &p)) {
        return retVal;
    }

    if (obj->packetCount == obj->memoryLimit) {
        int retSize;
        int* ret = routerForwardPacket(obj, &retSize);
        free(ret);
        ret = NULL;
    }

    obj->queue[obj->tail] = p;
    obj->tail = (obj->tail + 1) % obj->memoryLimit;
    obj->packetCount++;

    packetSetAdd(obj->packetSet, &p);

    Pair* pair = getPair(obj, destination);
    if (pair->size == pair->capacity) {
        pair->capacity = pair->capacity == 0 ? 4 : pair->capacity * 2;
        pair->timestamps = realloc(pair->timestamps, sizeof(int) * pair->capacity);
    }
    pair->timestamps[pair->size++] = timestamp;

    retVal = true;

    return retVal;
}
int routerGetCount(Router* obj, int destination, int startTime, int endTime) {
    int retVal = 0;

    Pair* pair = getPair(obj, destination);
    if ((pair == NULL) || (pair->size == 0)) {
        return retVal;
    }
    int left = lowerBound(pair->timestamps, pair->size, startTime, pair->head);
    int right = lowerBound(pair->timestamps, pair->size, endTime + 1, pair->head);
    retVal = right - left;

    return retVal;
}
void routerFree(Router* obj) {
    free(obj->queue);
    packetSetFree(obj->packetSet);
    for (int i = 0; i < DEST_HASH_SIZE; i++) {
        DestNode* node = obj->destTable[i];
        while (node) {
            free(node->pair.timestamps);
            DestNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(obj->destTable);
    free(obj);
}
/**
 * Your Router struct will be instantiated and called as such:
 * Router* obj = routerCreate(memoryLimit);
 * bool param_1 = routerAddPacket(obj, source, destination, timestamp);
 * int* param_2 = routerForwardPacket(obj, retSize);
 * int param_3 = routerGetCount(obj, destination, startTime, endTime);
 * routerFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int memoryLimit[MAX_SIZE];
        int source[MAX_SIZE];
        int destination[MAX_SIZE];
        int timestamp[MAX_SIZE];
        int startTime[MAX_SIZE];
        int endTime[MAX_SIZE];
        int calls;
    } testCase[] = {{{"Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket",
                      "addPacket", "getCount"},
                     {3, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 2, 1, 3, 4, 0, 5, 0},
                     {0, 4, 5, 4, 5, 5, 0, 2, 5},
                     {0, 90, 90, 90, 95, 105, 0, 110, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 100},
                     {0, 0, 0, 0, 0, 0, 0, 0, 110},
                     9},
                    {{"Router", "addPacket", "forwardPacket", "forwardPacket"},
                     {2, 0, 0, 0},
                     {0, 7, 0, 0},
                     {0, 4, 0, 0},
                     {0, 90, 0, 0},
                     {0, 0, 0, 0},
                     {0, 0, 0, 0},
                     4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input:
     *  ["Router","addPacket","addPacket","addPacket","addPacket","addPacket","forwardPacket","addPacket","getCount"]
     *  [[3],[1,4,90],[2,5,90],[1,4,90],[3,5,95],[4,5,105],[],[5,2,110],[5,100,110]]
     *  Output:
     *  [null,true,true,false,true,true,[2,5,90],true,1]
     *
     *  Input:
     *  ["Router","addPacket","forwardPacket","forwardPacket"]
     *  [[2],[7,4,90],[],[]]
     *  Output:
     *  [null,true,[7,4,90],[]]
     */

    Router* obj = NULL;
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (int j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (int j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ", ");
            if (strcmp(testCase[i].methods[j], "Router") == 0) {
                printf("[%d]", testCase[i].memoryLimit[j]);
            } else if (strcmp(testCase[i].methods[j], "addPacket") == 0) {
                printf("[%d, %d, %d]", testCase[i].source[j], testCase[i].destination[j], testCase[i].timestamp[j]);
            } else if (strcmp(testCase[i].methods[j], "forwardPacket") == 0) {
                printf("[]");
            } else if (strcmp(testCase[i].methods[j], "getCount") == 0) {
                printf("[%d, %d, %d]", testCase[i].destination[j], testCase[i].startTime[j], testCase[i].endTime[j]);
            }
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (int j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ", ");
            if (strcmp(testCase[i].methods[j], "Router") == 0) {
                obj = routerCreate(testCase[i].memoryLimit[j]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "addPacket") == 0) {
                bool retVal =
                    routerAddPacket(obj, testCase[i].source[j], testCase[i].destination[j], testCase[i].timestamp[j]);
                printf("%s", (retVal == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "forwardPacket") == 0) {
                int retValSize = 0;
                int* retVal = routerForwardPacket(obj, &retValSize);
                printf("[");
                for (int k = 0; k < retValSize; ++k) {
                    printf("%s%d", (k == 0) ? "" : ",", retVal[k]);
                }
                printf("]");
                free(retVal);
                retVal = NULL;
            } else if (strcmp(testCase[i].methods[j], "getCount") == 0) {
                int retVal =
                    routerGetCount(obj, testCase[i].destination[j], testCase[i].startTime[j], testCase[i].endTime[j]);
                printf("%d", retVal);
            }
        }
        printf("]\n");

        routerFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
