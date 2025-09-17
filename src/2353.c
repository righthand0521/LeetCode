#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int ratings;
    char *value;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;
Element *createElement(int ratings, char *value) {
    Element *obj = (Element *)malloc(sizeof(Element));
    obj->ratings = ratings;
    obj->value = value;
    return obj;
}
static bool less(const void *a, const void *b) {
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    if (e1->ratings == e2->ratings) {
        return strcmp(e1->value, e2->value) > 0;
    }
    return e1->ratings > e2->ratings;
}
static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b ^= *a;
        *a ^= *b;
        *b ^= *a;

        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) { memswap(&arr[i], &arr[j], sizeof(Element)); }
static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }
        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }
        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;
    return obj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
    // we need to alloc more space, just twice space size
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));
    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element *deQueue(PriorityQueue *obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element *e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;
    return e;
}
bool isEmpty(const PriorityQueue *obj) { return obj->queueSize == 0; }
Element *front(const PriorityQueue *obj) {
    if (obj->queueSize == 0) {
        return NULL;
    } else {
        return &obj->arr[0];
    }
}
void clear(PriorityQueue *obj) { obj->queueSize = 0; }
int size(const PriorityQueue *obj) { return obj->queueSize; }
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    free(obj);
}

#endif  // PRIORITY_QUEUE_H
#ifndef HASH_H
#define HASH_H

typedef struct {
    char *key;
    Element val;
    UT_hash_handle hh;
} HashFoodItem;
HashFoodItem *hashFindFoodItem(HashFoodItem **obj, char *key) {
    HashFoodItem *pEntry = NULL;
    HASH_FIND_STR(*obj, key, pEntry);
    return pEntry;
}
bool hashAddFoodItem(HashFoodItem **obj, char *key, int rating, char *cuisine) {
    if (hashFindFoodItem(obj, key)) {
        return false;
    }
    HashFoodItem *pEntry = (HashFoodItem *)malloc(sizeof(HashFoodItem));
    pEntry->key = key;
    pEntry->val.ratings = rating;
    pEntry->val.value = cuisine;
    HASH_ADD_STR(*obj, key, pEntry);
    return true;
}
bool hashSetFoodItem(HashFoodItem **obj, char *key, Element val) {
    HashFoodItem *pEntry = hashFindFoodItem(obj, key);
    if (!pEntry) {
        hashAddFoodItem(obj, key, val.ratings, val.value);
    } else {
        pEntry->val = val;
    }
    return true;
}
Element hashGetFoodItem(HashFoodItem **obj, char *key) {
    HashFoodItem *pEntry = hashFindFoodItem(obj, key);
    return pEntry->val;
}
void hashFoodFree(HashFoodItem **obj) {
    HashFoodItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

typedef struct {
    char *key;
    PriorityQueue *val;
    UT_hash_handle hh;
} HashRatingItem;
HashRatingItem *hashFindRatingItem(HashRatingItem **obj, char *key) {
    HashRatingItem *pEntry = NULL;
    HASH_FIND_STR(*obj, key, pEntry);
    return pEntry;
}
bool hashAddRatingItem(HashRatingItem **obj, char *key, int rating, char *food) {
    HashRatingItem *pEntry = hashFindRatingItem(obj, key);
    if (!pEntry) {
        pEntry = (HashRatingItem *)malloc(sizeof(HashRatingItem));
        pEntry->key = key;
        pEntry->val = createPriorityQueue(less);
        HASH_ADD_STR(*obj, key, pEntry);
    }
    Element e = {rating, food};
    enQueue(pEntry->val, &e);
    return true;
}
PriorityQueue *hashGetRatingItem(HashRatingItem **obj, char *key) {
    HashRatingItem *pEntry = hashFindRatingItem(obj, key);
    return pEntry->val;
}
void hashRatingFree(HashRatingItem **obj) {
    HashRatingItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        freeQueue(curr->val);
        free(curr);
    }
}

#endif  // HASH_H
typedef struct {
    HashFoodItem *foodMap;
    HashRatingItem *ratingMap;
    int n;
} FoodRatings;
FoodRatings *foodRatingsCreate(char **foods, int foodsSize, char **cuisines, int cuisinesSize, int *ratings,
                               int ratingsSize) {
    FoodRatings *pObj = NULL;

    pObj = (FoodRatings *)malloc(sizeof(FoodRatings));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->n = foodsSize;
    pObj->foodMap = NULL;
    pObj->ratingMap = NULL;
    for (int i = 0; i < foodsSize; ++i) {
        char *food = foods[i], *cuisine = cuisines[i];
        int rating = ratings[i];
        hashAddFoodItem(&pObj->foodMap, food, rating, cuisine);
        hashAddRatingItem(&pObj->ratingMap, cuisine, pObj->n - rating, food);
    }

    return pObj;
}
void foodRatingsChangeRating(FoodRatings *obj, char *food, int newRating) {
    Element e = hashGetFoodItem(&obj->foodMap, food);

    char *cuisine = e.value;
    hashAddRatingItem(&obj->ratingMap, cuisine, obj->n - newRating, food);
    e.ratings = newRating;
    hashSetFoodItem(&obj->foodMap, food, e);
}
char *foodRatingsHighestRated(FoodRatings *obj, char *cuisine) {
    char *pRetVal = "";

    PriorityQueue *q = hashGetRatingItem(&obj->ratingMap, cuisine);
    while (isEmpty(q) == false) {
        int rating = front(q)->ratings;
        char *food = front(q)->value;
        if (obj->n - rating == hashGetFoodItem(&obj->foodMap, food).ratings) {
            pRetVal = food;
            break;
        }
        deQueue(q);
    }

    return pRetVal;
}
void foodRatingsFree(FoodRatings *obj) {
    hashFoodFree(&obj->foodMap);
    hashRatingFree(&obj->ratingMap);
    free(obj);
}
/**
 * Your FoodRatings struct will be instantiated and called as such:
 * FoodRatings* obj = foodRatingsCreate(foods, foodsSize, cuisines, cuisinesSize, ratings, ratingsSize);
 * foodRatingsChangeRating(obj, food, newRating);
 * char* param_2 = foodRatingsHighestRated(obj, cuisine);
 * foodRatingsFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char *methods;
        char *foods[MAX_SIZE];
        int foodsSize;
        char *cuisines[MAX_SIZE];
        int cuisinesSize;
        int ratings[MAX_SIZE];
        int ratingsSize;
    } testCase[] = {{"FoodRatings",
                     {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"},
                     6,
                     {"korean", "japanese", "japanese", "greek", "japanese", "korean"},
                     6,
                     {9, 12, 8, 15, 14, 7},
                     6},
                    {"highestRated", {}, 0, {"korean"}, 1, {}, 0},
                    {"highestRated", {}, 0, {"japanese"}, 1, {}, 0},
                    {"changeRating", {"sushi"}, 1, {}, 0, {16}, 1},
                    {"highestRated", {}, 0, {"japanese"}, 1, {}, 0},
                    {"changeRating", {"ramen"}, 1, {}, 0, {16}, 1},
                    {"highestRated", {}, 0, {"japanese"}, 1, {}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["FoodRatings", "highestRated", "highestRated", "changeRating", "highestRated", "changeRating", "highestRated"]
     *  [
     *      [
     *          ["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"],
     *          ["korean", "japanese", "japanese", "greek", "japanese", "korean"],
     *          [9, 12, 8, 15, 14, 7]
     *      ],
     *      ["korean"],
     *      ["japanese"],
     *      ["sushi", 16],
     *      ["japanese"],
     *      ["ramen", 16],
     *      ["japanese"]
     *  ]
     *  Output
     *  [null, "kimchi", "ramen", null, "sushi", null, "ramen"]
     */

    FoodRatings *obj = NULL;

    printf("Input\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("%s\"%s\"", (i == 0) ? "" : ", ", testCase[i].methods);
    }
    printf("]\n");
    printf("[\n");
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("\t[");
        if ((testCase[i].foodsSize > 0) && (testCase[i].cuisinesSize > 0) && (testCase[i].ratingsSize > 0)) {
            for (int j = 0; j < testCase[i].foodsSize; ++j) {
                printf("%s", (j == 0) ? "[" : "");
                printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].foods[j]);
                printf("%s", (j == testCase[i].foodsSize - 1) ? "], " : "");
            }
            for (int j = 0; j < testCase[i].cuisinesSize; ++j) {
                printf("%s", (j == 0) ? "[" : "");
                printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].cuisines[j]);
                printf("%s", (j == testCase[i].cuisinesSize - 1) ? "], " : "");
            }
            for (int j = 0; j < testCase[i].ratingsSize; ++j) {
                printf("%s", (j == 0) ? "[" : "");
                printf("%s%d", (j == 0) ? "" : ", ", testCase[i].ratings[j]);
                printf("%s", (j == testCase[i].ratingsSize - 1) ? "]" : "");
            }
        } else {
            if (testCase[i].foodsSize > 0) {
                for (int j = 0; j < testCase[i].foodsSize; ++j) {
                    printf("\"%s\"", testCase[i].foods[j]);
                }
            }
            if (testCase[i].cuisinesSize > 0) {
                for (int j = 0; j < testCase[i].cuisinesSize; ++j) {
                    printf("\"%s\"", testCase[i].cuisines[j]);
                }
            }
            if (testCase[i].ratingsSize > 0) {
                for (int j = 0; j < testCase[i].ratingsSize; ++j) {
                    printf(", \"%d\"", testCase[i].ratings[j]);
                }
            }
        }
        printf("]\n");
    }
    printf("]\n");

    printf("Output\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        if (strcmp(testCase[i].methods, "FoodRatings") == 0) {
            obj = foodRatingsCreate(testCase[i].foods, testCase[i].foodsSize, testCase[i].cuisines,
                                    testCase[i].cuisinesSize, testCase[i].ratings, testCase[i].ratingsSize);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "changeRating") == 0) {
            foodRatingsChangeRating(obj, testCase[i].foods[0], testCase[i].ratings[0]);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "highestRated") == 0) {
            char *ret = foodRatingsHighestRated(obj, testCase[i].cuisines[0]);
            printf("%s\"%s\"", (i == 0) ? "" : ", ", ret);
        }
    }
    printf("]\n");

    foodRatingsFree(obj);
    obj = NULL;

    return EXIT_SUCCESS;
}
