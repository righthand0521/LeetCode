#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (16 + 4)  // 1 <= req_skills[i].length <= 16
struct hashStruct {
    char key[MAX_LENGTH];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct *pFree) {
    struct hashStruct *current;
    struct hashStruct *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *smallestSufficientTeam(char **req_skills, int req_skillsSize, char ***people, int peopleSize, int *peopleColSize,
                            int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    //
    struct hashStruct *pSkillIndex = NULL;
    struct hashStruct *pTemp;
    for (i = 0; i < req_skillsSize; ++i) {
        // All the strings of req_skills are unique.
        pTemp = (struct hashStruct *)malloc(sizeof(struct hashStruct));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(pSkillIndex);
            return pRetVal;
        }
        snprintf(pTemp->key, MAX_LENGTH, "%s", req_skills[i]);
        pTemp->value = i;
        HASH_ADD_STR(pSkillIndex, key, pTemp);
    }

    //
    int dpSize = (1 << req_skillsSize);
    int dp[dpSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for (i = 1; i < dpSize; ++i) {
        dp[i] = peopleSize;
    }

    //
    int curSkill, prev, comb;
    int prevSkillSize = (1 << req_skillsSize);
    int prevSkill[prevSkillSize];
    memset(prevSkill, 0, sizeof(prevSkill));
    int prevPeopleSize = (1 << req_skillsSize);
    int prevPeople[prevPeopleSize];
    memset(prevPeople, 0, sizeof(prevPeople));
    for (i = 0; i < peopleSize; ++i) {
        curSkill = 0;
        for (j = 0; j < peopleColSize[i]; ++j) {
            pTemp = NULL;
            HASH_FIND_STR(pSkillIndex, people[i][j], pTemp);
            if (pTemp == NULL) {
                freeAll(pSkillIndex);
                return pRetVal;
            }
            curSkill |= (1 << pTemp->value);
        }

        for (prev = 0; prev < (1 << req_skillsSize); prev++) {
            comb = prev | curSkill;
            if (dp[comb] > dp[prev] + 1) {
                dp[comb] = dp[prev] + 1;
                prevSkill[comb] = prev;
                prevPeople[comb] = i;
            }
        }
    }

    //
    pRetVal = (int *)malloc(req_skillsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(pSkillIndex);
        return pRetVal;
    }
    memset(pRetVal, 0, (req_skillsSize * sizeof(int)));
    i = (1 << req_skillsSize) - 1;
    while (i > 0) {
        pRetVal[(*returnSize)++] = prevPeople[i];
        i = prevSkill[i];
    }
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    //
    freeAll(pSkillIndex);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE_REQ_SKILLS (16)     // 1 <= req_skills.length <= 16
#define MAX_SIZE_PEOPLE (60)         // 1 <= people.length <= 60
#define MAX_SIZE_PEOPLE_SKILLS (16)  // 0 <= people[i].length <= 16
    struct testCaseType {
        char *req_skills[MAX_SIZE_REQ_SKILLS];
        int req_skillsSize;
        char *people[MAX_SIZE_PEOPLE][MAX_SIZE_PEOPLE_SKILLS];
        int peopleSize;
        int peopleColSize[MAX_SIZE_PEOPLE_SKILLS];
        int returnSize;
    } testCase[] = {{{"java", "nodejs", "reactjs"}, 3, {{"java"}, {"nodejs"}, {"nodejs", "reactjs"}}, 3, {1, 1, 2}, 0},
                    {{"algorithms", "math", "java", "reactjs", "csharp", "aws"},
                     6,
                     {{"algorithms", "math", "java"},
                      {"algorithms", "math", "reactjs"},
                      {"java", "csharp", "aws"},
                      {"reactjs", "csharp"},
                      {"csharp", "math"},
                      {"aws", "java"}},
                     6,
                     {3, 3, 3, 2, 2, 2},
                     0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
     *  Output: [0,2]
     *
     *  Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
     *  people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],
     *  ["reactjs","csharp"],["csharp","math"],["aws","java"]]
     *  Output: [1,2]
     */

    char **pReqSkills = NULL;
    char ***pPeople = NULL;
    int *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: req_skills = [");
        for (j = 0; j < testCase[i].req_skillsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].req_skills[j]);
        }
        printf("], people = [");
        for (j = 0; j < testCase[i].peopleSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].peopleColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].people[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pReqSkills = (char **)malloc(testCase[i].req_skillsSize * sizeof(char *));
        if (pReqSkills == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pReqSkills, 0, (testCase[i].req_skillsSize * sizeof(char *)));
        memcpy(pReqSkills, testCase[i].req_skills, (testCase[i].req_skillsSize * sizeof(char *)));
        pPeople = (char ***)malloc(testCase[i].peopleSize * sizeof(char **));
        if (pPeople == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].peopleSize; ++j) {
            pPeople[j] = (char **)malloc(testCase[i].peopleColSize[j] * sizeof(char *));
            if (pPeople[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPeople[k]);
                    pPeople[k] = NULL;
                }
                free(pPeople);
                pPeople = NULL;
                return EXIT_FAILURE;
            }
            memset(pPeople[j], 0, (testCase[i].peopleColSize[j] * sizeof(char *)));
            memcpy(pPeople[j], testCase[i].people[j], (testCase[i].peopleColSize[j] * sizeof(char *)));
        }
        pAnswer = smallestSufficientTeam(pReqSkills, testCase[i].req_skillsSize, pPeople, testCase[i].peopleSize,
                                         testCase[i].peopleColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        free(pReqSkills);
        pReqSkills = NULL;
        for (j = 0; j < testCase[i].peopleSize; ++j) {
            free(pPeople[j]);
            pPeople[j] = NULL;
        }
        free(pPeople);
        pPeople = NULL;
    }

    return EXIT_SUCCESS;
}
