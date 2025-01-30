# [Graph](https://en.wikipedia.org/wiki/Graph_(discrete_mathematics))

- [Breadth-First Search](https://en.wikipedia.org/wiki/Breadth-first_search)
- [Depth-First Search](https://en.wikipedia.org/wiki/Depth-first_search)
- [Topological sorting](https://en.wikipedia.org/wiki/Topological_sorting)
- [Union Find](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)

## [2045. Second Minimum Time to Reach Destination](https://leetcode.com/problems/second-minimum-time-to-reach-destination/)  2201

- [Official](https://leetcode.com/problems/second-minimum-time-to-reach-destination/editorial/)
- [Official](https://leetcode.cn/problems/second-minimum-time-to-reach-destination/solutions/1228283/dao-da-mu-de-di-de-di-er-duan-shi-jian-b-05i0/)

<details><summary>Description</summary>

```text
A city is represented as a bi-directional connected graph with n vertices
where each vertex is labeled from 1 to n (inclusive).
The edges in the graph are represented as a 2D integer array edges,
where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi.
Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
The time taken to traverse any edge is time minutes.

Each vertex has a traffic signal which changes its color from green to red and vice versa every change minutes.
All signals change at the same time. You can enter a vertex at any time,
but can leave a vertex only when the signal is green.
You cannot wait at a vertex if the signal is green.

The second minimum value is defined as the smallest value strictly larger than the minimum value.
- For example the second minimum value of [2, 3, 4] is 3, and the second minimum value of [2, 2, 4] is 4.

Given n, edges, time, and change, return the second minimum time it will take to go from vertex 1 to vertex n.

Notes:
- You can go through any vertex any number of times, including 1 and n.
- You can assume that when the journey starts, all signals have just turned green.

Example 1:  
Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
Output: 13
Explanation:
The figure on the left shows the given graph.
The blue path in the figure on the right is the minimum time path.
The time taken is:
- Start at 1, time elapsed=0
- 1 -> 4: 3 minutes, time elapsed=3
- 4 -> 5: 3 minutes, time elapsed=6
Hence the minimum time needed is 6 minutes.
The red path shows the path to get the second minimum time.
- Start at 1, time elapsed=0
- 1 -> 3: 3 minutes, time elapsed=3
- 3 -> 4: 3 minutes, time elapsed=6
- Wait at 4 for 4 minutes, time elapsed=10
- 4 -> 5: 3 minutes, time elapsed=13
Hence the second minimum time is 13 minutes.

Example 2:
Input: n = 2, edges = [[1,2]], time = 3, change = 2
Output: 11
Explanation:
The minimum time path is 1 -> 2 with time = 3 minutes.
The second minimum time path is 1 -> 2 -> 1 -> 2 with time = 11 minutes.

Constraints:
2 <= n <= 10^4
n - 1 <= edges.length <= min(2 * 10^4, n * (n - 1) / 2)
edges[i].length == 2
1 <= ui, vi <= n
ui != vi
There are no duplicate edges.
Each vertex can be reached directly or indirectly from every other vertex.
1 <= time, change <= 10^3
```

<details><summary>Hint</summary>

```text
1. How much is change actually necessary while calculating the required path?
2. How many extra edges do we need to add to the shortest path?
```

</details>

</details>

<details><summary>C</summary>

```c
struct Node {
    int val;
    struct Node *next;
};
int pushNode(struct Node **pObj, int value) {
    int retVal = EXIT_SUCCESS;

    struct Node *pNode = (struct Node *)malloc(sizeof(struct Node));
    if (pNode == NULL) {
        perror("malloc");
        retVal = EXIT_FAILURE;
        return retVal;
    }
    pNode->val = value;
    pNode->next = (*pObj);

    (*pObj) = pNode;

    return retVal;
}
void freeNode(struct Node *pObj) {
    struct Node *pFree;
    while (pObj != NULL) {
        pFree = pObj;
        pObj = pObj->next;
        free(pFree);
        pFree = NULL;
    }
}
int secondMinimum(int n, int **edges, int edgesSize, int *edgesColSize, int time, int change) {
    int retVal = 0;

    int i;

    //
    int pAdjacencySize = n + 1;
    struct Node **pAdjacency = (struct Node **)malloc(pAdjacencySize * sizeof(struct Node *));
    if (pAdjacency == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pAdjacency, 0, (pAdjacencySize * sizeof(struct Node *)));
    int ret;
    for (i = 0; i < edgesSize; i++) {
        ret = pushNode(&pAdjacency[edges[i][0]], edges[i][1]);
        if (ret == EXIT_FAILURE) {
            goto exit_pAdjacency;
        }

        ret = pushNode(&pAdjacency[edges[i][1]], edges[i][0]);
        if (ret == EXIT_FAILURE) {
            goto exit_pAdjacency;
        }
    }

    //
    int pPathSize = 2 * n + 1;
    int *pPath = (int *)malloc(pPathSize * sizeof(int));
    if (pPath == NULL) {
        perror("malloc");
        goto exit_pAdjacency;
    }
    memset(pPath, 0, (pPathSize * sizeof(int)));
    for (i = 1; i <= n; i++) {
        pPath[i] = INT_MAX;
        pPath[i + n] = INT_MAX;
    }
    pPath[1] = 0;

    //
    struct Pair {
        int node;
        int len;
    };
    int pBfsQueueSize = 2 * n + 1;
    struct Pair *pBfsQueue = (struct Pair *)malloc(pBfsQueueSize * sizeof(struct Pair));
    if (pPath == NULL) {
        perror("malloc");
        goto exit_pPath;
    }
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    pBfsQueue[bfsQueueTail].node = 1;
    pBfsQueue[bfsQueueTail++].len = 0;

    //
    struct Node *pCurrent;
    int node, len;
    while (pPath[n + n] == INT_MAX) {
        node = pBfsQueue[bfsQueueHead].node;
        len = pBfsQueue[bfsQueueHead++].len;

        pCurrent = pAdjacency[node];
        while (pCurrent != NULL) {
            if (len + 1 < pPath[pCurrent->val]) {
                pPath[pCurrent->val] = len + 1;
                pBfsQueue[bfsQueueTail].node = pCurrent->val;
                pBfsQueue[bfsQueueTail++].len = len + 1;
            } else if ((len + 1 > pPath[pCurrent->val]) && (len + 1 < pPath[pCurrent->val + n])) {
                pPath[pCurrent->val + n] = len + 1;
                pBfsQueue[bfsQueueTail].node = pCurrent->val;
                pBfsQueue[bfsQueueTail++].len = len + 1;
            }

            pCurrent = pCurrent->next;
        }
    }

    //
    for (i = 0; i < pPath[n + n]; i++) {
        if (retVal % (2 * change) >= change) {
            retVal = retVal + 2 * change - retVal % (2 * change);
        }

        retVal += time;
    }

    //
    free(pBfsQueue);
    pBfsQueue = NULL;

exit_pPath:
    free(pPath);
    pPath = NULL;

exit_pAdjacency:
    for (i = 1; i <= n; i++) {
        freeNode(pAdjacency[i]);
        pAdjacency[i] = NULL;
    }
    free(pAdjacency);
    pAdjacency = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        int retVal = 0;

        //
        vector<vector<int>> adjacency(n + 1);
        for (auto& edge : edges) {
            adjacency[edge[0]].emplace_back(edge[1]);
            adjacency[edge[1]].emplace_back(edge[0]);
        }

        //
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({1, 1});

        vector<int> dist1(n + 1, -1);
        dist1[1] = 0;

        vector<int> dist2(n + 1, -1);

        //
        while (bfsQueue.empty() == false) {
            auto [node, frequency] = bfsQueue.front();
            bfsQueue.pop();

            // If the timeTaken falls under the red bracket, wait till the path turns green.
            int timeTaken = ((frequency == 1) ? (dist1[node]) : (dist2[node]));
            if ((timeTaken / change) % 2) {
                timeTaken = change * (timeTaken / change + 1) + time;
            } else {
                timeTaken = timeTaken + time;
            }

            for (auto& neighbor : adjacency[node]) {
                if (dist1[neighbor] == -1) {
                    dist1[neighbor] = timeTaken;
                    bfsQueue.push({neighbor, 1});
                } else if ((dist2[neighbor] == -1) && (dist1[neighbor] != timeTaken)) {
                    if (neighbor == n) {
                        retVal = timeTaken;
                        return retVal;
                    }
                    dist2[neighbor] = timeTaken;
                    bfsQueue.push({neighbor, 2});
                }
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def secondMinimum(self, n: int, edges: List[List[int]], time: int, change: int) -> int:
        retVal = 0

        #
        adjacencyList = [[] for _ in range(n + 1)]
        for start, end in edges:
            adjacencyList[start].append(end)
            adjacencyList[end].append(start)

        #
        bfsQueue = deque()
        bfsQueue.append((1, 1))

        dist1 = [-1] * (n + 1)
        dist1[1] = 0

        dist2 = [-1] * (n + 1)

        #
        while bfsQueue:
            node, frequency = bfsQueue.popleft()

            # If the timeTaken falls under the red bracket, wait till the path turns green.
            timeTaken = dist1[node] if frequency == 1 else dist2[node]
            if (timeTaken // change) % 2:
                timeTaken = change * (timeTaken // change + 1) + time
            else:
                timeTaken = timeTaken + time

            for neighbor in adjacencyList[node]:
                if dist1[neighbor] == -1:
                    dist1[neighbor] = timeTaken
                    bfsQueue.append((neighbor, 1))
                elif (dist2[neighbor] == -1) and (dist1[neighbor] != timeTaken):
                    if neighbor == n:
                        retVal = timeTaken
                        return retVal
                    dist2[neighbor] = timeTaken
                    bfsQueue.append((neighbor, 2))

        return retVal
```

</details>

## [2050. Parallel Courses III](https://leetcode.com/problems/parallel-courses-iii/)  2084

- [Official](https://leetcode.com/problems/parallel-courses-iii/editorial/)
- [Official](https://leetcode.cn/problems/parallel-courses-iii/solutions/2357818/bing-xing-ke-cheng-iii-by-leetcode-solut-aw43/)

<details><summary>Description</summary>

```text
You are given an integer n, which indicates that there are n courses labeled from 1 to n.
You are also given a 2D integer array relations where relations[j] = [prevCoursej,
nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship).
Furthermore, you are given a 0-indexed integer array time
where time[i] denotes how many months it takes to complete the (i+1)th course.

You must find the minimum number of months needed to complete all the courses following these rules:
- You may start taking a course at any time if the prerequisites are met.
- Any number of courses can be taken at the same time.

Return the minimum number of months needed to complete all the courses.

Note: The test cases are generated such that it is possible to complete every course
(i.e., the graph is a directed acyclic graph).

Example 1:
Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
Output: 8
Explanation: The figure above represents the given graph and the time required to complete each course.
We start course 1 and course 2 simultaneously at month 0.
Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.

Example 2:
Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
Output: 12
Explanation: The figure above represents the given graph and the time required to complete each course.
You can start courses 1, 2, and 3 at month 0.
You can complete them after 1, 2, and 3 months respectively.
Course 4 can be taken only after course 3 is completed, i.e., after 3 months. It is completed after 3 + 4 = 7 months.
Course 5 can be taken only after courses 1, 2, 3, and 4 have been completed, i.e., after max(1,2,3,7) = 7 months.
Thus, the minimum time needed to complete all the courses is 7 + 5 = 12 months.

Constraints:
1 <= n <= 5 * 10^4
0 <= relations.length <= min(n * (n - 1) / 2, 5 * 10^4)
relations[j].length == 2
1 <= prevCoursej, nextCoursej <= n
prevCoursej != nextCoursej
All the pairs [prevCoursej, nextCoursej] are unique.
time.length == n
1 <= time[i] <= 10^4
The given graph is a directed acyclic graph.
```

<details><summary>Hint</summary>

```text
1. What is the earliest time a course can be taken?
2. How would you solve the problem if all courses take equal time?
3. How would you generalize this approach?
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumTime(int n, int** relations, int relationsSize, int* relationsColSize, int* time, int timeSize) {
    int retVal = 0;

    int i;

    //
    int count[n + 1];
    memset(count, 0, sizeof(count));
    for (i = 0; i < relationsSize; ++i) {
        count[relations[i][0]]++;
    }
    int graphMaxSize = 1;
    for (i = 0; i <= n; ++i) {
        graphMaxSize = fmax(graphMaxSize, count[i]);
    }

    int graph[n][graphMaxSize];
    memset(graph, -1, sizeof(graph));
    int graphColSize[n];
    memset(graphColSize, 0, sizeof(graphColSize));

    int indegree[n];
    memset(indegree, 0, sizeof(indegree));

    int x, y;
    for (i = 0; i < relationsSize; ++i) {
        x = relations[i][0] - 1;
        y = relations[i][1] - 1;
        graph[x][graphColSize[x]++] = y;
        indegree[y]++;
    }
#if (0)
    printf("indegree: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", indegree[i]);
    }
    printf("\n");
    for (i = 0; i < n; ++i) {
        printf("graph[%d]: ", i);
        for (int j = 0; j < graphColSize[i]; ++j) {
            printf("%2d ", graph[i][j]);
        }
        printf(": %d\n", graphColSize[i]);
    }
#endif

    //
    int maxTime[n];
    memset(maxTime, 0, sizeof(maxTime));

#define MAX_QUEUE_SIZE ((n)*2)
    int topologicalSortQueueHead = 0;
    int topologicalSortQueueTail = 0;
    int topologicalSortQueue[MAX_QUEUE_SIZE];

    for (i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            topologicalSortQueue[topologicalSortQueueTail++] = i;
            maxTime[i] = time[i];
        }
    }
#if (0)
    printf("maxTime: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", maxTime[i]);
    }
    printf("\n");
    for (i = 0; i < (topologicalSortQueueTail - topologicalSortQueueHead); ++i) {
        printf("%d ", topologicalSortQueue[i]);
    }
    printf("\n");
#endif

    // Topological Sort Using Kahn's Algorithm
    int node, neighbor;
    while (topologicalSortQueueHead < topologicalSortQueueTail) {
        node = topologicalSortQueue[topologicalSortQueueHead++];

        for (i = 0; i < graphColSize[node]; ++i) {
            neighbor = graph[node][i];

            maxTime[neighbor] = fmax(maxTime[neighbor], maxTime[node] + time[neighbor]);
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                topologicalSortQueue[topologicalSortQueueTail++] = neighbor;
            }
        }
    }

    for (i = 0; i < n; i++) {
        retVal = fmax(retVal, maxTime[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        int retVal = 0;

        unordered_map<int, vector<int>> graph;
        vector<int> indegree(n, 0);
        for (vector<int>& edge : relations) {
            int x = edge[0] - 1;
            int y = edge[1] - 1;
            graph[x].push_back(y);
            indegree[y]++;
        }

        queue<int> topologicalSortQueue;
        vector<int> maxTime(n, 0);
        for (int node = 0; node < n; node++) {
            if (indegree[node] == 0) {
                topologicalSortQueue.push(node);
                maxTime[node] = time[node];
            }
        }

        // Topological Sort Using Kahn's Algorithm
        while (topologicalSortQueue.empty() == false) {
            int node = topologicalSortQueue.front();
            topologicalSortQueue.pop();
            for (int neighbor : graph[node]) {
                maxTime[neighbor] = max(maxTime[neighbor], maxTime[node] + time[neighbor]);
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    topologicalSortQueue.push(neighbor);
                }
            }
        }

        for (int node = 0; node < n; node++) {
            retVal = max(retVal, maxTime[node]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumTime(self, n: int, relations: List[List[int]], time: List[int]) -> int:
        retVal = 0

        graph = defaultdict(list)
        indegree = [0] * n
        for (x, y) in relations:
            graph[x - 1].append(y - 1)
            indegree[y - 1] += 1

        topologicalSortQueue = deque()
        max_time = [0] * n
        for node in range(n):
            if indegree[node] == 0:
                topologicalSortQueue.append(node)
                max_time[node] = time[node]

        # Topological Sort Using Kahn's Algorithm
        while topologicalSortQueue:
            node = topologicalSortQueue.popleft()
            for neighbor in graph[node]:
                max_time[neighbor] = max(max_time[neighbor], max_time[node] + time[neighbor])
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    topologicalSortQueue.append(neighbor)

        retVal = max(max_time)

        return retVal
```

</details>

## [2092. Find All People With Secret](https://leetcode.com/problems/find-all-people-with-secret/)  2003

- [Official](https://leetcode.com/problems/find-all-people-with-secret/editorial/)
- [Official](https://leetcode.cn/problems/find-all-people-with-secret/solutions/1127118/zhao-chu-zhi-xiao-mi-mi-de-suo-you-zhuan-fzxf/)

<details><summary>Description</summary>

```text
You are given an integer n indicating there are n people numbered from 0 to n - 1.
You are also given a 0-indexed 2D integer array meetings
where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei.
A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.

Person 0 has a secret and initially shares the secret with a person firstPerson at time 0.
This secret is then shared every time a meeting takes place with a person that has the secret.
More formally, for every meeting, if a person xi has the secret at timei,
then they will share the secret with person yi, and vice versa.

The secrets are shared instantaneously.
That is, a person may receive the secret and share it with people in other meetings within the same time frame.

Return a list of all the people that have the secret after all the meetings have taken place.
You may return the answer in any order.

Example 1:
Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
Output: [0,1,2,3,5]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 5, person 1 shares the secret with person 2.
At time 8, person 2 shares the secret with person 3.
At time 10, person 1 shares the secret with person 5.​​​​
Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.

Example 2:
Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
Output: [0,1,3]
Explanation:
At time 0, person 0 shares the secret with person 3.
At time 2, neither person 1 nor person 2 know the secret.
At time 3, person 3 shares the secret with person 0 and person 1.
Thus, people 0, 1, and 3 know the secret after all the meetings.

Example 3:
Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
Output: [0,1,2,3,4]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
Note that person 2 can share the secret at the same time as receiving it.
At time 2, person 3 shares the secret with person 4.
Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.

Constraints:
2 <= n <= 10^5
1 <= meetings.length <= 10^5
meetings[i].length == 3
0 <= xi, yi <= n - 1
xi != yi
1 <= timei <= 10^5
1 <= firstPerson <= n - 1
```

<details><summary>Hint</summary>

```text
1. Could you model all the meetings happening at the same time as a graph?
2. What data structure can you use to efficiently share the secret?
3. You can use the union-find data structure to quickly determine who knows the secret and share the secret.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    return (p1[2] > p2[2]);
}
void GetResult(int** meetings, int start, int num, int* returnValue, int* returnSize, int* flag) {
    int people;
    int i;
    int rule = 1;
    while (rule > 0) {
        rule = 0;
        for (i = 0; i < num; i++) {
            if (flag[meetings[i + start][0]] != flag[meetings[i + start][1]]) {
                people = flag[meetings[i + start][0]] ? meetings[i + start][1] : meetings[i + start][0];
                returnValue[(*returnSize)++] = people;
                flag[people] = 1;
                rule = 1;
            }
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAllPeople(int n, int** meetings, int meetingsSize, int* meetingsColSize, int firstPerson, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));
    pRetVal[0] = 0;
    pRetVal[1] = firstPerson;
    (*returnSize) = 2;

    //
    qsort(meetings, meetingsSize, sizeof(int*), compareIntArray);

    //
    int* flag = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(flag, 0, (n * sizeof(int)));
    flag[0] = 1;
    flag[firstPerson] = 1;

    int people;
    int start = 0;
    int num = 0;
    int i;
    for (i = 0; i < meetingsSize; i++) {
        if ((i > 0) && (meetings[i][2] != meetings[i - 1][2])) {
            start = i;
            num = 1;
        } else {
            num++;
        }

        if (flag[meetings[i][0]] != flag[meetings[i][1]]) {
            people = flag[meetings[i][0]] ? meetings[i][1] : meetings[i][0];
            pRetVal[(*returnSize)] = people;
            (*returnSize)++;
            flag[people] = 1;
        }

        if (((i < (meetingsSize - 1)) && (meetings[i][2] != meetings[i + 1][2])) || (i == (meetingsSize - 1))) {
            GetResult(meetings, start, num, pRetVal, returnSize, flag);
        }
    }

    //
    free(flag);
    flag = NULL;

    //
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> retVal;

        //
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& meeting : meetings) {
            int x = meeting[0];
            int y = meeting[1];
            int t = meeting[2];
            graph[x].emplace_back(t, y);
            graph[y].emplace_back(t, x);
        }

        //
        int secretDefaultValue = std::numeric_limits<int>::max();
        vector<int> secret(n, secretDefaultValue);
        secret[0] = 0;
        secret[firstPerson] = 0;

        //
        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(0, 0);
        bfsQueue.emplace(firstPerson, 0);
        while (bfsQueue.empty() == false) {
            auto [person, time] = bfsQueue.front();
            bfsQueue.pop();
            for (auto [t, nextPerson] : graph[person]) {
                if ((t >= time) && (secret[nextPerson] > t)) {
                    secret[nextPerson] = t;
                    bfsQueue.emplace(nextPerson, t);
                }
            }
        }

        //
        for (int i = 0; i < n; ++i) {
            if (secret[i] != secretDefaultValue) {
                retVal.push_back(i);
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findAllPeople(self, n: int, meetings: List[List[int]], firstPerson: int) -> List[int]:
        retVal = []

        #
        graph = defaultdict(list)
        for x, y, t in meetings:
            graph[x].append((t, y))
            graph[y].append((t, x))

        #
        secretDefaultValue = float('inf')
        secret = [secretDefaultValue] * n
        secret[0] = 0
        secret[firstPerson] = 0

        #
        bfsQueue = deque()
        bfsQueue.append((0, 0))
        bfsQueue.append((firstPerson, 0))
        while bfsQueue:
            person, time = bfsQueue.popleft()
            for t, nextPerson in graph[person]:
                if t >= time and secret[nextPerson] > t:
                    secret[nextPerson] = t
                    bfsQueue.append((nextPerson, t))

        #
        for i in range(n):
            if secret[i] != secretDefaultValue:
                retVal.append(i)

        return retVal
```

</details>

## [2097. Valid Arrangement of Pairs](https://leetcode.com/problems/valid-arrangement-of-pairs/)  2650

- [Official](https://leetcode.com/problems/valid-arrangement-of-pairs/editorial/)
- [Official](https://leetcode.cn/problems/valid-arrangement-of-pairs/solutions/1140776/he-fa-zhong-xin-pai-lie-shu-dui-by-leetc-h8rl/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi].
An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.

Return any valid arrangement of pairs.

Note: The inputs will be generated such that there exists a valid arrangement of pairs.

Example 1:
Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
Output: [[11,9],[9,4],[4,5],[5,1]]
Explanation:
This is a valid arrangement since endi-1 always equals starti.
end0 = 9 == 9 = start1
end1 = 4 == 4 = start2
end2 = 5 == 5 = start3

Example 2:
Input: pairs = [[1,3],[3,2],[2,1]]
Output: [[1,3],[3,2],[2,1]]
Explanation:
This is a valid arrangement since endi-1 always equals starti.
end0 = 3 == 3 = start1
end1 = 2 == 2 = start2
The arrangements [[2,1],[1,3],[3,2]] and [[3,2],[2,1],[1,3]] are also valid.

Example 3:
Input: pairs = [[1,2],[1,3],[2,1]]
Output: [[1,2],[2,1],[1,3]]
Explanation:
This is a valid arrangement since endi-1 always equals starti.
end0 = 2 == 2 = start1
end1 = 1 == 1 = start2

Constraints:
1 <= pairs.length <= 10^5
pairs[i].length == 2
0 <= starti, endi <= 10^9
starti != endi
No two pairs are exactly the same.
There exists a valid arrangement of pairs.
```

<details><summary>Hint</summary>

```text
1. Could you convert this into a graph problem?
2. Consider the pairs as edges and each number as a node.
3. We have to find an Eulerian path of this graph. Hierholzer’s algorithm can be used.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/valid-arrangement-of-pairs/solutions/1175305/qing-cha-shou-ben-ti-de-di-yi-ge-cyu-yan-sru0/
struct hashTable {
    int key;
    int id;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->id);
        HASH_DEL(pFree, current);
        free(current);
    }
}
void dfs(int x, int **edges, int **edgesColSize, int **answer, int *answerSize) {
    int y;
    while ((*edgesColSize)[x] > 0) {
        y = edges[x][(*edgesColSize)[x] - 1];
        (*edgesColSize)[x]--;

        dfs(y, edges, edgesColSize, answer, answerSize);

        answer[(*answerSize)][0] = x;
        answer[(*answerSize)][1] = y;
        (*answerSize)++;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **validArrangement(int **pairs, int pairsSize, int *pairsColSize, int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j;

    //
    (*returnColumnSizes) = (int *)calloc(pairsSize, sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal = (int **)malloc(sizeof(int *) * pairsSize);
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_returnColumnSizes;
    }
    for (i = 0; i < pairsSize; ++i) {
        (*returnColumnSizes)[i] = 2;
        pRetVal[i] = (int *)calloc((*returnColumnSizes)[i], sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            goto exit_returnSize;
        }
    }

    //
    int *basicSize = (int *)calloc((pairsSize + 1), sizeof(int));
    if (basicSize == NULL) {
        perror("calloc");
        goto exit_returnSize;
    }
    int *edgesColSize = (int *)calloc((pairsSize + 1), sizeof(int));
    if (edgesColSize == NULL) {
        perror("calloc");
        goto exit_basicSize;
    }
    int **edges = (int **)malloc((pairsSize + 1) * sizeof(int *));
    if (edges == NULL) {
        perror("calloc");
        goto exit_edgesColSize;
    }
    for (i = 0; i < pairsSize + 1; i++) {
        edgesColSize[i] = 0;
        basicSize[i] = 8;
        edges[i] = (int *)calloc(basicSize[i], sizeof(int));
        if (edges[i] == NULL) {
            perror("calloc");
            goto exit_edges;
        }
    }
    //
    int *inDegree = (int *)calloc((pairsSize + 1), sizeof(int));
    if (inDegree == NULL) {
        perror("calloc");
        goto exit_edges;
    }
    int *outDegree = (int *)calloc((pairsSize + 1), sizeof(int));
    if (outDegree == NULL) {
        perror("calloc");
        goto exit_inDegree;
    }
    int *sign = (int *)calloc((pairsSize + 1), sizeof(int));
    if (sign == NULL) {
        perror("calloc");
        goto exit_outDegree;
    }
    //

    struct hashTable *pUser = NULL;
    struct hashTable *pTmp;
    int x, y, indexX, indexY;
    int count = 0;
    for (j = 0; j < pairsSize; ++j) {
        x = pairs[j][0];
        y = pairs[j][1];

        pTmp = NULL;
        HASH_FIND_INT(pUser, &x, pTmp);
        if (pTmp == NULL) {
            indexX = count;
            sign[indexX] = x;
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit_hashTable;
            }
            pTmp->key = x;
            pTmp->id = count++;
            HASH_ADD_INT(pUser, key, pTmp);
        } else {
            indexX = pTmp->id;
        }

        pTmp = NULL;
        HASH_FIND_INT(pUser, &y, pTmp);
        if (pTmp == NULL) {
            indexY = count;
            sign[indexY] = y;
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit_hashTable;
            }
            pTmp->key = y;
            pTmp->id = count++;
            HASH_ADD_INT(pUser, key, pTmp);
        } else {
            indexY = pTmp->id;
        }

        outDegree[indexX]++;
        inDegree[indexY]++;
        edgesColSize[indexX]++;
        if (edgesColSize[indexX] == basicSize[indexX]) {
            basicSize[indexX] *= 2;
            edges[indexX] = (int *)realloc(edges[indexX], basicSize[indexX] * sizeof(int));
            if (edges[indexX] == NULL) {
                perror("realloc");
                goto exit_hashTable;
            }
        }
        edges[indexX][edgesColSize[indexX] - 1] = indexY;
    }

    int start = 0;
    for (j = 0; j < count; ++j) {
        if (inDegree[j] == outDegree[j] - 1) {
            start = j;
        }
    }

    dfs(start, edges, &edgesColSize, pRetVal, returnSize);

    int temp0, temp1;
    for (j = 0; j < (*returnSize) / 2; ++j) {
        temp0 = pRetVal[j][0];
        temp1 = pRetVal[j][1];

        pRetVal[j][0] = sign[pRetVal[(*returnSize) - j - 1][0]];
        pRetVal[j][1] = sign[pRetVal[(*returnSize) - j - 1][1]];

        pRetVal[(*returnSize) - j - 1][0] = sign[temp0];
        pRetVal[(*returnSize) - j - 1][1] = sign[temp1];
    }

    if ((*returnSize) % 2 == 1) {
        j = (*returnSize) / 2;
        pRetVal[j][0] = sign[pRetVal[j][0]];
        pRetVal[j][1] = sign[pRetVal[j][1]];
    }

    (*returnSize) = pairsSize;

exit_hashTable:
    freeAll(pUser);
    pUser = NULL;
    // exit_sign:
    free(sign);
    sign = NULL;
exit_outDegree:
    free(outDegree);
    outDegree = NULL;
exit_inDegree:
    free(inDegree);
    inDegree = NULL;
exit_edges:
    for (j = 0; j < i; ++j) {
        free(edges[j]);
        edges[j] = NULL;
    }
    i = pairsSize;
    free(edges);
    edges = NULL;
exit_edgesColSize:
    free(edgesColSize);
    edgesColSize = NULL;
exit_basicSize:
    free(basicSize);
    basicSize = NULL;
exit_returnSize:
    if ((*returnSize) == 0) {
        for (j = 0; j < i; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
    }
exit_returnColumnSizes:
    if ((*returnSize) == 0) {
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        vector<vector<int>> retVal;

        // Build the adjacency list and track in-degrees and out-degrees
        unordered_map<int, deque<int>> adjacencyMatrix;
        unordered_map<int, int> inDegree;
        unordered_map<int, int> outDegree;
        for (const auto& pair : pairs) {
            int start = pair[0];
            int end = pair[1];
            adjacencyMatrix[start].push_back(end);
            outDegree[start]++;
            inDegree[end]++;
        }

        // Find the start node (outDegree == inDegree + 1)
        int startNode = -1;
        for (const auto& entry : outDegree) {
            int node = entry.first;
            if (outDegree[node] == inDegree[node] + 1) {
                startNode = node;
                break;
            }
        }
        if (startNode == -1) {  // If no such node exists, start from the first pair's first element
            startNode = pairs[0][0];
        }

        vector<int> result;
        // Iterative DFS using stack
        stack<int> nodeStack;
        nodeStack.push(startNode);
        while (nodeStack.empty() == false) {
            int node = nodeStack.top();
            if (adjacencyMatrix[node].empty() == false) {  // Visit the next node
                int nextNode = adjacencyMatrix[node].front();
                adjacencyMatrix[node].pop_front();
                nodeStack.push(nextNode);
            } else {  // No more neighbors to visit, add node to result
                result.push_back(node);
                nodeStack.pop();
            }
        }
        reverse(result.begin(), result.end());  // Reverse the result since we collected nodes in reverse order

        // Construct the result pairs
        int resultSize = result.size();
        for (int i = 1; i < resultSize; ++i) {
            retVal.push_back({result[i - 1], result[i]});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        retVal = []

        # Build the adjacency list and track in-degrees and out-degrees
        adjacencyMatrix = defaultdict(list)
        inDegree = defaultdict(int)
        outDegree = defaultdict(int)
        for start, end in pairs:
            adjacencyMatrix[start].append(end)
            outDegree[start] += 1
            inDegree[end] += 1

        # Find the start node (outDegree == inDegree + 1)
        startNode = -1
        for node in outDegree:
            if outDegree[node] == inDegree[node] + 1:
                startNode = node
                break
        if startNode == -1:  # If no such node exists, start from the first pair's first element
            startNode = pairs[0][0]

        result = []
        # Iterative DFS using stack
        nodeStack = [startNode]
        while nodeStack:
            node = nodeStack[-1]
            if adjacencyMatrix[node]:  # Visit the next node
                nextNode = adjacencyMatrix[node].pop(0)
                nodeStack.append(nextNode)
            else:  # No more neighbors to visit, add node to result
                result.append(node)
                nodeStack.pop()
        result.reverse()  # Reverse the result since we collected nodes in reverse order

        # Construct the result pairs
        for i in range(1, len(result)):
            retVal.append([result[i - 1], result[i]])

        return retVal
```

</details>

## [2101. Detonate the Maximum Bombs](https://leetcode.com/problems/detonate-the-maximum-bombs/)  1880

- [Official](https://leetcode.com/problems/detonate-the-maximum-bombs/editorial/)
- [Official](https://leetcode.cn/problems/detonate-the-maximum-bombs/solutions/1153683/yin-bao-zui-duo-de-zha-dan-by-leetcode-s-iccp/)

<details><summary>Description</summary>

```text
You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt.
This area is in the shape of a circle with the center as the location of the bomb.

The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri].
xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb,
whereas ri denotes the radius of its range.

You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range.
These bombs will further detonate the bombs that lie in their ranges.

Given the list of bombs,
return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.

Example 1:
Input: bombs = [[2,1,3],[6,1,4]]
Output: 2
Explanation:
The above figure shows the positions and ranges of the 2 bombs.
If we detonate the left bomb, the right bomb will not be affected.
But if we detonate the right bomb, both bombs will be detonated.
So the maximum bombs that can be detonated is max(1, 2) = 2.

Example 2:
Input: bombs = [[1,1,5],[10,10,5]]
Output: 1
Explanation:
Detonating either bomb will not detonate the other bomb, so the maximum number of bombs that can be detonated is 1.

Example 3:
Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
Output: 5
Explanation:
The best bomb to detonate is bomb 0 because:
- Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb 0.
- Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
- Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.
Thus all 5 bombs are detonated.

Constraints:
1 <= bombs.length <= 100
bombs[i].length == 3
1 <= xi, yi, ri <= 10^5
```

<details><summary>Hint</summary>

```text
1. How can we model the relationship between different bombs? Can "graphs" help us?
2. Bombs are nodes and are connected to other bombs in their range by directed edges.
3. If we know which bombs will be affected when any bomb is detonated,
   how can we find the total number of bombs that will be detonated if we start from a fixed bomb?
4. Run a Depth First Search (DFS) from every node, and all the nodes it reaches are the bombs that will be detonated.
```

</details>

</details>

<details><summary>C</summary>

```c
#define DFS (0)
#define BFS (1)
int bfs(int node, int** edges, int* edgesColSize, int bombsSize) {
    int retVal = 0;

    int visited[bombsSize];
    memset(visited, 0, sizeof(visited));
    visited[node] = 1;
    int bfsQueue[bombsSize * bombsSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = node;
    ++retVal;

    int i;
    int current;
    while (bfsQueueHead > bfsQueueTail) {
        current = bfsQueue[bfsQueueTail];
        ++bfsQueueTail;
        for (i = 0; i < edgesColSize[current]; ++i) {
            if (visited[edges[current][i]] == 1) {
                continue;
            }
            visited[edges[current][i]] = 1;
            bfsQueue[bfsQueueHead++] = edges[current][i];
            ++retVal;
        }
    }

    return retVal;
}
int maximumDetonation(int** bombs, int bombsSize, int* bombsColSize) {
    int retVal = 0;

    int i, j;

    //
    int** edges = (int**)malloc(bombsSize * sizeof(int*));
    if (edges == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < bombsSize; ++i) {
        edges[i] = (int*)malloc(bombsSize * sizeof(int));
        if (edges[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(edges[j]);
                edges[j] = NULL;
            }
            free(edges);
            edges = NULL;
            return retVal;
        }
        memset(edges[i], 0, (bombsSize * sizeof(int)));
    }
    int edgesColSize[bombsSize];
    memset(edgesColSize, 0, sizeof(edgesColSize));
    for (i = 0; i < bombsSize; ++i) {
        for (j = 0; j < bombsSize; ++j) {
            if (i == j) {
                continue;
            }

            // 1 <= xi, yi, ri <= 10^5
            long long dx = bombs[i][0] - bombs[j][0];
            long long dy = bombs[i][1] - bombs[j][1];
            long long dr = (dx * dx) + (dy * dy);
            long long r = (long long)bombs[i][2] * (long long)bombs[i][2];
            if (r >= dr) {
                edges[i][edgesColSize[i]++] = j;
            }
        }
    }
#if 0  // graph print
    for (i = 0; i < bombsSize; ++i) {
        printf("%d: ", i);
        for (j = 0; j < bombsSize; ++j) {
            printf("%d ", edges[i][j]);
        }
        printf(" => %d\n", edgesColSize[i]);
    }
#endif

    //
    for (int i = 0; i < bombsSize; ++i) {
#if (DFS)
#elif (BFS)
        retVal = fmax(retVal, bfs(i, edges, edgesColSize, bombsSize));
#endif
    }

    //
    for (i = 0; i < bombsSize; ++i) {
        free(edges[i]);
        edges[i] = NULL;
    }
    free(edges);
    edges = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
#define DFS (0)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    int dfs(int node, unordered_map<int, int>& visited, unordered_map<int, vector<int>>& edges) {
        int retVal = 0;

        visited[node] = 1;
        for (auto neighbor : edges[node]) {
            if (visited[neighbor] == 1) {
                continue;
            }
            visited[neighbor] = 1;
            dfs(neighbor, visited, edges);
        }
        retVal = visited.size();

        return retVal;
    }
    int bfs(int node, unordered_map<int, vector<int>>& edges, int bombsSize) {
        int retVal = 0;

        vector<int> visited(bombsSize, 0);
        visited[node] = 1;
        queue<int> bfsQueue;
        bfsQueue.emplace(node);
        ++retVal;

        while (bfsQueue.empty() == false) {
            auto current = bfsQueue.front();
            bfsQueue.pop();
            for (auto neighbor : edges[current]) {
                if (visited[neighbor] == 1) {
                    continue;
                }
                visited[neighbor] = 1;
                bfsQueue.emplace(neighbor);
                ++retVal;
            }
        }

        return retVal;
    }
    int maximumDetonation(vector<vector<int>>& bombs) {
        int retVal = 0;

        int bombsSize = bombs.size();

        //
        unordered_map<int, vector<int>> edges;
        for (int i = 0; i < bombsSize; ++i) {
            for (int j = 0; j < bombsSize; ++j) {
                if (i == j) {
                    continue;
                }

                // 1 <= xi, yi, ri <= 10^5
                long long dx = bombs[i][0] - bombs[j][0];
                long long dy = bombs[i][1] - bombs[j][1];
                long long dr = (dx * dx) + (dy * dy);
                long long r = (long long)bombs[i][2] * (long long)bombs[i][2];
                if (r >= dr) {
                    edges[i].push_back(j);
                }
            }
        }

        //
        for (int i = 0; i < bombsSize; ++i) {
#if (DFS)
            unordered_map<int, int> visited;
            retVal = max(retVal, dfs(i, visited, edges));
#elif (BFS)
            retVal = max(retVal, bfs(i, edges, bombsSize));
#endif
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.method = 2

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, cur: int, visited: set[int], graph: defaultdict[List[int]]) -> int:
        retVal = 0

        visited.add(cur)
        for neighbor in graph[cur]:
            if neighbor in visited:
                continue
            self.dfs(neighbor, visited, graph)
        retVal = len(visited)

        return retVal

    def bfs(self, i: int, graph: defaultdict[List[int]]) -> int:
        retVal = 0

        bfsQueue = deque([i])
        visited = set([i])
        while bfsQueue:
            current = bfsQueue.popleft()
            for neighbor in graph[current]:
                if neighbor in visited:
                    continue
                visited.add(neighbor)
                bfsQueue.append(neighbor)
        retVal = len(visited)

        return retVal

    def maximumDetonation(self, bombs: List[List[int]]) -> int:
        retVal = 0

        bombsSize = len(bombs)

        #
        graph = defaultdict(list)
        for i in range(bombsSize):
            for j in range(bombsSize):
                if i == j:
                    continue

                xi, yi, ri = bombs[i]
                xj, yj, _ = bombs[j]
                if ri ** 2 >= (xi - xj) ** 2 + (yi - yj) ** 2:
                    graph[i].append(j)

        #
        for i in range(bombsSize):
            if self.method == 1:
                visited = set()
                retVal = max(retVal, self.dfs(i, visited, graph))
            elif self.method == 2:
                retVal = max(retVal, self.bfs(i, graph))

        return retVal
```

</details>

## [2127. Maximum Employees to Be Invited to a Meeting](https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/)  2449

- [Official](https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/editorial/)
- [Official](https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/1190222/can-jia-hui-yi-de-zui-duo-yuan-gong-shu-u8e8u/)

<details><summary>Description</summary>

```text
A company is organizing a meeting and has a list of n employees, waiting to be invited.
They have arranged for a large circular table, capable of seating any number of employees.

The employees are numbered from 0 to n - 1.
Each employee has a favorite person and they will attend the meeting only if
they can sit next to their favorite person at the table.
The favorite person of an employee is not themself.

Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee,
return the maximum number of employees that can be invited to the meeting.

Example 1:
Input: favorite = [2,2,1,2]
Output: 3
Explanation:
The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
The maximum number of employees that can be invited to the meeting is 3.

Example 2:
Input: favorite = [1,2,0]
Output: 3
Explanation:
Each employee is the favorite person of at least one other employee,
and the only way the company can invite them is if they invite every employee.
The seating arrangement will be the same as that in the figure given in example 1:
- Employee 0 will sit between employees 2 and 1.
- Employee 1 will sit between employees 0 and 2.
- Employee 2 will sit between employees 1 and 0.
The maximum number of employees that can be invited to the meeting is 3.

Example 3:
Input: favorite = [3,0,1,4,1]
Output: 4
Explanation:
The above figure shows how the company will invite employees 0, 1, 3, and 4, and seat them at the round table.
Employee 2 cannot be invited because the two spots next to their favorite employee 1 are taken.
So the company leaves them out of the meeting.
The maximum number of employees that can be invited to the meeting is 4.

Constraints:
n == favorite.length
2 <= n <= 10^5
0 <= favorite[i] <= n - 1
favorite[i] != i
```

<details><summary>Hint</summary>

```text
1. From the given array favorite, create a graph where for every index i,
   there is a directed edge from favorite[i] to i.
   The graph will be a combination of cycles and chains of acyclic edges.
   Now, what are the ways in which we can choose employees to sit at the table?
2. The first way by which we can choose employees is by selecting a cycle of the graph.
   It can be proven that in this case, the employees that do not lie in the cycle can never be seated at the table.
3. The second way is by combining acyclic chains.
   At most two chains can be combined by a cycle of length 2,
   where each chain ends on one of the employees in the cycle.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumInvitations(int* favorite, int favoriteSize) {
    int retVal = 0;

    // Calculate in-degree for each node
    int inDegree[favoriteSize];
    memset(inDegree, 0, sizeof(inDegree));
    for (int person = 0; person < favoriteSize; ++person) {
        inDegree[favorite[person]]++;
    }

    // Topological sorting to remove non-cycle nodes
    int TopologicalSortingQueueSize = 2 * favoriteSize + 1;
    int TopologicalSortingQueue[TopologicalSortingQueueSize];
    memset(TopologicalSortingQueue, 0, sizeof(TopologicalSortingQueue));
    int TopologicalSortingQueueFront = 0;
    int TopologicalSortingQueueRear = 0;
    for (int person = 0; person < favoriteSize; ++person) {
        if (inDegree[person] == 0) {
            TopologicalSortingQueue[TopologicalSortingQueueRear++] = person;
        }
    }

    int depth[favoriteSize];  // Depth of each node
    for (int i = 0; i < favoriteSize; ++i) {
        depth[i] = 1;
    }

    int currentNode, nextNode;
    while (TopologicalSortingQueueFront < TopologicalSortingQueueRear) {
        currentNode = TopologicalSortingQueue[TopologicalSortingQueueFront++];

        nextNode = favorite[currentNode];
        depth[nextNode] = fmax(depth[nextNode], depth[currentNode] + 1);

        inDegree[nextNode]--;
        if (inDegree[nextNode] == 0) {
            TopologicalSortingQueue[TopologicalSortingQueueRear++] = nextNode;
        }
    }

    // Detect cycles
    int cycleLength, current;
    int longestCycle = 0;
    int twoCycleInvitations = 0;
    for (int person = 0; person < favoriteSize; ++person) {
        if (inDegree[person] == 0) {  // Already processed
            continue;
        }

        cycleLength = 0;
        current = person;
        while (inDegree[current] != 0) {
            inDegree[current] = 0;  // Mark as visited
            cycleLength++;
            current = favorite[current];
        }

        if (cycleLength == 2) {  // For 2-cycles, add the depth of both nodes
            twoCycleInvitations += depth[person] + depth[favorite[person]];
        } else {
            longestCycle = fmax(longestCycle, cycleLength);
        }
    }

    retVal = fmax(longestCycle, twoCycleInvitations);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumInvitations(vector<int>& favorite) {
        int retVal = 0;

        int favoriteSize = favorite.size();

        // Calculate in-degree for each node
        vector<int> inDegree(favoriteSize, 0);
        for (int person = 0; person < favoriteSize; ++person) {
            inDegree[favorite[person]]++;
        }

        // Topological sorting to remove non-cycle nodes
        queue<int> TopologicalSortingQueue;
        for (int person = 0; person < favoriteSize; ++person) {
            if (inDegree[person] == 0) {
                TopologicalSortingQueue.push(person);
            }
        }

        vector<int> depth(favoriteSize, 1);  // Depth of each node

        while (TopologicalSortingQueue.empty() == false) {
            int currentNode = TopologicalSortingQueue.front();
            TopologicalSortingQueue.pop();

            int nextNode = favorite[currentNode];
            depth[nextNode] = max(depth[nextNode], depth[currentNode] + 1);

            inDegree[nextNode]--;
            if (inDegree[nextNode] == 0) {
                TopologicalSortingQueue.push(nextNode);
            }
        }

        // Detect cycles
        int longestCycle = 0;
        int twoCycleInvitations = 0;
        for (int person = 0; person < favoriteSize; ++person) {
            if (inDegree[person] == 0) {  // Already processed
                continue;
            }

            int cycleLength = 0;
            int current = person;
            while (inDegree[current] != 0) {
                inDegree[current] = 0;  // Mark as visited
                cycleLength++;
                current = favorite[current];
            }

            if (cycleLength == 2) {  // For 2-cycles, add the depth of both nodes
                twoCycleInvitations += depth[person] + depth[favorite[person]];
            } else {
                longestCycle = max(longestCycle, cycleLength);
            }
        }

        retVal = max(longestCycle, twoCycleInvitations);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumInvitations(self, favorite: List[int]) -> int:
        retVal = 0

        favoriteSize = len(favorite)

        # Calculate in-degree for each node
        inDegree = [0] * favoriteSize
        for person in range(favoriteSize):
            inDegree[favorite[person]] += 1

        # Topological sorting to remove non-cycle nodes
        TopologicalSortingQueue = deque()
        for person in range(favoriteSize):
            if inDegree[person] == 0:
                TopologicalSortingQueue.append(person)

        depth = [1] * favoriteSize  # Depth of each node

        while TopologicalSortingQueue:
            currentNode = TopologicalSortingQueue.popleft()
            nextNode = favorite[currentNode]
            depth[nextNode] = max(depth[nextNode], depth[currentNode] + 1)
            inDegree[nextNode] -= 1
            if inDegree[nextNode] == 0:
                TopologicalSortingQueue.append(nextNode)

        # Detect cycles
        longestCycle = 0
        twoCycleInvitations = 0
        for person in range(favoriteSize):
            if inDegree[person] == 0:  # Already processed
                continue

            cycleLength = 0
            current = person
            while inDegree[current] != 0:
                inDegree[current] = 0  # Mark as visited
                cycleLength += 1
                current = favorite[current]

            if cycleLength == 2:  # For 2-cycles, add the depth of both nodes
                twoCycleInvitations += depth[person] + depth[favorite[person]]
            else:
                longestCycle = max(longestCycle, cycleLength)

        retVal = max(longestCycle, twoCycleInvitations)

        return retVal
```

</details>

## [2192. All Ancestors of a Node in a Directed Acyclic Graph](https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/)  1787

- [Official](https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/editorial/)
- [Official](https://leetcode.cn/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/solutions/1364674/you-xiang-wu-huan-tu-zhong-yi-ge-jie-dia-6ed5/)

<details><summary>Description</summary>

```text
You are given a positive integer n representing the number of nodes of a Directed Acyclic Graph (DAG).
The nodes are numbered from 0 to n - 1 (inclusive).

You are also given a 2D integer array edges, where edges[i] = [fromi, toi] denotes
that there is a unidirectional edge from fromi to toi in the graph.

Return a list answer, where answer[i] is the list of ancestors of the ith node, sorted in ascending order.

A node u is an ancestor of another node v if u can reach v via a set of edges.

Example 1:
Input: n = 8, edgeList = [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
Explanation:
The above diagram represents the input graph.
- Nodes 0, 1, and 2 do not have any ancestors.
- Node 3 has two ancestors 0 and 1.
- Node 4 has two ancestors 0 and 2.
- Node 5 has three ancestors 0, 1, and 3.
- Node 6 has five ancestors 0, 1, 2, 3, and 4.
- Node 7 has four ancestors 0, 1, 2, and 3.

Example 2:
Input: n = 5, edgeList = [[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Output: [[],[0],[0,1],[0,1,2],[0,1,2,3]]
Explanation:
The above diagram represents the input graph.
- Node 0 does not have any ancestor.
- Node 1 has one ancestor 0.
- Node 2 has two ancestors 0 and 1.
- Node 3 has three ancestors 0, 1, and 2.
- Node 4 has four ancestors 0, 1, 2, and 3.

Constraints:
1 <= n <= 1000
0 <= edges.length <= min(2000, n * (n - 1) / 2)
edges[i].length == 2
0 <= fromi, toi <= n - 1
fromi != toi
There are no duplicate edges.
The graph is directed and acyclic.
```

<details><summary>Hint</summary>

```text
1. Consider how reversing each edge of the graph can help us.
2. How can performing BFS/DFS on the reversed graph help us find the ancestors of every node?
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    UT_hash_handle hh;
};
struct hashTable *hashFindItem(struct hashTable **obj, int key) {
    struct hashTable *pRetVal = NULL;

    HASH_FIND_INT(*obj, &key, pRetVal);

    return pRetVal;
}
bool hashAddItem(struct hashTable **obj, int key) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }
    struct hashTable *pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void freeAll(struct hashTable **pFree) {
    struct hashTable *current = NULL;
    struct hashTable *tmp = NULL;
    HASH_ITER(hh, (*pFree), current, tmp) {
        // printf("%d\n", (*pFree)->key);
        HASH_DEL((*pFree), current);
        free(current);
    }
}
struct ListNode *creatListNode(int val) {
    struct ListNode *pRetVal = NULL;

    pRetVal = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = val;
    pRetVal->next = NULL;

    return pRetVal;
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **getAncestors(int n, int **edges, int edgesSize, int *edgesColSize, int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int **)malloc(n * sizeof(int *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int *)malloc(n * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (n * sizeof(int)));

    //
    int i;

    //
    struct hashTable *ancestorsSetList[n];
    struct ListNode *adjacencyList[n];
    int indegree[n];
    for (i = 0; i < n; i++) {
        ancestorsSetList[i] = NULL;
        adjacencyList[i] = NULL;
        indegree[i] = 0;
    }
    struct ListNode *pNode;
    int from, to;
    for (i = 0; i < edgesSize; i++) {
        from = edges[i][0];
        to = edges[i][1];

        pNode = creatListNode(to);
        if (pNode == NULL) {
            continue;
        }
        pNode->next = adjacencyList[from];
        adjacencyList[from] = pNode;
        indegree[to] += 1;
    }

    //
    int nodesWithZeroIndegree[n];
    int nodesWithZeroIndegreeHead = 0;
    int nodesWithZeroIndegreeTail = 0;
    for (i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            nodesWithZeroIndegree[nodesWithZeroIndegreeTail++] = i;
        }
    }
    struct hashTable *pEntry;
    int currentNode, key, value;
    while (nodesWithZeroIndegreeHead != nodesWithZeroIndegreeTail) {
        currentNode = nodesWithZeroIndegree[nodesWithZeroIndegreeHead++];
        for (pNode = adjacencyList[currentNode]; pNode; pNode = pNode->next) {
            value = pNode->val;
            hashAddItem(&ancestorsSetList[value], currentNode);

            for (pEntry = ancestorsSetList[currentNode]; pEntry != NULL; pEntry = pEntry->hh.next) {
                key = pEntry->key;
                hashAddItem(&ancestorsSetList[value], key);
            }

            indegree[value] -= 1;
            if (indegree[value] == 0) {
                nodesWithZeroIndegree[nodesWithZeroIndegreeTail++] = value;
            }
        }
    }

    //
    int idx;
    int ancestorsSetListCount;
    for (i = 0; i < n; ++i) {
        ancestorsSetListCount = HASH_COUNT(ancestorsSetList[i]);

        (*returnColumnSizes)[i] = ancestorsSetListCount;
        pRetVal[i] = (int *)malloc(ancestorsSetListCount * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            continue;
        }
        memset(pRetVal[i], 0, (ancestorsSetListCount * sizeof(int)));
        (*returnSize) += 1;
        idx = 0;
        for (pEntry = ancestorsSetList[i]; pEntry != NULL; pEntry = pEntry->hh.next) {
            pRetVal[i][idx++] = pEntry->key;
        }
        qsort(pRetVal[i], ancestorsSetListCount, sizeof(int), compareInteger);

        freeAll(&ancestorsSetList[i]);
        ancestorsSetList[i] = NULL;
        while (adjacencyList[i] != NULL) {
            pNode = adjacencyList[i];
            adjacencyList[i] = adjacencyList[i]->next;
            free(pNode);
            pNode = NULL;
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> retVal(n);

        vector<vector<int>> adjacencyList(n);
        for (int i = 0; i < n; i++) {
            adjacencyList[i] = {};
        }

        vector<int> indegree(n, 0);
        for (auto& edge : edges) {
            int from = edge[0];
            int to = edge[1];
            adjacencyList[from].push_back(to);
            indegree[to]++;
        }
        int indegreeSize = indegree.size();

        queue<int> nodesWithZeroIndegree;
        for (int i = 0; i < indegreeSize; i++) {
            if (indegree[i] == 0) {
                nodesWithZeroIndegree.push(i);
            }
        }

        vector<int> topologicalOrder;
        while (nodesWithZeroIndegree.empty() == false) {
            int currentNode = nodesWithZeroIndegree.front();
            nodesWithZeroIndegree.pop();
            topologicalOrder.push_back(currentNode);
            // Reduce indegree of neighboring nodes and add them to the queue if they have no more incoming edges
            for (int neighbor : adjacencyList[currentNode]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    nodesWithZeroIndegree.push(neighbor);
                }
            }
        }

        vector<set<int>> ancestorsSetList(n);
        // Fill the set list with ancestors using the topological order
        for (int node : topologicalOrder) {
            for (int neighbor : adjacencyList[node]) {
                // Add immediate parent, and other ancestors
                ancestorsSetList[neighbor].insert(node);
                ancestorsSetList[neighbor].insert(ancestorsSetList[node].begin(), ancestorsSetList[node].end());
            }
        }
        // Convert sets to lists and sort them
        int retValSize = retVal.size();
        for (int i = 0; i < retValSize; i++) {
            retVal[i].assign(ancestorsSetList[i].begin(), ancestorsSetList[i].end());
            sort(retVal[i].begin(), retVal[i].end());
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        retVal = [list()]

        adjacencyList = [[] for _ in range(n)]
        indegree = [0 for _ in range(n)]
        for edge in edges:
            fromNode = edge[0]
            toNode = edge[1]
            adjacencyList[fromNode].append(toNode)
            indegree[toNode] += 1

        nodesWithZeroIndegree = [i for i in range(n) if indegree[i] == 0]

        topologicalOrder = []
        while nodesWithZeroIndegree:
            currentNode = nodesWithZeroIndegree.pop(0)
            topologicalOrder.append(currentNode)
            # Reduce indegree of neighboring nodes and add them to the queue if they have no more incoming edges
            for neighbor in adjacencyList[currentNode]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    nodesWithZeroIndegree.append(neighbor)

        # Initialize the result list and set list for storing ancestors
        retVal = [[] for _ in range(n)]
        ancestorsSetList = [set() for _ in range(n)]
        # Fill the set list with ancestors using the topological order
        for node in topologicalOrder:
            for neighbor in adjacencyList[node]:
                # Add immediate parent, and other ancestors.
                ancestorsSetList[neighbor].add(node)
                ancestorsSetList[neighbor].update(ancestorsSetList[node])
        # Convert sets to lists and sort them
        for i in range(n):
            retVal[i].extend(ancestorsSetList[i])
            retVal[i].sort()

        return retVal
```

</details>

## [2246. Longest Path With Different Adjacent Characters](https://leetcode.com/problems/longest-path-with-different-adjacent-characters/)  2126

- [Official](https://leetcode.com/problems/longest-path-with-different-adjacent-characters/solutions/2889382/longest-path-with-different-adjacent-characters/)

<details><summary>Description</summary>

```text
You are given a tree (i.e. a connected, undirected graph that has no cycles)
rooted at node 0 consisting of n nodes numbered from 0 to n - 1.
The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent of node i.
Since node 0 is the root, parent[0] == -1.

You are also given a string s of length n, where s[i] is the character assigned to node i.

Return the length of the longest path in the tree
such that no pair of adjacent nodes on the path have the same character assigned to them.
```

```text
Example 1:
```

```mermaid
graph TD
    root((0:a))---|a|l((2:a))
    root((0:a))---|b|r((1:b))
    l((2:a))---|e|ll((5:e))
    l((2:a))---lr(null)
    r((1:b))---|c|rl((3:c))
    r((1:b))---|b|rr((4:b))
```

```text
Input: parent = [-1,0,0,1,1,2], s = "abacbe"
Output: 3
Explanation: The longest path where each two adjacent nodes have different characters in the tree is the path: 0 -> 1 -> 3.
The length of this path is 3, so 3 is returned.
It can be proven that there is no longer path that satisfies the conditions.
```

```text
Example 2:
```

```mermaid
graph TD
    root((0:a))---|c|l((3:c))
    root((0:a))---|b|m((2:b))
    root((0:a))---|a|r((1:a))
```

```text
Input: parent = [-1,0,0,0], s = "aabc"
Output: 3
Explanation: The longest path where each two adjacent nodes have different characters is the path: 2 -> 0 -> 3.
The length of this path is 3, so 3 is returned.
```

```text
Constraints:
n == parent.length == s.length
1 <= n <= 10^5
0 <= parent[i] <= n - 1 for all i >= 1
parent[0] == -1
parent represents a valid tree.
s consists of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int longestPath(int* parent, int parentSize, char * s){

}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define DEPTH_FIRST_SEARCH (1)
#define BREADTH_FIRST_SEARCH (1)

   public:
    int dfs(int currentNode, vector<vector<int>>& children, string& s, int& longestPath) {
        // Longest and second longest chains starting from currentNode (does not count the currentNode itself).
        int longestChain = 0;
        int secondLongestChain = 0;

        for (int child : children[currentNode]) {
            // Get the number of nodes in the longest path in the subtree of child, including the child.
            int longestChainStartingFromChild = dfs(child, children, s, longestPath);

            // We won't move to the child if it has the same character as the currentNode.
            if (s[currentNode] == s[child]) {
                continue;
            }

            // Modify the longestChain and secondLongestChain if longestChainStartingFromChild is bigger.
            if (longestChainStartingFromChild > longestChain) {
                secondLongestChain = longestChain;
                longestChain = longestChainStartingFromChild;
            } else if (longestChainStartingFromChild > secondLongestChain) {
                secondLongestChain = longestChainStartingFromChild;
            }
        }

        // Add "1" for the node itself.
        longestPath = max(longestPath, longestChain + secondLongestChain + 1);

        return longestChain + 1;
    }

    int longestPath(vector<int>& parent, string s) {
        int retVal;

#if (DEPTH_FIRST_SEARCH)
        cout << "DEPTH_FIRST_SEARCH\n";

        int n = parent.size();
        vector<vector<int>> children(n);
        // Start from node 1, since root node 0 does not have a parent.
        for (int i = 1; i < n; ++i) {
            children[parent[i]].push_back(i);
        }

        retVal = 1;
        dfs(0, children, s, retVal);
#elif (BREADTH_FIRST_SEARCH)
        cout << "BREADTH_FIRST_SEARCH\n";

        retVal = 1;

        int n = parent.size();
        vector<int> childrenCount(n);
        // Start from 1, since the root node does not have a parent.
        for (int node = 1; node < n; node++) {
            childrenCount[parent[node]]++;
        }

        vector<vector<int>> longestChains(n);
        queue<int> q;
        for (int node = 0; node < n; node++) {
            longestChains[node] = vector<int>(2);
            // Push all leaf nodes in the queue.
            if (childrenCount[node] == 0 && node != 0) {
                q.push(node);
                longestChains[node][0] = 1;
            }
        }

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();
            int par = parent[currentNode];

            // Get the number of nodes in the longest chain starting from the currentNode, including the currentNode.
            if (s[currentNode] != s[par]) {
                // Modify the longest chain and second longest chain if longestChainStartingFromCurrNode is bigger.
                int longestChainStartingFromCurrNode = longestChains[currentNode][0];
                if (longestChainStartingFromCurrNode > longestChains[par][0]) {
                    longestChains[par][1] = longestChains[par][0];
                    longestChains[par][0] = longestChainStartingFromCurrNode;
                } else if (longestChainStartingFromCurrNode > longestChains[par][1]) {
                    longestChains[par][1] = longestChainStartingFromCurrNode;
                }
            }

            retVal = max(retVal, longestChains[par][0] + longestChains[par][1] + 1);
            childrenCount[par]--;

            if (childrenCount[par] == 0 && par != 0) {
                longestChains[par][0]++;
                q.push(par);
            }
        }
#endif

        return retVal;
    }
};
```

</details>

## [2285. Maximum Total Importance of Roads](https://leetcode.com/problems/maximum-total-importance-of-roads/)  1496

- [Official](https://leetcode.com/problems/maximum-total-importance-of-roads/editorial/)

<details><summary>Description</summary>

```text
You are given an integer n denoting the number of cities in a country. The cities are numbered from 0 to n - 1.

You are also given a 2D integer array roads where roads[i] = [ai, bi]
denotes that there exists a bidirectional road connecting cities ai and bi.

You need to assign each city with an integer value from 1 to n, where each value can only be used once.
The importance of a road is then defined as the sum of the values of the two cities it connects.

Return the maximum total importance of all roads possible after assigning the values optimally.

Example 1:
Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
Output: 43
Explanation: The figure above shows the country and the assigned values of [2,4,5,3,1].
- The road (0,1) has an importance of 2 + 4 = 6.
- The road (1,2) has an importance of 4 + 5 = 9.
- The road (2,3) has an importance of 5 + 3 = 8.
- The road (0,2) has an importance of 2 + 5 = 7.
- The road (1,3) has an importance of 4 + 3 = 7.
- The road (2,4) has an importance of 5 + 1 = 6.
The total importance of all roads is 6 + 9 + 8 + 7 + 7 + 6 = 43.
It can be shown that we cannot obtain a greater total importance than 43.

Example 2:
Input: n = 5, roads = [[0,3],[2,4],[1,3]]
Output: 20
Explanation: The figure above shows the country and the assigned values of [4,3,2,5,1].
- The road (0,3) has an importance of 4 + 5 = 9.
- The road (2,4) has an importance of 2 + 1 = 3.
- The road (1,3) has an importance of 3 + 5 = 8.
The total importance of all roads is 9 + 3 + 8 = 20.
It can be shown that we cannot obtain a greater total importance than 20.

Constraints:
2 <= n <= 5 * 10^4
1 <= roads.length <= 5 * 10^4
roads[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
There are no duplicate roads.
```

<details><summary>Hint</summary>

```text
1. Consider what each city contributes to the total importance of all roads.
2. Based on that, how can you sort the cities
   such that assigning them values in that order will yield the maximum total importance?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long maximumImportance(int n, int** roads, int roadsSize, int* roadsColSize) {
    long long retVal = 0;

    int degree[n];
    memset(degree, 0, sizeof(degree));

    int i;
    for (i = 0; i < roadsSize; ++i) {
        degree[roads[i][0]] += 1;
        degree[roads[i][1]] += 1;
    }
    qsort(degree, n, sizeof(int), compareInteger);

    long long value = 1;
    for (i = 0; i < n; ++i) {
        retVal += (value * degree[i]);
        value += 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        long long retVal = 0;

        vector<int> degree(n, 0);
        for (auto road : roads) {
            degree[road[0]] += 1;
            degree[road[1]] += 1;
        }
        sort(degree.begin(), degree.end());

        long long value = 1;
        for (int d : degree) {
            retVal += (value * d);
            value += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        retVal = 0

        degree = [0] * n
        for edge in roads:
            degree[edge[0]] += 1
            degree[edge[1]] += 1
        degree.sort()

        value = 1
        for d in degree:
            retVal += (value * d)
            value += 1

        return retVal
```

</details>

## [2290. Minimum Obstacle Removal to Reach Corner](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/)  2137

- [Official](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
- 0 represents an empty cell,
- 1 represents an obstacle that may be removed.

You can move up, down, left, or right from and to an empty cell.

Return the minimum number of obstacles to remove
so you can move from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).

Example 1:
Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.

Example 2:
Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 10^5
2 <= m * n <= 10^5
grid[i][j] is either 0 or 1.
grid[0][0] == grid[m - 1][n - 1] == 0
```

<details><summary>Hint</summary>

```text
1. Model the grid as a graph where cells are nodes and edges are between adjacent cells.
   Edges to cells with obstacles have a cost of 1 and all other edges have a cost of 0.
2. Could you use 0-1 Breadth-First Search or Dijkstra’s algorithm?
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef DEQUE_H
#define DEQUE_H

typedef struct DLinkListNode {
    int obstacles;
    int row;
    int col;
    struct DLinkListNode* prev;
    struct DLinkListNode* next;
} DLinkListNode;
DLinkListNode* dLinkListNodeCreat(int obstacles, int row, int col) {
    DLinkListNode* obj = NULL;

    obj = (DLinkListNode*)malloc(sizeof(DLinkListNode));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->obstacles = obstacles;
    obj->row = row;
    obj->col = col;
    obj->prev = NULL;
    obj->next = NULL;

    return obj;
}
typedef struct {
    int capacity;
    DLinkListNode* head;
    DLinkListNode* tail;
    int size;
} MyCircularDeque;
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = NULL;

    obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = k;
    obj->head = NULL;
    obj->tail = NULL;
    obj->size = 0;

    return obj;
}
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == 0) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == obj->capacity) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeInsertFront(MyCircularDeque* obj, int obstacles, int row, int col) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(obstacles, row, col);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        pNew->next = obj->head;
        obj->head->prev = pNew;
        obj->head = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeInsertLast(MyCircularDeque* obj, int obstacles, int row, int col) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(obstacles, row, col);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        obj->tail->next = pNew;
        pNew->prev = obj->tail;
        obj->tail = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->head;
    obj->head = obj->head->next;
    if (obj->head != NULL) {
        obj->head->prev = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->tail;
    obj->tail = obj->tail->prev;
    if (obj->tail != NULL) {
        obj->tail->next = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
void myCircularDequeFree(MyCircularDeque* obj) {
    DLinkListNode* pDelete = NULL;
    while (obj->head != obj->tail) {
        pDelete = obj->head;
        obj->head = obj->head->next;
        free(pDelete);
        pDelete = NULL;
    }
    free(obj->head);
    obj->head = NULL;

    free(obj);
    obj = NULL;
}

#endif  // DEQUE_H
bool isValid(int gridSize, int gridColSize, int row, int col) {
    bool retVal = true;

    if (row < 0) {
        retVal = false;
    } else if (row >= gridSize) {
        retVal = false;
    } else if (col < 0) {
        retVal = false;
    } else if (col >= gridColSize) {
        retVal = false;
    }

    return retVal;
}
int minimumObstacles(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int minObstacles[rowSize][colSize];
    memset(minObstacles, 0, sizeof(minObstacles));
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            minObstacles[i][j] = INT_MAX;
        }
    }
    minObstacles[0][0] = 0;

    MyCircularDeque* deque = NULL;
    deque = myCircularDequeCreate(rowSize * colSize + 1);
    myCircularDequeInsertLast(deque, 0, 0, 0);

    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int obstacles, row, col;
    int newRow, newCol;
    while (myCircularDequeIsEmpty(deque) == false) {
        obstacles = deque->head->obstacles;
        row = deque->head->row;
        col = deque->head->col;
        myCircularDequeDeleteFront(deque);

        for (int i = 0; i < 4; ++i) {
            newRow = row + directions[i][0];
            newCol = col + directions[i][1];
            if (isValid(rowSize, colSize, newRow, newCol) == false) {
                continue;
            } else if (minObstacles[newRow][newCol] != INT_MAX) {
                continue;
            }

            if (grid[newRow][newCol] == 1) {
                minObstacles[newRow][newCol] = obstacles + 1;
                myCircularDequeInsertLast(deque, obstacles + 1, newRow, newCol);
            } else {
                minObstacles[newRow][newCol] = obstacles;
                myCircularDequeInsertFront(deque, obstacles, newRow, newCol);
            }
        }
    }
    retVal = minObstacles[rowSize - 1][colSize - 1];

    //
    free(deque);
    deque = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    bool isValid(int gridSize, int gridColSize, int row, int col) {
        bool retVal = true;

        if (row < 0) {
            retVal = false;
        } else if (row >= gridSize) {
            retVal = false;
        } else if (col < 0) {
            retVal = false;
        } else if (col >= gridColSize) {
            retVal = false;
        }

        return retVal;
    }

   public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        vector<vector<int>> minObstacles(gridSize, vector<int>(gridColSize, numeric_limits<int>::max()));
        minObstacles[0][0] = grid[0][0];

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({minObstacles[0][0], 0, 0});
        while (pq.empty() == false) {
            vector<int> current = pq.top();
            pq.pop();
            int obstacles = current[0];
            int row = current[1];
            int col = current[2];
            if ((row == gridSize - 1) && (col == gridColSize - 1)) {
                retVal = obstacles;
                return retVal;
            }

            for (vector<int>& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                if (isValid(gridSize, gridColSize, newRow, newCol) == false) {
                    continue;
                }

                int newObstacles = obstacles + grid[newRow][newCol];
                if (newObstacles < minObstacles[newRow][newCol]) {
                    minObstacles[newRow][newCol] = newObstacles;
                    pq.push({newObstacles, newRow, newCol});
                }
            }
        }
        retVal = minObstacles[gridSize - 1][gridColSize - 1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    def isValid(self, gridSize: int, gridColSize: int, row: int, col: int) -> bool:
        retVal = False

        if (0 <= row < gridSize) and (0 <= col < gridColSize):
            retVal = True

        return retVal

    def minimumObstacles(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        minObstacles = [[float("inf")] * gridColSize for _ in range(gridSize)]
        minObstacles[0][0] = grid[0][0]

        priorityQueue = [(minObstacles[0][0], 0, 0)]
        while priorityQueue:
            obstacles, row, col = heappop(priorityQueue)
            if (row == gridSize - 1) and (col == gridColSize - 1):
                retVal = obstacles
                return retVal

            for x, y in self.directions:
                newRow = row + x
                newCol = col + y
                if self.isValid(gridSize, gridColSize, newRow, newCol) == False:
                    continue

                newObstacles = obstacles + grid[newRow][newCol]
                if newObstacles < minObstacles[newRow][newCol]:
                    minObstacles[newRow][newCol] = newObstacles
                    heappush(priorityQueue, (newObstacles, newRow, newCol))

        retVal = minObstacles[gridSize - 1][gridColSize - 1]

        return retVal
```

</details>

## [2316. Count Unreachable Pairs of Nodes in an Undirected Graph](https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/)  1604

<details><summary>Description</summary>

```text
You are given an integer n.
There is an undirected graph with n nodes, numbered from 0 to n - 1.
You are given a 2D integer array edges where edges[i] = [ai, bi] denotes
that there exists an undirected edge connecting nodes ai and bi.

Return the number of pairs of different nodes that are unreachable from each other.

Example 1:
Input: n = 3, edges = [[0,1],[0,2],[1,2]]
Output: 0
Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.

Example 2:
Input: n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
Output: 14
Explanation: There are 14 pairs of nodes that are unreachable from each other:
[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]].
Therefore, we return 14.

Constraints:
1 <= n <= 10^5
0 <= edges.length <= 2 * 10^5
edges[i].length == 2
0 <= ai, bi < n
ai != bi
There are no repeated edges.
```

<details><summary>Hint</summary>

```text
1. Find the connected components of the graph.
   To find connected components, you can use Union Find (Disjoint Sets), BFS, or DFS.
2. For a node u, the number of nodes that are unreachable from u is the number of nodes
   that are not in the same connected component as u.
3. The number of unreachable nodes from node u will be the same for the number of nodes
   that are unreachable from node v if nodes u and v belong to the same connected component.
```

</details>

</details>

<details><summary>C</summary>

```c
#define UNION_FIND (1)
#if (UNION_FIND)
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

struct DisjointSetUnion {
    int* parent;
    int* size;
    int n;
    int setCount;
};
int initDisjointSet(struct DisjointSetUnion* obj, int n) {
    obj->parent = (int*)malloc(n * sizeof(int));
    if (obj->parent == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    obj->size = (int*)malloc(n * sizeof(int));
    if (obj->size == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    obj->n = n;
    obj->setCount = n;

    int i;
    for (i = 0; i < n; ++i) {
        obj->parent[i] = i;
        obj->size[i] = 1;
    }

    return EXIT_SUCCESS;
}
void freeDisjointSet(struct DisjointSetUnion* obj) {
    if (obj->parent) {
        free(obj->parent);
        obj->parent = NULL;
    }

    if (obj->size) {
        free(obj->size);
        obj->size = NULL;
    }
}
int find(struct DisjointSetUnion* obj, int x) {
    int retVal = x;

    if (obj->parent[x] != x) {
        obj->parent[x] = find(obj, obj->parent[x]);
        retVal = obj->parent[x];
    }

    return retVal;
}
bool unionSet(struct DisjointSetUnion* obj, int x, int y) {
    int retVal = false;

    int fx = find(obj, x);
    int fy = find(obj, y);
    if (fx == fy) {
        return retVal;
    }

    if (obj->size[fx] < obj->size[fy]) {
        swap(&fx, &fy);
    }
    obj->size[fx] += obj->size[fy];
    obj->parent[fy] = fx;
    obj->setCount--;
    retVal = true;

    return retVal;
}
#endif
long long countPairs(int n, int** edges, int edgesSize, int* edgesColSize) {
    long long retVal = 0;

    struct DisjointSetUnion* pUnionFind = (struct DisjointSetUnion*)malloc(sizeof(struct DisjointSetUnion));
    if (pUnionFind == NULL) {
        perror("malloc");
        return retVal;
    }
    if (initDisjointSet(pUnionFind, n) == EXIT_FAILURE) {
        freeDisjointSet(pUnionFind);
        free(pUnionFind);
        pUnionFind = NULL;
        return retVal;
    }

    int i;
    for (i = 0; i < edgesSize; ++i) {
        unionSet(pUnionFind, edges[i][0], edges[i][1]);
    }
    for (i = 0; i < n; ++i) {
        if (pUnionFind->parent[i] == i) {
            retVal += (long long)pUnionFind->size[i] * (n - pUnionFind->size[i]);
        }
    }
    retVal /= 2;

    freeDisjointSet(pUnionFind);
    free(pUnionFind);
    pUnionFind = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class UnionFind {
   public:
    vector<int> parent;
    vector<int> size;
    int n;
    int setCount;
    UnionFind(int _n) : parent(vector<int>(_n)), size(vector<int>(_n, 1)), n(_n), setCount(_n) {
        //
        iota(parent.begin(), parent.end(), 0);
    }

    int findset(int x) {
        int retVal = x;

        if (parent[x] == x) {
            return retVal;
        }
        parent[x] = findset(parent[x]);
        retVal = parent[x];

        return retVal;
    }
    bool unite(int x, int y) {
        bool retVal = false;

        x = findset(x);
        y = findset(y);
        if (x == y) {
            return retVal;
        }

        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        retVal = true;

        return retVal;
    }
    bool connected(int x, int y) {
        bool retVal = false;

        x = findset(x);
        y = findset(y);
        if (x == y) {
            retVal = true;
        }

        return retVal;
    }
};

class Solution {
   public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        long long retVal = 0;

        UnionFind uf(n);
        for (auto& edge : edges) {
            uf.unite(edge[0], edge[1]);
        }

        for (int i = 0; i < n; i++) {
            if (uf.parent[i] == i) {
                retVal += (long long)uf.size[i] * (n - uf.size[i]);
            }
        }
        retVal /= 2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class UnionFind:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.size = [1] * n
        self.n = n
        self.setCount = n

    def findset(self, x: int) -> int:
        if self.parent[x] == x:
            return x
        self.parent[x] = self.findset(self.parent[x])
        return self.parent[x]

    def unite(self, x: int, y: int) -> bool:
        x, y = self.findset(x), self.findset(y)
        if x == y:
            return False
        if self.size[x] < self.size[y]:
            x, y = y, x
        self.parent[y] = x
        self.size[x] += self.size[y]
        self.setCount -= 1
        return True

    def connected(self, x: int, y: int) -> bool:
        x, y = self.findset(x), self.findset(y)
        return x == y


class Solution:
    def countPairs(self, n: int, edges: List[List[int]]) -> int:
        retVal = 0

        uf = UnionFind(n)
        for x, y in edges:
            uf.unite(x, y)

        for i in range(n):
            if uf.parent[i] == i:
                retVal += uf.size[i] * (n - uf.size[i])
        retVal = int(retVal / 2)

        return retVal
```

</details>

## [2359. Find Closest Node to Given Two Nodes](https://leetcode.com/problems/find-closest-node-to-given-two-nodes/)  1714

- [Official](https://leetcode.com/problems/find-closest-node-to-given-two-nodes/solutions/2864716/find-closest-node-to-given-two-nodes/)

<details><summary>Description</summary>

```text
You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n,
indicating that there is a directed edge from node i to node edges[i].
If there is no outgoing edge from i, then edges[i] == -1.

You are also given two integers node1 and node2.

Return the index of the node that can be reached from both node1 and node2,
such that the maximum between the distance from node1 to that node, and from node2 to that node is minimized.
If there are multiple answers, return the node with the smallest index, and if no possible answer exists, return -1.

Note that edges may contain cycles.

Example 1:
Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
Output: 2
Explanation: The distance from node 0 to node 2 is 1, and the distance from node 1 to node 2 is 1.
The maximum of those two distances is 1.
It can be proven that we cannot get a node with a smaller maximum distance than 1, so we return node 2.

Example 2:
Input: edges = [1,2,-1], node1 = 0, node2 = 2
Output: 2
Explanation: The distance from node 0 to node 2 is 2, and the distance from node 2 to itself is 0.
The maximum of those two distances is 2.
It can be proven that we cannot get a node with a smaller maximum distance than 2, so we return node 2.

Constraints:
n == edges.length
2 <= n <= 10^5
-1 <= edges[i] < n
edges[i] != i
0 <= node1, node2 < n
```

</details>

<details><summary>C</summary>

```c
void dfs(int node, int* edges, int* dist, int* visit) {
    visit[node] = 1;

    int neighbor = edges[node];
    if ((neighbor != -1) && (visit[neighbor] == 0)) {
        dist[neighbor] = 1 + dist[node];
        dfs(neighbor, edges, dist, visit);
    }
}
int closestMeetingNode(int* edges, int edgesSize, int node1, int node2) {
    int retVal = -1;

    int i;

    int dist1[edgesSize];
    for (i = 0; i < edgesSize; ++i) {
        dist1[i] = INT_MAX;
    }
    dist1[node1] = 0;
    int visit1[edgesSize];
    memset(visit1, 0, sizeof(visit1));
    dfs(node1, edges, dist1, visit1);

    int dist2[edgesSize];
    for (i = 0; i < edgesSize; ++i) {
        dist2[i] = INT_MAX;
    }
    dist2[node2] = 0;
    int visit2[edgesSize];
    memset(visit2, 0, sizeof(visit1));
    dfs(node2, edges, dist2, visit2);

    int minDist = INT_MAX;
    for (i = 0; i < edgesSize; ++i) {
        if (minDist > fmax(dist1[i], dist2[i])) {
            retVal = i;
            minDist = fmax(dist1[i], dist2[i]);
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void dfs(int node, vector<int>& edges, vector<int>& dist, vector<bool>& visit) {
        visit[node] = true;

        int neighbor = edges[node];
        if ((neighbor != -1) && (!visit[neighbor])) {
            dist[neighbor] = 1 + dist[node];
            dfs(neighbor, edges, dist, visit);
        }
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int retVal = -1;

        int n = edges.size();

        vector<int> dist1(n, numeric_limits<int>::max());
        dist1[node1] = 0;
        vector<bool> visit1(n);
        dfs(node1, edges, dist1, visit1);

        vector<int> dist2(n, numeric_limits<int>::max());
        dist2[node2] = 0;
        vector<bool> visit2(n);
        dfs(node2, edges, dist2, visit2);

        int minDist = numeric_limits<int>::max();
        for (int currNode = 0; currNode < n; ++currNode) {
            if (minDist > max(dist1[currNode], dist2[currNode])) {
                retVal = currNode;
                minDist = max(dist1[currNode], dist2[currNode]);
            }
        }

        return retVal;
    }
};
```

</details>

## [2360. Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/)  1897

<details><summary>Description</summary>

```text
You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n,
indicating that there is a directed edge from node i to node edges[i].
If there is no outgoing edge from node i, then edges[i] == -1.

Return the length of the longest cycle in the graph. If no cycle exists, return -1.

A cycle is a path that starts and ends at the same node.

Example 1:
Input: edges = [3,3,4,2,3]
Output: 3
Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
The length of this cycle is 3, so 3 is returned.

Example 2:
Input: edges = [2,-1,3,1]
Output: -1
Explanation: There are no cycles in this graph.

Constraints:
n == edges.length
2 <= n <= 10^5
-1 <= edges[i] < n
edges[i] != i
```

<details><summary>Hint</summary>

```text
1. How many cycles can each node at most be part of?
2. Each node can be part of at most one cycle.
   Start from each node and find the cycle that it is part of if there is any.
   Save the already visited nodes to not repeat visiting the same cycle multiple times.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.com/problems/longest-cycle-in-a-graph/solutions/2358092/simple-short-iterative-c-o-n/
int longestCycle(int* edges, int edgesSize) {
    int retVal = -1;

    int idx[edgesSize];
    memset(idx, 0, sizeof(idx));

    int k = 1;
    int curk;
    int i, j;
    for (i = 0; i < edgesSize; ++i) {
        j = i;
        curk = k;

        while ((j != -1) && (idx[j] == 0)) {
            idx[j] = k++;
            j = edges[j];
        }

        if ((j != -1) && (idx[j] >= curk)) {
            retVal = fmax(retVal, k - idx[j]);
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
// https://leetcode.com/problems/longest-cycle-in-a-graph/solutions/2357750/simple-dfs-traversal-easy-explanation-c/
#define DFS (1)
// https://leetcode.com/problems/longest-cycle-in-a-graph/solutions/2358092/simple-short-iterative-c-o-n/
#define TARJANS_ALGORITHM (1)

   public:
#if (DFS)
    int dfs(int node, vector<int>& edges, vector<bool>& visit, vector<int>& store) {
        int retVal = -1;

        if (node == -1) {
            return retVal;
        }

        int storeSize = store.size();

        if (visit[node] == true) {
            int count = -1;
            for (int i = 0; i < storeSize; ++i) {
                if (store[i] == node) {
                    count = i;
                    break;
                }
            }

            if (count == -1) {
                return retVal;
            }
            retVal = storeSize - count;

            return retVal;
        }

        visit[node] = true;
        store.push_back(node);
        retVal = dfs(edges[node], edges, visit, store);

        return retVal;
    }
#elif (TARJANS_ALGORITHM)
#endif

    int longestCycle(vector<int>& edges) {
        int retVal = -1;

        int edgesSize = edges.size();

#if (DFS)
        cout << "DFS\n";

        vector<bool> visit(edgesSize, 0);
        for (int i = 0; i < edgesSize; ++i) {
            if (visit[i] == true) {
                continue;
            }

            vector<int> store;
            retVal = max(retVal, dfs(i, edges, visit, store));
        }
#elif (TARJANS_ALGORITHM)
        cout << "TARJANS_ALGORITHM\n";

        vector<int> idx(edgesSize);
        int k = 1;
        for (int i = 0; i < edgesSize; ++i) {
            int j = i;
            int curk = k;
            while ((j != -1) && (idx[j] == 0)) {
                idx[j] = k++;
                j = edges[j];
            }

            if ((j != -1) && (idx[j] >= curk)) {
                retVal = max(retVal, k - idx[j]);
            }
        }
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # // https://leetcode.com/problems/longest-cycle-in-a-graph/solutions/2358092/simple-short-iterative-c-o-n/
    def longestCycle(self, edges: List[int]) -> int:
        retVal = -1

        idx = [0 for i in range(len(edges))]
        k = 1
        for i in range(len(edges)):
            j = i
            curk = k

            while (j != -1) and (idx[j] == 0):
                idx[j] = k
                k += 1
                j = edges[j]

            if (j != -1) and (idx[j] >= curk):
                retVal = max(retVal, k-idx[j])

        return retVal
```

</details>

## [2392. Build a Matrix With Conditions](https://leetcode.com/problems/build-a-matrix-with-conditions/)  1960

- [Official](https://leetcode.com/problems/build-a-matrix-with-conditions/editorial/)

<details><summary>Description</summary>

```text
You are given a positive integer k. You are also given:
- a 2D integer array rowConditions of size n where rowConditions[i] = [abovei, belowi], and
- a 2D integer array colConditions of size m where colConditions[i] = [lefti, righti].

The two arrays contain integers from 1 to k.

You have to build a k x k matrix that contains each of the numbers from 1 to k exactly once.
The remaining cells should have the value 0.

The matrix should also satisfy the following conditions:
- The number abovei should appear in a row that is strictly above the row
  at which the number belowi appears for all i from 0 to n - 1.
- The number lefti should appear in a column that is strictly left of the column
  at which the number righti appears for all i from 0 to m - 1.

Return any matrix that satisfies the conditions. If no answer exists, return an empty matrix.

Example 1:
Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
Output: [[3,0,0],[0,0,1],[0,2,0]]
Explanation: The diagram above shows a valid example of a matrix that satisfies all the conditions.
The row conditions are the following:
- Number 1 is in row 1, and number 2 is in row 2, so 1 is above 2 in the matrix.
- Number 3 is in row 0, and number 2 is in row 2, so 3 is above 2 in the matrix.
The column conditions are the following:
- Number 2 is in column 1, and number 1 is in column 2, so 2 is left of 1 in the matrix.
- Number 3 is in column 0, and number 2 is in column 1, so 3 is left of 2 in the matrix.
Note that there may be multiple correct answers.

Example 2:
Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]], colConditions = [[2,1]]
Output: []
Explanation: From the first two conditions,
3 has to be below 1 but the third conditions needs 3 to be above 1 to be satisfied.
No matrix can satisfy all the conditions, so we return the empty matrix.

Constraints:
2 <= k <= 400
1 <= rowConditions.length, colConditions.length <= 10^4
rowConditions[i].length == colConditions[i].length == 2
1 <= abovei, belowi, lefti, righti <= k
abovei != belowi
lefti != righti
```

<details><summary>Hint</summary>

```text
1. Can you think of the problem in terms of graphs?
2. What algorithm allows you to find the order of nodes in a graph?
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/build-a-matrix-with-conditions/solutions/2544099/gei-ding-tiao-jian-xia-gou-zao-ju-zhen-t-kra5/
struct LinkedNode {
    int dest;
    struct LinkedNode *next;
};
struct BinodeQueue {
    int *arr;
    int arrHead;
    int arrSize;
};
static void queuePush(struct BinodeQueue *queue, int x) {
    queue->arr[queue->arrHead + queue->arrSize] = x;
    queue->arrSize++;
}
static void queuePop(struct BinodeQueue *queue) {
    queue->arrHead++;
    queue->arrSize--;
}
static int topology(int **conditions, int conditionsSize, int k, struct LinkedNode *list, int *sites) {
    int retVal = 0;

    int i;

    int degreeSize = k + 1;
    int degree[degreeSize];
    memset(degree, 0, sizeof(degree));

    struct LinkedNode *head[k + 1];
    memset(head, 0, sizeof(head));

    int arr[k];
    memset(arr, 0, sizeof(arr));
    struct BinodeQueue degreeQueue;
    degreeQueue.arr = arr;
    degreeQueue.arrHead = 0;
    degreeQueue.arrSize = 0;

    for (i = 0; conditionsSize > i; ++i) {
        degree[conditions[i][1]]++;

        list[retVal].dest = conditions[i][1];
        list[retVal].next = head[conditions[i][0]];

        head[conditions[i][0]] = &list[retVal];

        retVal++;
    }

    for (i = 1; i < degreeSize; ++i) {
        if (degree[i] == 0) {
            queuePush(&degreeQueue, i);
        }
    }

    retVal = 0;
    struct LinkedNode *node = NULL;
    while (0 < degreeQueue.arrSize) {
        i = degreeQueue.arr[degreeQueue.arrHead];
        sites[i] = retVal;
        retVal++;
        queuePop(&degreeQueue);

        for (node = head[i]; node != NULL; node = node->next) {
            degree[node->dest]--;
            if (degree[node->dest] == 0) {
                queuePush(&degreeQueue, node->dest);
            }
        }
    }

    return retVal;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **buildMatrix(int k, int **rowConditions, int rowConditionsSize, int *rowConditionsColSize, int **colConditions,
                  int colConditionsSize, int *colConditionsColSize, int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    //
    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    //
    int buffSize = fmax(rowConditionsSize, colConditionsSize);
    struct LinkedNode list[buffSize];
    int sitesSize = k + 1;
    int sites[2][sitesSize];
    int ret = 0;
    ret = topology(rowConditions, rowConditionsSize, k, list, &sites[0][0]);
    if (ret != k) {
        return pRetVal;
    }
    ret = topology(colConditions, colConditionsSize, k, list, &sites[1][0]);
    if (ret != k) {
        return pRetVal;
    }

    //
    pRetVal = (int **)malloc(k * sizeof(int *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int *)malloc(k * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    //
    int i, j;
    for (i = 0; i < k; ++i) {
        pRetVal[i] = (int *)calloc(k, sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        (*returnColumnSizes)[i] = k;
        (*returnSize) += 1;
    }
    for (i = 1; i < sitesSize; ++i) {
        pRetVal[sites[0][i]][sites[1][i]] = i;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // Code to find the topologically sorted sequence using Kahn's algorithm.
    vector<int> topoSort(vector<vector<int>>& edges, int n) {
        vector<int> retVal;

        // Create an adjacency list to store the edges.
        vector<vector<int>> adjacency(n + 1);
        vector<int> degree(n + 1);
        for (auto edge : edges) {
            adjacency[edge[0]].emplace_back(edge[1]);
            degree[edge[1]]++;
        }

        // Push all integers with in-degree 0 in the queue.
        queue<int> degreeQueue;
        for (int i = 1; i <= n; i++) {
            if (degree[i] == 0) {
                degreeQueue.push(i);
            }
        }
        while (degreeQueue.empty() == false) {
            int order = degreeQueue.front();
            degreeQueue.pop();
            retVal.emplace_back(order);
            for (auto neighbor : adjacency[order]) {
                degree[neighbor]--;
                if (degree[neighbor] == 0) {
                    degreeQueue.push(neighbor);
                }
            }
            n--;
        }

        // If we have not visited all integers, return empty array.
        if (n != 0) {
            retVal.clear();
        }

        return retVal;
    }

   public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> retVal(k, vector<int>(k, 0));

        // Store the topologically sorted sequences.
        vector<int> orderRows = topoSort(rowConditions, k);
        vector<int> orderColumns = topoSort(colConditions, k);

        // If no topological sort exists, return empty array.
        if ((orderRows.empty() == true) or (orderColumns.empty() == true)) {
            retVal.clear();
            return retVal;
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (orderRows[i] == orderColumns[j]) {
                    retVal[i][j] = orderRows[i];
                }
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def topoSort(self, edges: List[List[int]], n: int) -> List[int]:
        retVal = []

        adjacency = [[] for _ in range(n + 1)]
        degree = [0] * (n + 1)
        for edge in edges:
            adjacency[edge[0]].append(edge[1])
            degree[edge[1]] += 1

        degreeQueue = deque()
        for i in range(1, n + 1):
            if degree[i] == 0:
                degreeQueue.append(i)
        while degreeQueue:
            order = degreeQueue.popleft()
            retVal.append(order)
            for neighbor in adjacency[order]:
                degree[neighbor] -= 1
                if degree[neighbor] == 0:
                    degreeQueue.append(neighbor)
            n -= 1

        if n != 0:
            retVal = []

        return retVal

    def buildMatrix(self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]) -> List[List[int]]:
        retVal = []

        orderRows = self.topoSort(rowConditions, k)
        orderColumns = self.topoSort(colConditions, k)
        if (not orderRows) or (not orderColumns):
            return retVal

        retVal = [[0] * k for _ in range(k)]
        for i in range(k):
            for j in range(k):
                if orderRows[i] == orderColumns[j]:
                    retVal[i][j] = orderRows[i]

        return retVal
```

</details>

## [2421. Number of Good Paths](https://leetcode.com/problems/number-of-good-paths/)  2444

- [Official](https://leetcode.com/problems/number-of-good-paths/solutions/2892908/number-of-good-paths/)

<details><summary>Description</summary>

```text
There is a tree (i.e. a connected, undirected graph with no cycles)
consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.

You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node.
You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes
that there exists an undirected edge connecting nodes ai and bi.

A good path is a simple path that satisfies the following conditions:
- The starting node and the ending node have the same value.
- All nodes between the starting node and the ending node have values less than or equal to the starting node
  (i.e. the starting node's value should be the maximum value along the path).

Return the number of distinct good paths.

Note that a path and its reverse are counted as the same path.
For example, 0 -> 1 is considered to be the same as 1 -> 0.
A single node is also considered as a valid path.
Example 1:
    (0:[1])
   /       \
(1:[3])   (2:[2])
         /       \
      (3:[1])   (4:[3])
Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
Output: 6
Explanation: There are 5 good paths consisting of a single node.
There is 1 additional good path: 1 -> 0 -> 2 -> 4.
(The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].

Example 2:
            (0:[1])
           /
        (1:[1])
       /
    (2:[2])
   /       \
(3:[2])   (4:[3])
Input: vals = [1,1,2,2,3], edges = [[0,1],[1,2],[2,3],[2,4]]
Output: 7
Explanation: There are 5 good paths consisting of a single node.
There are 2 additional good paths: 0 -> 1 and 2 -> 3.

Example 3:
(0:[1])
Input: vals = [1], edges = []
Output: 1
Explanation: The tree consists of only one node, so there is one good path.

Constraints:
n == vals.length
1 <= n <= 3 * 10^4
0 <= vals[i] <= 10^5
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/number-of-good-paths/solutions/1850357/by-priceless-brahmaguptatvb-ichm/
#define MAX_UNION_FIND (30010)
int find(int* root, int x) {
    if (root[x] != x) {
        root[x] = find(root, root[x]);
    }

    return root[x];
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int numberOfGoodPaths(int* vals, int n, int** edges, int edgesSize, int* edgesColSize) {
    int retVal = 0;

    int i, j;

    int sortedVals[MAX_UNION_FIND][2];
    for (i = 0; i < n; ++i) {
        sortedVals[i][0] = vals[i];
        sortedVals[i][1] = i;
    }
    qsort(sortedVals, n, sizeof(2 * sizeof(int)), compareInteger);

    int idx = 0;
    int e[2 * MAX_UNION_FIND];
    memset(e, 0, sizeof(e));
    int ne[2 * MAX_UNION_FIND];
    memset(ne, 0, sizeof(ne));
    int h[MAX_UNION_FIND];
    memset(h, -1, sizeof(h));
    for (i = 0; i < edgesSize; ++i) {
        e[idx] = edges[i][1];
        ne[idx] = h[edges[i][0]];
        h[edges[i][0]] = idx++;

        e[idx] = edges[i][0];
        ne[idx] = h[edges[i][1]];
        h[edges[i][1]] = idx++;
    }

    int root[MAX_UNION_FIND];
    int size[MAX_UNION_FIND];
    for (i = 0; i < n; i++) {
        root[i] = i;
        size[i] = 1;
    }

    int x;
    int y;
    for (retVal = n, i = 0; i < n; ++i) {
        x = find(root, sortedVals[i][1]);

        for (j = h[sortedVals[i][1]]; j != -1; j = ne[j]) {
            y = find(root, e[j]);
            if ((x != y) && (vals[y] <= sortedVals[i][0])) {
                if (vals[y] == sortedVals[i][0]) {
                    retVal += size[y] * size[x];
                    size[x] += size[y];
                }
                root[y] = x;
            }
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
// https://leetcode.com/problems/number-of-good-paths/solutions/3053175/leetcode-the-hard-way-explained-line-by-line/
class Solution {
   public:
    int find(vector<int>& root, int idx) {
        if (idx == root[idx]) {
            return idx;
        }
        root[idx] = find(root, root[idx]);

        return root[idx];
    }

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int retVal = 0;

        int n = vals.size();

        vector<int> root(n);
        for (int i = 0; i < n; i++) {
            root[i] = i;
        }

        sort(edges.begin(), edges.end(), [&](const vector<int>& x, const vector<int>& y) {
            return max(vals[x[0]], vals[x[1]]) < max(vals[y[0]], vals[y[1]]);
        });

        vector<int> cnt(n, 1);
        for (auto e : edges) {
            int x = e[0];
            x = find(root, x);

            int y = e[1];
            y = find(root, y);

            if (vals[x] == vals[y]) {
                retVal += cnt[x] * cnt[y];
                root[x] = y;
                cnt[y] += cnt[x];
            } else if (vals[x] > vals[y]) {
                root[y] = x;
            } else {
                root[x] = y;
            }
        }
        retVal += n;

        return retVal;
    }
};
```

</details>

## [2477. Minimum Fuel Cost to Report to the Capital](https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/)  2011

- [Official](https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/solutions/3080167/minimum-fuel-cost-to-report-to-the-capital/)

<details><summary>Description</summary>

```text
There is a tree (i.e., a connected, undirected graph with no cycles) structure country network
consisting of n cities numbered from 0 to n - 1 and exactly n - 1 roads.
The capital city is city 0.
You are given a 2D integer array roads where roads[i] = [ai, bi]
denotes that there exists a bidirectional road connecting cities ai and bi.

There is a meeting for the representatives of each city. The meeting is in the capital city.

There is a car in each city. You are given an integer seats that indicates the number of seats in each car.

A representative can use the car in their city to travel or change the car and ride with another representative.
The cost of traveling between two cities is one liter of fuel.

Return the minimum number of liters of fuel to reach the capital city.
```

```text
Example 1:
```

```mermaid
graph TD
    0((0))---1((1))
    0((0))---2((2))
    0((0))---3((3))
```

```text
Input: roads = [[0,1],[0,2],[0,3]], seats = 5
Output: 3
Explanation:
- Representative1 goes directly to the capital with 1 liter of fuel.
- Representative2 goes directly to the capital with 1 liter of fuel.
- Representative3 goes directly to the capital with 1 liter of fuel.
It costs 3 liters of fuel at minimum.
It can be proven that 3 is the minimum number of liters of fuel needed.
```

```text
Example 2:
```

```mermaid
graph TD
    3((3))---1((1))
    3((3))---2((2))
    1((1))---0((0))
    0((0))---4((4))
    0((0))---5((5))
    4((4))---6((6))
```

```text
Input: roads = [[3,1],[3,2],[1,0],[0,4],[0,5],[4,6]], seats = 2
Output: 7
Explanation:
- Representative2 goes directly to city 3 with 1 liter of fuel.
- Representative2 and representative3 go together to city 1 with 1 liter of fuel.
- Representative2 and representative3 go together to the capital with 1 liter of fuel.
- Representative1 goes directly to the capital with 1 liter of fuel.
- Representative5 goes directly to the capital with 1 liter of fuel.
- Representative6 goes directly to city 4 with 1 liter of fuel.
- Representative4 and representative6 go together to the capital with 1 liter of fuel.
It costs 7 liters of fuel at minimum.
It can be proven that 7 is the minimum number of liters of fuel needed.
```

```text
Example 3:
Input: roads = [], seats = 1
Output: 0
Explanation: No representatives need to travel to the capital city.
```

```text
Constraints:
1 <= n <= 10^5
roads.length == n - 1
roads[i].length == 2
0 <= ai, bi < n
ai != bi
roads represents a valid tree.
1 <= seats <= 10^5
```

<details><summary>Hint</summary>

```text
1. Can you record the size of each subtree?
2. If n people meet on the same node, what is the minimum number of cars needed?
```

</details>

</details>

<details><summary>C</summary>

```c
long long minimumFuelCost(int** roads, int roadsSize, int* roadsColSize, int seats) {
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long dfs(int node, int parent, vector<vector<int>>& adjacent, int seats, long long& fuel) {
        long long retVal = 1;

        for (int neighbor : adjacent[node]) {
            if (neighbor != parent) {
                retVal += dfs(neighbor, node, adjacent, seats, fuel);
            }
        }

        if (node != 0) {
            // Count the fuel it takes to move to the parent node. Root node does not have any parent so we ignore it.
            fuel += ceil((double)retVal / seats);
        }

        return retVal;
    }
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        long long retVal = 0;

        vector<vector<int>> adjacent(roads.size() + 1);
        for (auto& road : roads) {
            adjacent[road[0]].push_back(road[1]);
            adjacent[road[1]].push_back(road[0]);
        }
        dfs(0, -1, adjacent, seats, retVal);

        return retVal;
    }
};
```

</details>

## [2492. Minimum Score of a Path Between Two Cities](https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/)  1679

<details><summary>Description</summary>

```text
You are given a positive integer n representing n cities numbered from 1 to n.
You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates
that there is a bidirectional road between cities ai and bi with a distance equal to distancei.
The cities graph is not necessarily connected.

The score of a path between two cities is defined as the minimum distance of a road in this path.

Return the minimum possible score of a path between cities 1 and n.

Note:
A path is a sequence of roads between two cities.
It is allowed for a path to contain the same road multiple times,
and you can visit cities 1 and n multiple times along the path.
The test cases are generated such that there is at least one path between 1 and n.

Example 1:
     +-(1)-+
    7|     |9
    (4)---(2)
        5  |6
          (3)
Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
Output: 5
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
It can be shown that no other path has less score.

Example 2:
     +-(1)-+
    4|     |2
    (3)---(2)
    7|
    (4)
Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
Output: 2
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4.
The score of this path is min(2,2,4,7) = 2.

Constraints:
2 <= n <= 10^5
1 <= roads.length <= 10^5
roads[i].length == 3
1 <= ai, bi <= n
ai != bi
1 <= distancei <= 10^4
There are no repeated edges.
There is at least one path between 1 and n.
```

<details><summary>Hint</summary>

```text
1. Can you solve the problem if the whole graph is connected?
2. Notice that if the graph is connected, you can always use any edge of the graph in your path.
3. How to solve the general problem in a similar way? Remove all the nodes that are not connected to 1 and n,
   then apply the previous solution in the new graph.
```

</details>

</details>

<details><summary>C</summary>

```c
int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {

}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minScore(int n, vector<vector<int>>& roads) {
        int retVal = 0;

        int roadsSize = roads.size();

        //
        vector<pair<int, int>> adjacent[n + 1];
        for (int i = 0; i < roadsSize; ++i) {
            adjacent[roads[i][0]].push_back({roads[i][1], roads[i][2]});
            adjacent[roads[i][1]].push_back({roads[i][0], roads[i][2]});
        }

        // Breadth-First Search
        queue<int> bfsQueue;
        bfsQueue.push(1);

        vector<bool> visit(n + 1);
        visit[1] = true;

        retVal = numeric_limits<int>::max();
        while (bfsQueue.empty() == false) {
            int src = bfsQueue.front();
            bfsQueue.pop();

            for (auto& iterator : adjacent[src]) {
                int dest = iterator.first;
                if (visit[dest] == false) {
                    bfsQueue.push(dest);
                    visit[dest] = true;
                }

                int distance = iterator.second;
                retVal = (distance < retVal ? distance : retVal);
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
import queue    # Submit need extra import

class Solution:
    def __init__(self):
        # queue
        self.method = 1
        # deque
        self.method = 2

    def minScore(self, n: int, roads: List[List[int]]) -> int:
        retVal = sys.maxsize

        #
        adjacent = defaultdict(dict)
        for src, dest, distance in roads:
            adjacent[src][dest] = distance
            adjacent[dest][src] = distance

        # Breadth-First Search
        visit = set()

        if self.method == 1:
            print("import queue")

            bfsQueue = queue.Queue()
            bfsQueue.put(1)

            while bfsQueue.empty() == False:
                src = bfsQueue.get()
                for dest, distance in adjacent[src].items():
                    if dest not in visit:
                        bfsQueue.put(dest)
                        visit.add(dest)
                    retVal = min(retVal, distance)

        elif self.method == 2:
            print("from collections import deque")

            bfsQueue = deque([1])

            while bfsQueue:
                src = bfsQueue.popleft()
                for dest, distance in adjacent[src].items():
                    if dest not in visit:
                        bfsQueue.append(dest)
                        visit.add(dest)
                    retVal = min(retVal, distance)

        return retVal
```

</details>

## [2493. Divide Nodes Into the Maximum Number of Groups](https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/)  2415

- [Official](https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/editorial/)

<details><summary>Description</summary>

```text
You are given a positive integer n representing the number of nodes in an undirected graph.
The nodes are labeled from 1 to n.

You are also given a 2D integer array edges,
where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi.
Notice that the given graph may be disconnected.

Divide the nodes of the graph into m groups (1-indexed) such that:
- Each node in the graph belongs to exactly one group.
- For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x,
  and bi belongs to the group with index y, then |y - x| = 1.

Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes.
Return -1 if it is impossible to group the nodes with the given conditions.

Example 1:
Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
Output: 4
Explanation: As shown in the image we:
- Add node 5 to the first group.
- Add node 1 to the second group.
- Add nodes 2 and 4 to the third group.
- Add nodes 3 and 6 to the fourth group.
We can see that every edge is satisfied.
It can be shown that that if we create a fifth group and move any node from the third or fourth group to it,
at least on of the edges will not be satisfied.

Example 2:
Input: n = 3, edges = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: If we add node 1 to the first group, node 2 to the second group,
and node 3 to the third group to satisfy the first two edges, we can see that the third edge will not be satisfied.
It can be shown that no grouping is possible.

Constraints:
1 <= n <= 500
1 <= edges.length <= 10^4
edges[i].length == 2
1 <= ai, bi <= n
ai != bi
There is at most one edge between any pair of vertices.
```

<details><summary>Hint</summary>

```text
1. If the graph is not bipartite, it is not possible to group the nodes.
2. Notice that we can solve the problem for each connected component independently,
   and the final answer will be just the sum of the maximum number of groups in each component.
3. Finally, to solve the problem for each connected component,
   we can notice that if for some node v we fix its position to be in the leftmost group,
   then we can also evaluate the position of every other node.
   That position is the depth of the node in a bfs tree after rooting at node v.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef UnionFind_H
#define UnionFind_H

void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
int find(int node, int *parent) {
    int retVal = 0;

    while (parent[node] != -1) {
        node = parent[node];
    }
    retVal = node;

    return retVal;
}
void Union(int node1, int node2, int *parent, int *depth) {
    node1 = find(node1, parent);
    node2 = find(node2, parent);

    // If both nodes already belong to the same set, no action needed
    if (node1 == node2) {
        return;
    }

    // Union by rank (depth) to keep the tree balanced
    if (depth[node1] < depth[node2]) {
        swap(&node1, &node2);
    }
    parent[node2] = node1;

    // If the depths are equal, increment the depth of the new root
    if (depth[node1] == depth[node2]) {
        depth[node1]++;
    }
}

#endif  // UnionFind_H
int getNumberOfGroups(int **adjacencyList, int adjacencyListSize, int srcNode, int n) {
    int retVal = 0;

    // Perform BFS to calculate the number of layers (groups)
    int bfsQueueSize = n * n;
    int bfsQueue[bfsQueueSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueFront = 0;
    int bfsQueueRear = 0;
    bfsQueue[bfsQueueRear++] = srcNode;

    int layerSeen[n];
    for (int i = 0; i < n; ++i) {
        layerSeen[i] = -1;
    }
    layerSeen[srcNode] = 0;

    int bfsQueueCount, currentNode, neighbor;
    while (bfsQueueFront < bfsQueueRear) {
        bfsQueueCount = bfsQueueRear - bfsQueueFront;
        for (int i = 0; i < bfsQueueCount; i++) {
            currentNode = bfsQueue[bfsQueueFront++];

            for (int j = 0; j < adjacencyListSize; ++j) {
                neighbor = adjacencyList[currentNode][j];
                if (neighbor == -1) {
                    continue;
                }

                // If neighbor hasn't been visited, assign it to the next layer
                if (layerSeen[neighbor] == -1) {
                    layerSeen[neighbor] = retVal + 1;
                    bfsQueue[bfsQueueRear++] = neighbor;
                    continue;
                }

                // If the neighbor is already in the same layer, return -1 (invalid partition)
                if (layerSeen[neighbor] == retVal) {
                    retVal = -1;
                    return retVal;
                }
            }
        }
        retVal++;
    }

    return retVal;
}
int magnificentSets(int n, int **edges, int edgesSize, int *edgesColSize) {
    int retVal = 0;

    // Build the adjacency list and apply Union-Find for each edge
    int **adjacencyList = (int **)malloc(n * sizeof(int *));
    if (adjacencyList == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < n; ++i) {
        adjacencyList[i] = (int *)malloc(n * sizeof(int));
        if (adjacencyList[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(adjacencyList[j]);
                adjacencyList[j] = NULL;
            }
            free(adjacencyList);
            adjacencyList = NULL;
            return retVal;
        }
        for (int j = 0; j < n; ++j) {
            adjacencyList[i][j] = -1;
        }
    }

    int *parent = (int *)malloc(n * sizeof(int));
    if (parent == NULL) {
        perror("malloc");
        for (int i = 0; i < n; ++i) {
            free(adjacencyList[i]);
            adjacencyList[i] = NULL;
        }
        free(adjacencyList);
        adjacencyList = NULL;
        return retVal;
    }

    int *depth = (int *)malloc(n * sizeof(int));
    if (depth == NULL) {
        perror("malloc");
        free(parent);
        parent = NULL;
        for (int i = 0; i < n; ++i) {
            free(adjacencyList[i]);
            adjacencyList[i] = NULL;
        }
        free(adjacencyList);
        adjacencyList = NULL;
        return retVal;
    }
    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        depth[i] = 0;
    }

    int src, dst;
    for (int i = 0; i < edgesSize; ++i) {
        src = edges[i][0] - 1;
        dst = edges[i][1] - 1;
        adjacencyList[src][dst] = dst;
        adjacencyList[dst][src] = src;
        Union(src, dst, parent, depth);
    }

    // For each node, calculate the maximum number of groups for its component
    int numOfGroupsForComponent[n];
    for (int i = 0; i < n; ++i) {
        numOfGroupsForComponent[i] = -1;
    }

    int numberOfGroups, rootNode;
    for (int node = 0; node < n; node++) {
        numberOfGroups = getNumberOfGroups(adjacencyList, n, node, n);
        if (numberOfGroups == -1) {
            retVal = -1;  // If invalid split, return -1
            break;
        }
        rootNode = find(node, parent);
        numOfGroupsForComponent[rootNode] = fmax(numOfGroupsForComponent[rootNode], numberOfGroups);
    }

    // Calculate the total number of groups across all components
    if (retVal != -1) {
        for (int i = 0; i < n; ++i) {
            if (numOfGroupsForComponent[i] == -1) {
                continue;
            }
            retVal += numOfGroupsForComponent[i];
        }
    }

    //
    free(depth);
    depth = NULL;
    free(parent);
    parent = NULL;
    for (int i = 0; i < n; ++i) {
        free(adjacencyList[i]);
        adjacencyList[i] = NULL;
    }
    free(adjacencyList);
    adjacencyList = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class UnionFind {
   public:
    int n;
    vector<int> parent;
    vector<int> depth;

    UnionFind(int _n) : n(_n), parent(_n, -1), depth(_n, 0) {}
    int find(int node) {
        int retVal = 0;

        while (parent[node] != -1) {
            node = parent[node];
        }
        retVal = node;

        return retVal;
    }
    void Union(int node1, int node2) {
        node1 = find(node1);
        node2 = find(node2);

        // If both nodes already belong to the same set, no action needed
        if (node1 == node2) {
            return;
        }

        // Union by rank (depth) to keep the tree balanced
        if (depth[node1] < depth[node2]) {
            swap(node1, node2);
        }
        parent[node2] = node1;

        // If the depths are equal, increment the depth of the new root
        if (depth[node1] == depth[node2]) {
            depth[node1]++;
        }
    }
};
class Solution {
   private:
    int getNumberOfGroups(vector<vector<int>> &adjacencyList, int srcNode, int n) {
        int retVal = 0;

        // Perform BFS to calculate the number of layers (groups)
        queue<int> bfsQueue;
        bfsQueue.push(srcNode);
        vector<int> layerSeen(n, -1);
        layerSeen[srcNode] = 0;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; i++) {
                int currentNode = bfsQueue.front();
                bfsQueue.pop();
                for (int neighbor : adjacencyList[currentNode]) {
                    // If neighbor hasn't been visited, assign it to the next layer
                    if (layerSeen[neighbor] == -1) {
                        layerSeen[neighbor] = retVal + 1;
                        bfsQueue.push(neighbor);
                        continue;
                    }

                    // If the neighbor is already in the same layer, return -1 (invalid partition)
                    if (layerSeen[neighbor] == retVal) {
                        retVal = -1;
                        return retVal;
                    }
                }
            }
            retVal++;
        }

        return retVal;
    }

   public:
    int magnificentSets(int n, vector<vector<int>> &edges) {
        int retVal = 0;

        // Build the adjacency list and apply Union-Find for each edge
        vector<vector<int>> adjacencyList(n);
        UnionFind uf(n);
        for (auto edge : edges) {
            adjacencyList[edge[0] - 1].push_back(edge[1] - 1);
            adjacencyList[edge[1] - 1].push_back(edge[0] - 1);
            uf.Union(edge[0] - 1, edge[1] - 1);
        }

        // For each node, calculate the maximum number of groups for its component
        unordered_map<int, int> numOfGroupsForComponent;
        for (int node = 0; node < n; node++) {
            int numberOfGroups = getNumberOfGroups(adjacencyList, node, n);
            if (numberOfGroups == -1) {
                retVal = -1;  // If invalid split, return -1
                return retVal;
            }

            int rootNode = uf.find(node);
            numOfGroupsForComponent[rootNode] = max(numOfGroupsForComponent[rootNode], numberOfGroups);
        }

        // Calculate the total number of groups across all components
        for (auto [rootNode, numberOfGroups] : numOfGroupsForComponent) {
            retVal += numberOfGroups;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class UnionFind:
    def __init__(self, n: int):
        self.parent = [-1] * n
        self.depth = [0] * n

    def find(self, node) -> int:
        retVal = 0

        while self.parent[node] != -1:
            node = self.parent[node]
        retVal = node

        return retVal

    def union(self, node1, node2) -> None:
        node1 = self.find(node1)
        node2 = self.find(node2)

        # If both nodes already belong to the same set, no action needed
        if node1 == node2:
            return

        # Union by rank (depth) to keep the tree balanced
        if self.depth[node1] < self.depth[node2]:
            node1, node2 = node2, node1
        self.parent[node2] = node1

        # If the depths are equal, increment the depth of the new root
        if self.depth[node1] == self.depth[node2]:
            self.depth[node1] += 1


class Solution:
    def getNumberOfGroups(self, adjacencyList, srcNode, n) -> int:
        retVal = 0

        bfsQueue = deque()
        bfsQueue.append(srcNode)
        layerSeen = [-1] * n
        layerSeen[srcNode] = 0
        while bfsQueue:
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                currentNode = bfsQueue.popleft()
                for neighbor in adjacencyList[currentNode]:
                    if layerSeen[neighbor] == -1:  # If neighbor hasn't been visited, assign it to the next layer
                        layerSeen[neighbor] = retVal + 1
                        bfsQueue.append(neighbor)
                        continue

                    # If the neighbor is already in the same layer, return -1 (invalid partition)
                    if layerSeen[neighbor] == retVal:
                        retVal = -1
                        return retVal
            retVal += 1

        return retVal

    def magnificentSets(self, n: int, edges: List[List[int]]) -> int:
        retVal = -1  # If invalid split, return -1

        # Build the adjacency list and apply Union-Find for each edge
        adjacencyList = [[] for _ in range(n)]
        uf = UnionFind(n)
        for edge in edges:
            adjacencyList[edge[0] - 1].append(edge[1] - 1)
            adjacencyList[edge[1] - 1].append(edge[0] - 1)
            uf.union(edge[0] - 1, edge[1] - 1)

        # For each node, calculate the maximum number of groups for its component
        numOfGroupsForComponent = {}
        for node in range(n):
            numberOfGroups = self.getNumberOfGroups(adjacencyList, node, n)
            if numberOfGroups == -1:
                return retVal

            rootNode = uf.find(node)
            numOfGroupsForComponent[rootNode] = max(numOfGroupsForComponent.get(rootNode, 0), numberOfGroups)

        # Calculate the total number of groups across all components
        retVal = sum(numOfGroupsForComponent.values())

        return retVal
```

</details>

## [2577. Minimum Time to Visit a Cell In a Grid](https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/)  2381

- [Official](https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/editorial/)

<details><summary>Description</summary>

```text
You are given a m x n matrix grid consisting of non-negative integers
where grid[row][col] represents the minimum time required to be able to visit the cell (row, col),
which means you can visit the cell (row, col) only
when the time you visit it is greater than or equal to grid[row][col].

You are standing in the top-left cell of the matrix in the 0th second,
and you must move to any adjacent cell in the four directions: up, down, left, and right.
Each move you make takes 1 second.

Return the minimum time required in which you can visit the bottom-right cell of the matrix.
If you cannot visit the bottom-right cell, then return -1.

Example 1:
Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
Output: 7
Explanation: One of the paths that we can take is the following:
- at t = 0, we are on the cell (0,0).
- at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
- at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
- at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
- at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
- at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
- at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
- at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
The final time is 7. It can be shown that it is the minimum time possible.

Example 2:
Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
Output: -1
Explanation: There is no path from the top left to the bottom-right cell.

Constraints:
m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 10^5
0 <= grid[i][j] <= 10^5
grid[0][0] == 0
```

<details><summary>Hint</summary>

```text
1. Try using some algorithm that can find the shortest paths on a graph.
2. Consider the case where you have to go back and forth between two cells of the matrix to unlock some other cells.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/minimum-time-to-visit-a-cell-in-a-grid/solutions/2521039/zai-wang-ge-tu-zhong-fang-wen-yi-ge-ge-z-l4jw/
#ifndef HEAP_H
#define HEAP_H

#define MERGE_LONG(t, x, y) ((long long)(t) << 32 | (long long)(x) << 16 | (long long)(y))
#define ROW_INT(l) ((l) >> 16 & 0xFFFF)
#define COL_INT(l) ((l) & 0xFFFF)
#define FATHER_NODE(i) (0 == (i) ? -1 : (((i) - 1) >> 1))
#define LEFT_NODE(i) (((i) << 1) + 1)
#define RIGHT_NODE(i) (((i) << 1) + 2)

typedef struct {
    long long *arr;
    int arrSize;
} PriorityQueue;

static void queuePush(PriorityQueue *queue, long long value) {
    int son = queue->arrSize;
    int father = FATHER_NODE(son);

    queue->arrSize++;
    while ((-1 != father) && (value < queue->arr[father])) {
        queue->arr[son] = queue->arr[father];
        son = father;
        father = FATHER_NODE(son);
    }
    queue->arr[son] = value;
}
static void queuePop(PriorityQueue *queue) {
    int father = 0;
    int left = LEFT_NODE(father);
    int right = RIGHT_NODE(father);
    int son = 0;

    queue->arrSize--;
    while (((queue->arrSize > left) && (queue->arr[queue->arrSize] > queue->arr[left])) ||
           ((queue->arrSize > right) && (queue->arr[queue->arrSize] > queue->arr[right]))) {
        son = (queue->arrSize > right && queue->arr[left] > queue->arr[right]) ? right : left;
        queue->arr[father] = queue->arr[son];
        father = son;
        left = LEFT_NODE(father);
        right = RIGHT_NODE(father);
    }
    queue->arr[father] = queue->arr[queue->arrSize];
}

#endif  // HEAP_H
int minimumTime(int **grid, int gridSize, int *gridColSize) {
    int retVal = -1;

    if ((1 < grid[0][1]) && (1 < grid[1][0])) {
        return retVal;
    }

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    int arrive[rowSize][colSize];
    memset(arrive, -1, sizeof(arrive));
    arrive[0][0] = 0;

    int totalSize = rowSize * colSize;
    long long arr[totalSize];
    PriorityQueue queue;
    queue.arr = arr;
    queue.arrSize = 0;
    queuePush(&queue, MERGE_LONG(arrive[0][0], 0, 0));

    const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int x, y, nextRow, nextCol;
    while ((0 < queue.arrSize) && (-1 == arrive[rowSize - 1][colSize - 1])) {
        x = ROW_INT(queue.arr[0]);
        y = COL_INT(queue.arr[0]);
        queuePop(&queue);

        for (int i = 0; ((i < 4) && (-1 == arrive[rowSize - 1][colSize - 1])); ++i) {
            nextRow = x + directions[i][0];
            nextCol = y + directions[i][1];
            if (nextRow < 0) {
                continue;
            } else if (nextRow >= rowSize) {
                continue;
            } else if (nextCol < 0) {
                continue;
            } else if (nextCol >= colSize) {
                continue;
            } else if (arrive[nextRow][nextCol] != -1) {
                continue;
            }

            if (arrive[x][y] + 1 >= grid[nextRow][nextCol]) {
                arrive[nextRow][nextCol] = arrive[x][y] + 1;
            } else {
                arrive[nextRow][nextCol] = grid[nextRow][nextCol] + ((grid[nextRow][nextCol] - arrive[x][y] + 1) & 1);
            }
            queuePush(&queue, MERGE_LONG(arrive[nextRow][nextCol], nextRow, nextCol));
        }
    }
    retVal = arrive[rowSize - 1][colSize - 1];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool isValid(vector<vector<bool>>& visited, int row, int col) {
        bool retVal = true;

        int visitedSize = visited.size();
        int visitedColSize = visited[0].size();
        if (row < 0) {
            retVal = false;
        } else if (row >= visitedSize) {
            retVal = false;
        } else if (col < 0) {
            retVal = false;
        } else if (col >= visitedColSize) {
            retVal = false;
        } else if (visited[row][col] == true) {
            retVal = false;
        }

        return retVal;
    }

   public:
    int minimumTime(vector<vector<int>>& grid) {
        int retVal = -1;

        // If both initial moves require more than 1 second, impossible to proceed
        if ((grid[0][1] > 1) && (grid[1][0] > 1)) {
            return retVal;
        }

        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Possible movements: down, up, right, left
        vector<vector<bool>> visited(gridSize, vector<bool>(gridColSize, false));

        // Priority queue stores {time, row, col}, Ordered by minimum time to reach each cell.
        priority_queue<vector<int>, vector<vector<int>>, greater<>> priorityQueue;
        priorityQueue.push({grid[0][0], 0, 0});

        while (priorityQueue.empty() == false) {
            auto curr = priorityQueue.top();
            priorityQueue.pop();

            int time = curr[0];
            int row = curr[1];
            int col = curr[2];
            if ((row == gridSize - 1) && (col == gridColSize - 1)) {  // Check if reached target
                retVal = time;
                return retVal;
            }

            // Skip if cell already visited
            if (visited[row][col]) {
                continue;
            }
            visited[row][col] = true;

            // Try all four directions
            for (auto& d : directions) {
                int nextRow = row + d[0];
                int nextCol = col + d[1];
                if (isValid(visited, nextRow, nextCol) == false) {
                    continue;
                }

                // Calculate the wait time needed to move to next cell
                int waitTime = ((grid[nextRow][nextCol] - time) % 2 == 0) ? 1 : 0;
                int nextTime = max(grid[nextRow][nextCol] + waitTime, time + 1);
                priorityQueue.push({nextTime, nextRow, nextCol});
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    def isValid(self, visited: set, row: int, col: int, gridSize: int, gridColSize: int) -> bool:
        retVal = True

        if (row, col) in visited:
            retVal = False
        elif row < 0:
            retVal = False
        elif row >= gridSize:
            retVal = False
        elif col < 0:
            retVal = False
        elif col >= gridColSize:
            retVal = False

        return retVal

    def minimumTime(self, grid: List[List[int]]) -> int:
        retVal = -1

        # If both initial moves require more than 1 second, impossible to proceed
        if (grid[0][1] > 1) and (grid[1][0] > 1):
            return retVal

        gridSize = len(grid)
        gridColSize = len(grid[0])

        visited = set()

        # Priority queue stores (time, row, col), Ordered by minimum time to reach each cell.
        priorityQueue = [(grid[0][0], 0, 0)]
        while priorityQueue:
            time, row, col = heappop(priorityQueue)

            # Check if reached target
            if (row, col) == (gridSize - 1, gridColSize - 1):
                retVal = time
                return retVal

            # Skip if cell already visited
            if (row, col) in visited:
                continue
            visited.add((row, col))

            # Try all four directions
            for dx, dy in self.directions:
                nextRow = row + dx
                nextCol = col + dy
                if self.isValid(visited, nextRow, nextCol, gridSize, gridColSize) == False:
                    continue

                # Calculate the wait time needed to move to next cell
                waitTime = 0
                if (grid[nextRow][nextCol] - time) % 2 == 0:
                    waitTime = 1

                nextTime = max(grid[nextRow][nextCol] + waitTime, time + 1)
                heappush(priorityQueue, (nextTime, nextRow, nextCol))

        return retVal
```

</details>

## [2642. Design Graph With Shortest Path Calculator](https://leetcode.com/problems/design-graph-with-shortest-path-calculator/description/)  1810

- [Official](https://leetcode.com/problems/design-graph-with-shortest-path-calculator/editorial/)

<details><summary>Description</summary>

```text
There is a directed weighted graph that consists of n nodes numbered from 0 to n - 1.
The edges of the graph are initially represented by the given array edges
where edges[i] = [fromi, toi, edgeCosti] meaning that there is an edge from fromi to toi with the cost edgeCosti.

Implement the Graph class:
- Graph(int n, int[][] edges)
    initializes the object with n nodes and the given edges.
- addEdge(int[] edge)
    adds an edge to the list of edges where edge = [from, to, edgeCost].
    It is guaranteed that there is no edge between the two nodes before adding this one.
- int shortestPath(int node1, int node2)
    returns the minimum cost of a path from node1 to node2.
    If no path exists, return -1. The cost of a path is the sum of the costs of the edges in the path.

Example 1:
Input
["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
Output
[null, 6, -1, null, 6]
Explanation
Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
g.shortestPath(3, 2);
// return 6.
   The shortest path from 3 to 2 in the first diagram above is 3 -> 0 -> 1 -> 2 with a total cost of 3 + 2 + 1 = 6.
g.shortestPath(0, 3);
// return -1. There is no path from 0 to 3.
g.addEdge([1, 3, 4]);
// We add an edge from node 1 to node 3, and we get the second diagram above.
g.shortestPath(0, 3);
// return 6. The shortest path from 0 to 3 now is 0 -> 1 -> 3 with a total cost of 2 + 4 = 6.

Constraints:
1 <= n <= 100
0 <= edges.length <= n * (n - 1)
edges[i].length == edge.length == 3
0 <= fromi, toi, from, to, node1, node2 <= n - 1
1 <= edgeCosti, edgeCost <= 10^6
There are no repeated edges and no self-loops in the graph at any point.
At most 100 calls will be made for addEdge.
At most 100 calls will be made for shortestPath.
```

<details><summary>Hint</summary>

```text
1. After adding each edge, update your graph with the new edge,
   and you can calculate the shortest path in your graph each time the shortestPath method is called.
2. Use dijkstra’s algorithm to calculate the shortest paths.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    int* vetr;
    int vetr_num;
    int** vetr_edge;
} Graph;
Graph* graphCreate(int n, int** edges, int edgesSize, int* edgesColSize) {
    Graph* obj = (Graph*)malloc(sizeof(Graph));

    int i;

    obj->vetr = (int*)calloc(n, sizeof(int));
    for (i = 0; i < n; i++) {
        obj->vetr[i] = i;
    }

    obj->vetr_num = n;

    obj->vetr_edge = (int**)calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        obj->vetr_edge[i] = (int*)calloc(n, sizeof(int));
    }
    for (i = 0; i < edgesSize; i++) {
        obj->vetr_edge[edges[i][0]][edges[i][1]] = edges[i][2];
    }

    return obj;
}
void graphAddEdge(Graph* obj, int* edge, int edgeSize) {
    //
    obj->vetr_edge[edge[0]][edge[1]] = edge[2];
}
int graphShortestPath(Graph* obj, int node1, int node2) {
    int retVal = 0;

    int* path = (int*)calloc(obj->vetr_num, sizeof(int));
    int i;
    for (i = 0; i < obj->vetr_num; i++) {
        path[i] = -1;
    }

    int judge[obj->vetr_num];
    memset(judge, 0, sizeof(judge));
    path[node1] = 0;

    int node;
    int min[2];
    while (1) {
        min[0] = -1;
        min[1] = -1;

        for (node = 0; node < obj->vetr_num; node++) {
            if (path[node] != -1 && judge[node] == 0) {
                if (min[0] == -1) {
                    min[0] = node;
                    min[1] = path[node];
                } else {
                    if (min[1] > path[node]) {
                        min[0] = node;
                        min[1] = path[node];
                    }
                }
            }
        }

        if (min[0] != -1) {
            judge[min[0]] = 1;
            for (i = 0; i < obj->vetr_num; i++) {
                if ((obj->vetr_edge[min[0]][i] != 0) && (judge[i] == 0)) {
                    if (path[i] == -1) {
                        path[i] = path[min[0]] + obj->vetr_edge[min[0]][i];
                    } else {
                        node = path[min[0]] + obj->vetr_edge[min[0]][i];
                        path[i] = ((path[i] > node) ? (node) : (path[i]));
                    }
                }
            }
        } else {
            break;
        }
    }

    retVal = path[node2];

    free(path);
    path = NULL;

    return retVal;
}
void graphFree(Graph* obj) {
    int i;
    for (i = 0; i < obj->vetr_num; i++) {
        free(obj->vetr_edge[i]);
        obj->vetr_edge[i] = NULL;
    }
    free(obj->vetr_edge);
    obj->vetr_edge = NULL;

    free(obj->vetr);
    obj->vetr = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your Graph struct will be instantiated and called as such:
 * Graph* obj = graphCreate(n, edges, edgesSize, edgesColSize);
 * graphAddEdge(obj, edge, edgeSize);
 * int param_2 = graphShortestPath(obj, node1, node2);
 * graphFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class Graph {
   public:
    vector<vector<pair<int, int>>> adjList;
    Graph(int n, vector<vector<int>>& edges) {
        adjList.resize(n);
        for (auto& e : edges) {
            adjList[e[0]].push_back(make_pair(e[1], e[2]));
        }
    }
    void addEdge(vector<int> edge) {
        //
        adjList[edge[0]].push_back(make_pair(edge[1], edge[2]));
    }
    int shortestPath(int node1, int node2) {
        int retVal = -1;

        int n = adjList.size();
        vector<int> costForNode(n, numeric_limits<int>::max());
        costForNode[node1] = 0;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, node1});
        while (pq.empty() == false) {
            int currCost = pq.top()[0];
            int currNode = pq.top()[1];
            pq.pop();
            if (currCost > costForNode[currNode]) {
                continue;
            }

            if (currNode == node2) {
                retVal = currCost;
                break;
            }

            for (auto& neighbor : adjList[currNode]) {
                int neighborNode = neighbor.first;
                int cost = neighbor.second;
                int newCost = currCost + cost;
                if (newCost < costForNode[neighborNode]) {
                    costForNode[neighborNode] = newCost;
                    pq.push({newCost, neighborNode});
                }
            }
        }

        return retVal;
    }
};
/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
```

</details>

<details><summary>Python3</summary>

```python
class Graph:
    def __init__(self, n: int, edges: List[List[int]]):
        self.adj_list = [[] for _ in range(n)]
        for from_node, to_node, cost in edges:
            self.adj_list[from_node].append((to_node, cost))

    def addEdge(self, edge: List[int]) -> None:
        from_node, to_node, cost = edge
        self.adj_list[from_node].append((to_node, cost))

    def shortestPath(self, node1: int, node2: int) -> int:
        retVal = -1

        n = len(self.adj_list)
        cost_for_node = [float('inf')] * (n)
        cost_for_node[node1] = 0

        pq = [(0, node1)]
        while pq:
            curr_cost, curr_node = heappop(pq)
            if curr_cost > cost_for_node[curr_node]:
                continue

            if curr_node == node2:
                retVal = curr_cost
                break

            for neighbor, cost in self.adj_list[curr_node]:
                new_cost = curr_cost + cost
                if new_cost < cost_for_node[neighbor]:
                    cost_for_node[neighbor] = new_cost
                    heappush(pq, (new_cost, neighbor))

        return retVal


# Your Graph object will be instantiated and called as such:
# obj = Graph(n, edges)
# obj.addEdge(edge)
# param_2 = obj.shortestPath(node1,node2)
```

</details>

## [2658. Maximum Number of Fish in a Grid](https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/)  1489

- [Official](https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
- A land cell if grid[r][c] = 0, or
- A water cell containing grid[r][c] fish, if grid[r][c] > 0.

A fisher can start at any water cell (r, c) and can do the following operations any number of times:
- Catch all the fish at cell (r, c), or
- Move to any adjacent water cell.

Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally,
or 0 if no water cell exists.

An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.

Example 1:
Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
Output: 7
Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.

Example 2:
Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
Output: 1
Explanation: The fisher can start at cells (0,0) or (3,3) and collect a single fish.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 10
0 <= grid[i][j] <= 10
```

<details><summary>Hint</summary>

```text
1. Run DFS from each non-zero cell.
2. Each time you pick a cell to start from, add up the number of fish contained in the cells you visit.
```

</details>

</details>

<details><summary>C</summary>

```c
int bfs(int** grid, int rowSize, int colSize, bool** pVisited, int row, int col) {
    int retVal = 0;

    int bfsQueueSize = 4 * rowSize * colSize;
    int bfsQueue[bfsQueueSize][2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueFront = 0;
    int bfsQueueRear = 0;
    bfsQueue[bfsQueueRear][0] = row;
    bfsQueue[bfsQueueRear][1] = col;
    bfsQueueRear++;

    pVisited[row][col] = true;

    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int x, y, nextX, nextY;
    while (bfsQueueFront < bfsQueueRear) {
        x = bfsQueue[bfsQueueFront][0];
        y = bfsQueue[bfsQueueFront][1];
        bfsQueueFront++;

        retVal += grid[x][y];

        for (int dir = 0; dir < 4; ++dir) {
            nextX = x + directions[dir][0];
            nextY = y + directions[dir][1];
            if ((nextX < 0) || (nextX >= rowSize) || (nextY < 0) || (nextY >= colSize)) {
                continue;
            }

            if ((grid[nextX][nextY] != 0) && (pVisited[nextX][nextY] == false)) {
                bfsQueue[bfsQueueRear][0] = nextX;
                bfsQueue[bfsQueueRear][1] = nextY;
                bfsQueueRear++;
                pVisited[nextX][nextY] = true;
            }
        }
    }

    return retVal;
}
int findMaxFish(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    bool** pVisited = (bool**)malloc(rowSize * sizeof(bool*));
    if (pVisited == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < rowSize; ++i) {
        pVisited[i] = (bool*)malloc(colSize * sizeof(bool));
        if (pVisited[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pVisited[j]);
                pVisited[j] = NULL;
            }
            free(pVisited);
            pVisited = NULL;
            return retVal;
        }
        memset(pVisited[i], false, (colSize * sizeof(bool)));
    }
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if ((grid[i][j] != 0) && (pVisited[i][j] == false)) {
                retVal = fmax(retVal, bfs(grid, rowSize, colSize, pVisited, i, j));
            }
        }
    }

    //
    for (int i = 0; i < rowSize; ++i) {
        free(pVisited[i]);
        pVisited[i] = NULL;
    }
    free(pVisited);
    pVisited = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int row, int col) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({row, col});
        visited[row][col] = true;
        const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (bfsQueue.empty() == false) {
            int x = bfsQueue.front().first;
            int y = bfsQueue.front().second;
            bfsQueue.pop();
            retVal += grid[x][y];

            for (auto& direction : directions) {
                int nextX = x + direction[0];
                int nextY = y + direction[1];
                if ((nextX < 0) || (nextX >= rowSize) || (nextY < 0) || (nextY >= colSize)) {
                    continue;
                }

                if ((grid[nextX][nextY] != 0) && (visited[nextX][nextY] == false)) {
                    bfsQueue.push({nextX, nextY});
                    visited[nextX][nextY] = true;
                }
            }
        }

        return retVal;
    }

   public:
    int findMaxFish(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<vector<bool>> visited(rowSize, vector<bool>(colSize));
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                if ((grid[i][j] != 0) && (visited[i][j] == false)) {
                    retVal = max(retVal, bfs(grid, visited, i, j));
                }
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def bfs(self, grid, visited, row, col) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        bfsQueue = [(row, col)]
        visited[row][col] = True
        directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        while bfsQueue:
            x, y = bfsQueue.pop(0)
            retVal += grid[x][y]

            for dx, dy in directions:
                nextX = x + dx
                nextY = y + dy
                if (nextX < 0) or (nextX >= rowSize) or (nextY < 0) or (nextY >= colSize):
                    continue

                if (grid[nextX][nextY] != 0) and (visited[nextX][nextY] == False):
                    bfsQueue.append((nextX, nextY))
                    visited[nextX][nextY] = True

        return retVal

    def findMaxFish(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        visited = [[False] * colSize for _ in range(rowSize)]
        for i in range(rowSize):
            for j in range(colSize):
                if (grid[i][j] != 0) and (visited[i][j] == False):
                    retVal = max(retVal, self.bfs(grid, visited, i, j))

        return retVal
```

</details>

## [2699. Modify Graph Edge Weights](https://leetcode.com/problems/modify-graph-edge-weights/)  2873

- [Official](https://leetcode.com/problems/modify-graph-edge-weights/editorial/)
- [Official](https://leetcode.cn/problems/modify-graph-edge-weights/solutions/2300101/xiu-gai-tu-zhong-de-bian-quan-by-leetcod-66bg/)

<details><summary>Description</summary>

```text
You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1,
and an integer array edges where edges[i] = [ai, bi, wi] indicates that
there is an edge between nodes ai and bi with weight wi.

Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).

Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2*10^9]
so that the shortest distance between the nodes source and destination becomes equal to an integer target.
If there are multiple modifications that make the shortest distance between source and destination equal to target,
any of them will be considered correct.

Return an array containing all edges (even unmodified ones) in any order
if it is possible to make the shortest distance from source to destination equal to target,
or an empty array if it's impossible.

Note: You are not allowed to modify the weights of edges with initial positive weights.

Example 1:
Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.

Example 2:
Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2, target = 6
Output: []
Explanation: The graph above contains the initial edges.
It is not possible to make the distance from 0 to 2 equal to 6 by modifying the edge with weight -1.
So, an empty array is returned.

Example 3:
Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0, destination = 2, target = 6
Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
Explanation: The graph above shows a modified graph having the shortest distance from 0 to 2 as 6.

Constraints:
1 <= n <= 100
1 <= edges.length <= n * (n - 1) / 2
edges[i].length == 3
0 <= ai, bi < n
wi = -1 or 1 <= wi <= 10^7
ai != bi
0 <= source, destination < n
source != destination
1 <= target <= 10^9
The graph is connected, and there are no self-loops or repeated edges
```

<details><summary>Hint</summary>

```text
1. Firstly, check that it’s actually possible to make the shortest path from source to destination equal to the target.
2. If the shortest path from source to destination without the edges to be modified, is less than the target,
   then it is not possible.
3. If the shortest path from source to destination including the edges to be modified
   and assigning them a temporary weight of 1, is greater than the target, then it is also not possible.
4. Suppose we can find a modifiable edge (u, v) such that the length of the shortest path
   from source to u (dis1) plus the length of the shortest path from v to destination (dis2) is less than
   target (dis1 + dis2 < target), then we can change its weight to "target - dis1 - dis2".
5. For all the other edges that still have the weight "-1,"
   change the weights into sufficient large number (target, target + 1 or 200000000 etc.).
```

</details>

</details>

<details><summary>C</summary>

```c
long long *fromDestination = NULL;
long long *dijkstra(int op, int source, int n, int **edges, int edgesSize, int *edgesColSize, int **adjacency,
                    int *checkTarget) {
    long long *pRetVal = NULL;

    int i;

    pRetVal = (long long *)malloc(n * sizeof(long long));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(long long)));
    for (i = 0; i < n; ++i) {
        pRetVal[i] = LLONG_MAX / 2;
    }
    pRetVal[source] = 0;

    bool visited[n];
    memset(visited, false, sizeof(visited));

    int u, v;
    int round;
    for (round = 0; round < n - 1; ++round) {
        u = -1;
        for (i = 0; i < n; ++i) {
            if (visited[i] == true) {
                continue;
            }

            if ((u == -1) || (pRetVal[i] < pRetVal[u])) {
                u = i;
            }
        }
        visited[u] = true;

        for (v = 0; v < n; ++v) {
            if (visited[v] == true) {
                continue;
            } else if (adjacency[u][v] == -1) {
                continue;
            }

            if (edges[adjacency[u][v]][2] != -1) {
                pRetVal[v] = fmin(pRetVal[v], pRetVal[u] + edges[adjacency[u][v]][2]);
                continue;
            }

            if (op == 0) {
                pRetVal[v] = fmin(pRetVal[v], pRetVal[u] + 1);
            } else {
                int modify = (*checkTarget) - pRetVal[u] - fromDestination[v];
                if (modify > 0) {
                    pRetVal[v] = fmin(pRetVal[v], pRetVal[u] + modify);
                    edges[adjacency[u][v]][2] = modify;
                } else {
                    edges[adjacency[u][v]][2] = (*checkTarget);
                }
            }
        }
    }

    return pRetVal;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **modifiedGraphEdges(int n, int **edges, int edgesSize, int *edgesColSize, int source, int destination, int target,
                         int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    int **adjacency = (int **)malloc(n * sizeof(int *));
    if (adjacency == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < n; ++i) {
        adjacency[i] = (int *)malloc(n * sizeof(int));
        if (adjacency[i] == NULL) {
            perror("malloc");
            goto exit_adjacency;
        }
        for (j = 0; j < n; ++j) {
            adjacency[i][j] = -1;
        }
    }
    for (i = 0; i < edgesSize; ++i) {
        adjacency[edges[i][0]][edges[i][1]] = i;
        adjacency[edges[i][1]][edges[i][0]] = i;
    }

    fromDestination = NULL;
    int checkTarget = target;
    fromDestination = dijkstra(0, destination, n, edges, edgesSize, edgesColSize, adjacency, &checkTarget);
    if (fromDestination == NULL) {
        perror("malloc");
        goto exit_adjacency;
    }
    if (fromDestination[source] > target) {
        goto exit_fromDestination;
    }

    long long *fromSource = dijkstra(1, source, n, edges, edgesSize, edgesColSize, adjacency, &checkTarget);
    if (fromDestination == NULL) {
        perror("malloc");
        goto exit_fromDestination;
    }
    if (fromSource[destination] != target) {
        goto exit_fromSource;
    }

    //
    pRetVal = edges;
    (*returnSize) = edgesSize;
    (*returnColumnSizes) = edgesColSize;

exit_fromSource:
    free(fromSource);
    fromSource = NULL;

exit_fromDestination:
    free(fromDestination);
    fromDestination = NULL;

exit_adjacency:
    for (i = 0; i < n; ++i) {
        if (adjacency[i] != NULL) {
            free(adjacency[i]);
            adjacency[i] = NULL;
        }
    }
    free(adjacency);
    adjacency = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<long long> fromDestination;
    int target;

    vector<long long> dijkstra(int op, int source, vector<vector<int>>& edges, const vector<vector<int>>& adjacency) {
        vector<long long> retVal;

        int n = adjacency.size();
        vector<long long> distance(n, numeric_limits<int>::max() / 2);
        distance[source] = 0;
        vector<int> visited(n);

        for (int round = 0; round < n - 1; ++round) {
            int u = -1;
            for (int i = 0; i < n; ++i) {
                if (visited[i] == true) {
                    continue;
                }

                if ((u == -1) || (distance[i] < distance[u])) {
                    u = i;
                }
            }
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (visited[v] == true) {
                    continue;
                } else if (adjacency[u][v] == -1) {
                    continue;
                }

                if (edges[adjacency[u][v]][2] != -1) {
                    distance[v] = min(distance[v], distance[u] + edges[adjacency[u][v]][2]);
                    continue;
                }

                if (op == 0) {
                    distance[v] = min(distance[v], distance[u] + 1);
                } else {
                    int modify = target - distance[u] - fromDestination[v];
                    if (modify > 0) {
                        distance[v] = min(distance[v], distance[u] + modify);
                        edges[adjacency[u][v]][2] = modify;
                    } else {
                        edges[adjacency[u][v]][2] = target;
                    }
                }
            }
        }
        retVal = distance;

        return retVal;
    }

   public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        vector<vector<int>> retVal;

        this->target = target;

        vector<vector<int>> adjacency(n, vector<int>(n, -1));
        int edgesSize = edges.size();
        for (int i = 0; i < edgesSize; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            adjacency[u][v] = i;
            adjacency[v][u] = i;
        }

        fromDestination = dijkstra(0, destination, edges, adjacency);
        if (fromDestination[source] > target) {
            return retVal;
        }

        vector<long long> fromSource = dijkstra(1, source, edges, adjacency);
        if (fromSource[destination] != target) {
            return retVal;
        }

        retVal = edges;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.fromDestination = None
        self.target = 0

    def dijkstra(self, option: int, source: int, n: int, edges: List[List[int]], adjacency: List[List[int]]) -> List[int]:
        retVal = []

        distance = [float("inf")] * n
        distance[source] = 0

        visited = [False] * n

        for _ in range(n - 1):
            u = -1
            for i in range(n):
                if visited[i] == True:
                    continue
                if ((u == -1) or (distance[i] < distance[u])):
                    u = i
            visited[u] = True

            for v in range(n):
                if visited[v] == True:
                    continue
                elif adjacency[u][v] == -1:
                    continue

                if edges[adjacency[u][v]][2] != -1:
                    distance[v] = min(distance[v], distance[u] + edges[adjacency[u][v]][2])
                    continue

                if option == 0:
                    distance[v] = min(distance[v], distance[u] + 1)
                else:
                    modify = self.target - distance[u] - self.fromDestination[v]
                    if modify > 0:
                        distance[v] = min(distance[v], distance[u] + modify)
                        edges[adjacency[u][v]][2] = modify
                    else:
                        edges[adjacency[u][v]][2] = self.target

        retVal = distance

        return retVal

    def modifiedGraphEdges(self, n: int, edges: List[List[int]], source: int, destination: int, target: int) -> List[List[int]]:
        retVal = []

        self.fromDestination = []
        self.target = target

        adjacency = [[-1] * n for _ in range(n)]
        for i, (u, v, w) in enumerate(edges):
            adjacency[u][v] = adjacency[v][u] = i

        self.fromDestination = self.dijkstra(0, destination, n, edges, adjacency)
        if self.fromDestination[source] > target:
            return retVal

        fromSource = self.dijkstra(1, source, n, edges, adjacency)
        if fromSource[destination] != target:
            return retVal

        retVal = edges

        return retVal
```

</details>

## [2709. Greatest Common Divisor Traversal](https://leetcode.com/problems/greatest-common-divisor-traversal/)  2171

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices.
You can traverse between index i and index j, i != j,
if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.

Your task is to determine if for every pair of indices i and j in nums, where i < j,
there exists a sequence of traversals that can take us from i to j.

Return true if it is possible to traverse between all such pairs of indices, or false otherwise.

Example 1:
Input: nums = [2,3,6]
Output: true
Explanation: In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2 -> 1,
where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1,
and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1.
Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.

Example 2:
Input: nums = [3,9,5]
Output: false
Explanation: No sequence of traversals can take us from index 0 to index 2 in this example. So, we return false.

Example 3:
Input: nums = [4,3,12,8]
Output: true
Explanation:
There are 6 possible pairs of indices to traverse between: (0, 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3).
A valid sequence of traversals exists for each pair, so we return true.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Create a (prime) factor-numbers list for all the indices.
2. Add an edge between the neighbors of the (prime) factor-numbers list. The order of the numbers doesn’t matter.
   We only need edges between 2 neighbors instead of edges for all pairs.
3. The problem is now similar to checking if all the numbers (nodes of the graph) are in the same connected component.
4. Any algorithm (i.e., BFS, DFS, or Union-Find Set) should work to find or check connected components
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/greatest-common-divisor-traversal/
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
struct DisjointSetUnion {
    int* f;
    int* size;
    int n;
    int setCount;
};
int initDSU(struct DisjointSetUnion* obj, int n) {
    obj->f = (int*)malloc(n * sizeof(int));
    if (obj->f == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    memset(obj->f, 0, (n * sizeof(int)));

    obj->size = (int*)malloc(n * sizeof(int));
    if (obj->size == NULL) {
        perror("malloc");
        free(obj->f);
        obj->f = NULL;
        return EXIT_FAILURE;
    }
    memset(obj->size, 0, (n * sizeof(int)));

    int i;
    for (i = 0; i < n; i++) {
        obj->f[i] = i;
        obj->size[i] = 1;
    }
    obj->n = n;
    obj->setCount = n;

    return EXIT_SUCCESS;
}
int find(struct DisjointSetUnion* obj, int x) {
    int retVal = x;

    if (obj->f[x] != x) {
        obj->f[x] = find(obj, obj->f[x]);
        retVal = obj->f[x];
    }

    return retVal;
}
bool unionSet(struct DisjointSetUnion* obj, int x, int y) {
    bool retVal = false;

    int fx = find(obj, x);
    int fy = find(obj, y);
    if (fx == fy) {
        return retVal;
    }

    if (obj->size[fx] < obj->size[fy]) {
        swap(&fx, &fy);
    }
    obj->size[fx] += obj->size[fy];
    obj->f[fy] = fx;
    obj->setCount--;
    retVal = true;

    return retVal;
}
bool canTraverseAllPairs(int* nums, int numsSize) {
    bool retVal = true;

    if (numsSize == 1) {
        return retVal;
    }

    struct DisjointSetUnion* ufa = (struct DisjointSetUnion*)malloc(sizeof(struct DisjointSetUnion));
    if (ufa == NULL) {
        perror("malloc");
        return retVal;
    }
    if (initDSU(ufa, numsSize) == EXIT_FAILURE) {
        perror("malloc");
        free(ufa);
        ufa = NULL;
        return retVal;
    }

    int i;

    int maxVal = 0;
    for (i = 0; i < numsSize; i++) {
        maxVal = fmax(maxVal, nums[i]);
    }

    int occured[maxVal + 1];
    memset(occured, -1, sizeof(occured));
    for (i = 0; i < numsSize; i++) {
        if (occured[nums[i]] == -1) {
            occured[nums[i]] = i;
        } else if (nums[i] == 1) {
            retVal = false;
            goto exit;
        } else {
            ufa->setCount--;
        }
    }

    int j;
    int subGcd;
    for (i = 2; i <= maxVal; i++) {
        subGcd = -1;
        for (j = i; j <= maxVal; j += i) {
            if (occured[j] != -1) {
                if (subGcd == -1) {
                    subGcd = occured[j];
                } else {
                    unionSet(ufa, subGcd, occured[j]);
                    subGcd = occured[j];
                }
            }
        }
    }

    if (ufa->setCount != 1) {
        retVal = false;
    }

exit:
    free(ufa->f);
    ufa->f = NULL;
    free(ufa->size);
    ufa->size = NULL;
    free(ufa);
    ufa = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
    // https://leetcode.com/problems/greatest-common-divisor-traversal/solutions/4778264/mastering-javascript-python-python3-and-c-achieved-100-00-efficiency/
   private:
    int findSetLeader(vector<int>& disjointSet, int x) {
        int retVal = x;

        if (disjointSet[x] == x) {
            return retVal;
        }
        disjointSet[x] = findSetLeader(disjointSet, disjointSet[x]);
        retVal = disjointSet[x];

        return retVal;
    }
    void unionSets(vector<int>& disjointSet, vector<int>& setSize, int x, int y) {
        int xLeader = findSetLeader(disjointSet, x);
        int yLeader = findSetLeader(disjointSet, y);
        if (xLeader == yLeader) {
            return;
        }

        if (setSize[xLeader] < setSize[yLeader]) {
            disjointSet[xLeader] = yLeader;
            setSize[yLeader] += setSize[xLeader];
        } else {
            disjointSet[yLeader] = xLeader;
            setSize[xLeader] += setSize[yLeader];
        }
    }

   public:
    bool canTraverseAllPairs(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        if (numsSize == 1) {
            return retVal;
        }

        vector<int> disjointSet(numsSize);
        vector<int> setSize(numsSize, 1);
        unordered_map<int, int> factorFirstOccurrence;
        for (int i = 0; i < numsSize; ++i) {
            disjointSet[i] = i;

            int num = nums[i];
            int divisor = 2;
            while (divisor * divisor <= num) {
                if (num % divisor == 0) {
                    if (factorFirstOccurrence.find(divisor) != factorFirstOccurrence.end()) {
                        unionSets(disjointSet, setSize, i, factorFirstOccurrence[divisor]);
                    } else {
                        factorFirstOccurrence[divisor] = i;
                    }

                    while (num % divisor == 0) {
                        num /= divisor;
                    }
                }
                divisor++;
            }

            if (num > 1) {
                if (factorFirstOccurrence.find(num) != factorFirstOccurrence.end()) {
                    unionSets(disjointSet, setSize, i, factorFirstOccurrence[num]);
                } else {
                    factorFirstOccurrence[num] = i;
                }
            }
        }
        retVal = setSize[findSetLeader(disjointSet, 0)] == numsSize;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://leetcode.com/problems/greatest-common-divisor-traversal/solutions/4778264/mastering-javascript-python-python3-and-c-achieved-100-00-efficiency/
    def __init__(self) -> None:
        self.disjoint_set = []
        self.set_size = []
        self.factor_first_occurrence = {}

    def find_set_leader(self, x) -> int:
        retVal = x

        if self.disjoint_set[x] == x:
            return retVal

        self.disjoint_set[x] = self.find_set_leader(self.disjoint_set[x])
        retVal = self.disjoint_set[x]

        return retVal

    def union_sets(self, x, y) -> None:
        x_leader = self.find_set_leader(x)
        y_leader = self.find_set_leader(y)
        if x_leader == y_leader:
            return

        if self.set_size[x_leader] < self.set_size[y_leader]:
            self.disjoint_set[x_leader] = y_leader
            self.set_size[y_leader] += self.set_size[x_leader]
        else:
            self.disjoint_set[y_leader] = x_leader
            self.set_size[x_leader] += self.set_size[y_leader]

    def canTraverseAllPairs(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        if numsSize == 1:
            return retVal

        self.disjoint_set = [i for i in range(numsSize)]
        self.set_size = [1] * numsSize
        self.factor_first_occurrence = {}

        for i, num in enumerate(nums):
            divisor = 2
            while divisor * divisor <= num:
                if num % divisor == 0:
                    if divisor in self.factor_first_occurrence:
                        self.union_sets(i, self.factor_first_occurrence[divisor])
                    else:
                        self.factor_first_occurrence[divisor] = i

                    while num % divisor == 0:
                        num //= divisor

                divisor += 1

            if num > 1:
                if num in self.factor_first_occurrence:
                    self.union_sets(i, self.factor_first_occurrence[num])
                else:
                    self.factor_first_occurrence[num] = i

        retVal = self.set_size[self.find_set_leader(0)] == numsSize

        return retVal
```

</details>

## [2812. Find the Safest Path in a Grid](https://leetcode.com/problems/find-the-safest-path-in-a-grid/)  2153

- [Official](https://leetcode.com/problems/find-the-safest-path-in-a-grid/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
- A cell containing a thief if grid[r][c] = 1
- An empty cell if grid[r][c] = 0

You are initially positioned at cell (0, 0).
In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

The safeness factor of a path on the grid is defined as the minimum manhattan distance
from any cell in the path to any thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|,
where |val| denotes the absolute value of val.

Example 1:
Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
Output: 0
Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).

Example 2:
Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 2) is cell (0, 0).
  The distance between them is | 0 - 0 | + | 0 - 2 | = 2.
It can be shown that there are no other paths with a higher safeness factor.

Example 3:
Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 3) is cell (1, 2).
  The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
- The closest cell of the path to the thief at cell (3, 0) is cell (3, 2).
  The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
It can be shown that there are no other paths with a higher safeness factor.

Constraints:
1 <= grid.length == n <= 400
grid[i].length == n
grid[i][j] is either 0 or 1.
There is at least one thief in the grid.
```

<details><summary>Hint</summary>

```text
1. Consider using both BFS and binary search together.
2. Launch a BFS starting from all the cells containing thieves to calculate d[x][y]
   which is the smallest Manhattan distance from (x, y) to the nearest grid that contains thieves.
3. To check if the bottom-right cell of the grid can be reached **through a path of safeness factor v**,
   eliminate all cells (x, y) such that grid[x][y] < v.
   if (0, 0) and (n - 1, n - 1) are still connected,
   there exists a path between (0, 0) and (n - 1, n - 1) of safeness factor v.
4. Binary search over the final safeness factor v.
```

</details>

</details>

<details><summary>C</summary>

```c
const int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
bool enable(int** grid, int gridSize, int* gridColSize, int target) {
    bool retVal = false;

    if (grid[0][0] < target) {
        return retVal;
    }

    int queueSize = gridSize * gridColSize[0];
    int queue[queueSize][2];
    memset(queue, 0, sizeof(queueSize));
    int queueHead = 0;
    int queueTail = 0;
    queue[queueTail][0] = 0;
    queue[queueTail][1] = 0;
    queueTail++;

    int pathSize = gridSize * gridColSize[0];
    int path[pathSize];
    memset(path, 0, sizeof(path));
    path[0] = 1;

    int diffX, diffY;
    int currentX, currentY;
    int i;
    while (queueHead < queueTail) {
        currentX = queue[queueHead][0];
        currentY = queue[queueHead][1];
        queueHead++;
        if ((currentX == gridSize - 1) && (currentY == gridColSize[0] - 1)) {
            retVal = true;
            break;
        }

        for (i = 0; i < 4; i++) {
            diffX = currentX + direction[i][0];
            diffY = currentY + direction[i][1];
            if ((diffX < 0) || (diffX >= gridSize) || (diffY < 0) || (diffY >= gridColSize[0]) ||
                (grid[diffX][diffY] < target) || (path[diffX * gridColSize[0] + diffY] == 1)) {
                continue;
            }

            path[diffX * gridColSize[0] + diffY] = 1;
            queue[queueTail][0] = diffX;
            queue[queueTail][1] = diffY;
            queueTail++;
        }
    }

    return retVal;
}
int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    if ((grid[0][0] == 1) || (grid[gridSize - 1][gridColSize[0] - 1] == 1)) {
        return retVal;
    }

    int i, j;

    int multiSourceQueueSize = gridSize * gridColSize[0];
    int multiSourceQueue[multiSourceQueueSize][2];
    memset(multiSourceQueue, 0, sizeof(multiSourceQueue));
    int multiSourceQueueHead = 0;
    int multiSourceQueueTail = 0;
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == 1) {
                grid[i][j] = 0;
                multiSourceQueue[multiSourceQueueTail][0] = i;
                multiSourceQueue[multiSourceQueueTail][1] = j;
                multiSourceQueueTail++;
            } else {
                grid[i][j] = -1;
            }
        }
    }

    int diffX, diffY;
    int currentX, currentY;
    while (multiSourceQueueHead < multiSourceQueueTail) {
        currentX = multiSourceQueue[multiSourceQueueHead][0];
        currentY = multiSourceQueue[multiSourceQueueHead][1];
        multiSourceQueueHead++;

        for (i = 0; i < 4; i++) {
            diffX = currentX + direction[i][0];
            diffY = currentY + direction[i][1];
            if ((diffX < 0) || (diffX >= gridSize) || (diffY < 0) || (diffY >= gridColSize[0]) ||
                (grid[diffX][diffY] >= 0)) {
                continue;
            }
            grid[diffX][diffY] = grid[currentX][currentY] + 1;
            multiSourceQueue[multiSourceQueueTail][0] = diffX;
            multiSourceQueue[multiSourceQueueTail][1] = diffY;
            multiSourceQueueTail++;
        }
    }

    int left = 0;
    int right = fmin(gridSize, gridColSize[0]);
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;

        if (enable(grid, gridSize, gridColSize, middle) == true) {
            left = middle + 1;
            retVal = middle;
        } else {
            right = middle - 1;
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    bool isValidCell(vector<vector<int>>& grid, int i, int j) {
        bool retVal = false;

        int gridSize = grid.size();
        if ((i >= 0) && (i < gridSize) && (j >= 0) && (j < gridSize)) {
            retVal = true;
        }

        return retVal;
    }

   public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int retVal = -1;

        int gridSize = grid.size();

        // Mark thieves as 0 and empty cells as -1, and push thieves to the queue
        queue<pair<int, int>> multiSourceQueue;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j] == 1) {
                    multiSourceQueue.push({i, j});
                    grid[i][j] = 0;
                } else {
                    grid[i][j] = -1;
                }
            }
        }

        // Calculate safeness factor for each cell using BFS
        while (multiSourceQueue.empty() == false) {
            int multiSourceQueueSize = multiSourceQueue.size();
            while (multiSourceQueueSize-- > 0) {
                auto curr = multiSourceQueue.front();
                multiSourceQueue.pop();

                // Check neighboring cells
                for (auto& d : direction) {
                    int di = curr.first + d[0];
                    int dj = curr.second + d[1];
                    int val = grid[curr.first][curr.second];

                    // Check if the neighboring cell is valid and unvisited
                    if ((isValidCell(grid, di, dj) == true) && (grid[di][dj] == -1)) {
                        grid[di][dj] = val + 1;
                        multiSourceQueue.push({di, dj});
                    }
                }
            }
        }

        // Priority queue to prioritize cells with higher safeness factor, Push starting cell to the priority queue.
        priority_queue<vector<int>> pq;
        pq.push(vector<int>{grid[0][0], 0, 0});  // [maximum_safeness_till_now, x-coordinate, y-coordinate]
        grid[0][0] = -1;                         // Mark the source cell as visited

        // BFS to find the path with maximum safeness factor
        while (pq.empty() == false) {
            auto curr = pq.top();
            pq.pop();

            // If reached the destination, return safeness factor
            if ((curr[1] == gridSize - 1) && (curr[2] == gridSize - 1)) {
                retVal = curr[0];
                break;
            }

            // Explore neighboring cells
            for (auto& d : direction) {
                int di = d[0] + curr[1];
                int dj = d[1] + curr[2];
                if (isValidCell(grid, di, dj) && grid[di][dj] != -1) {
                    // Update safeness factor for the path and mark the cell as visited
                    pq.push(vector<int>{min(curr[0], grid[di][dj]), di, dj});
                    grid[di][dj] = -1;
                }
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.direction = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    def isValidCell(self, grid: List[List[int]], i: int, j: int) -> bool:
        retVal = False

        gridSize = len(grid)
        if (0 <= i < gridSize) and (0 <= j < gridSize):
            retVal = True

        return retVal

    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        retVal = -1

        gridSize = len(grid)

        # Mark thieves as 0 and empty cells as -1, and push thieves to the queue
        multi_source_queue = deque()
        for i in range(gridSize):
            for j in range(gridSize):
                if grid[i][j] == 1:
                    # Push thief coordinates to the queue
                    multi_source_queue.append((i, j))
                    grid[i][j] = 0  # Mark thief cell with 0
                else:
                    grid[i][j] = -1  # Mark empty cell with -1

        # Calculate safeness factor for each cell using BFS
        while multi_source_queue:
            size = len(multi_source_queue)
            while size > 0:
                # Check neighboring cells
                curr = multi_source_queue.popleft()
                for d in self.direction:
                    di = curr[0] + d[0]
                    dj = curr[1] + d[1]
                    val = grid[curr[0]][curr[1]]

                    # Check if the cell is valid and unvisited
                    if self.isValidCell(grid, di, dj) and grid[di][dj] == -1:
                        # Update safeness factor and push to the queue
                        grid[di][dj] = val + 1
                        multi_source_queue.append((di, dj))

                size -= 1

        # Priority queue to prioritize cells with higher safeness factor
        # [maximum_safeness_till_now, x-coordinate, y-coordinate]
        pq = [[-grid[0][0], 0, 0]]
        grid[0][0] = -1  # Mark the source cell as visited

        # BFS to find the path with maximum safeness factor
        while pq:
            retVal, i, j = heappop(pq)

            # If reached the destination, return safeness factor
            if (i == gridSize - 1) and (j == gridSize - 1):
                return -retVal

            # Check neighboring cells
            for d in self.direction:
                di = i + d[0]
                dj = j + d[1]

                # Check if the neighboring cell is valid and unvisited
                if self.isValidCell(grid, di, dj) and grid[di][dj] != -1:
                    heappush(pq, [-min(-retVal, grid[di][dj]), di, dj])
                    grid[di][dj] = -1

        return retVal
```

</details>

## [2924. Find Champion II](https://leetcode.com/problems/find-champion-ii/)  1430

- [Official](https://leetcode.com/problems/find-champion-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-champion-ii/solutions/2718321/zhao-dao-guan-jun-ii-by-leetcode-solutio-4x5y/)

<details><summary>Description</summary>

```text
There are n teams numbered from 0 to n - 1 in a tournament; each team is also a node in a DAG.

You are given the integer n and a 0-indexed 2D integer array edges of length m representing the DAG,
where edges[i] = [ui, vi] indicates that there is a directed edge from team ui to team vi in the graph.

A directed edge from a to b in the graph means that team a is stronger than team b and team b is weaker than team a.

Team a will be the champion of the tournament if there is no team b that is stronger than team a.

Return the team that will be the champion of the tournament if there is a unique champion, otherwise, return -1.

Notes
- A cycle is a series of nodes a1, a2, ..., an, an+1
  such that node a1 is the same node as node an+1, the nodes a1, a2, ..., an are distinct,
  and there is a directed edge from the node ai to node ai+1 for every i in the range [1, n].
- A DAG is a directed graph that does not have any cycle.

Example 1:
Input: n = 3, edges = [[0,1],[1,2]]
Output: 0
Explanation: Team 1 is weaker than team 0. Team 2 is weaker than team 1. So the champion is team 0.

Example 2:
Input: n = 4, edges = [[0,2],[1,3],[1,2]]
Output: -1
Explanation: Team 2 is weaker than team 0 and team 1. Team 3 is weaker than team 1.
But team 1 and team 0 are not weaker than any other teams. So the answer is -1.

Constraints:
1 <= n <= 100
m == edges.length
0 <= m <= n * (n - 1) / 2
edges[i].length == 2
0 <= edge[i][j] <= n - 1
edges[i][0] != edges[i][1]
The input is generated such that if team a is stronger than team b, team b is not stronger than team a.
The input is generated such that if team a is stronger than team b and team b is stronger than team c,
then team a is stronger than team c.
```

<details><summary>Hint</summary>

```text
1. The champion(s) should have in-degree 0 in the DAG.
```

</details>

</details>

<details><summary>C</summary>

```c
int findChampion(int n, int **edges, int edgesSize, int *edgesColSize) {
    int retVal = -1;

    int indegree[n];
    memset(indegree, 0, sizeof(indegree));

    int i;
    for (i = 0; i < edgesSize; ++i) {
        indegree[edges[i][1]] += 1;
    }

    for (i = 0; i < n; ++i) {
        if (indegree[i] != 0) {
            continue;
        }

        if (retVal == -1) {
            retVal = i;
        } else {
            retVal = -1;
            break;
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findChampion(int n, vector<vector<int>>& edges) {
        int retVal = -1;

        vector<int> indegree(n, 0);
        for (auto edge : edges) {
            indegree[edge[1]] += 1;
        }

        for (int i = 0; i < n; ++i) {
            if (indegree[i] != 0) {
                continue;
            }

            if (retVal == -1) {
                retVal = i;
            } else {
                retVal = -1;
                break;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        retVal = -1

        indegree = [0] * n
        for edge in edges:
            indegree[edge[1]] += 1

        for i in range(n):
            if indegree[i] != 0:
                continue

            if retVal == -1:
                retVal = i
            else:
                retVal = -1
                break

        return retVal
```

</details>

## [2976. Minimum Cost to Convert String I](https://leetcode.com/problems/minimum-cost-to-convert-string-i/)  1882

- [Official](https://leetcode.com/problems/minimum-cost-to-convert-string-i/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters.
You are also given two 0-indexed character arrays original and changed, and an integer array cost,
where cost[i] represents the cost of changing the character original[i] to the character changed[i].

You start with the string source.
In one operation, you can pick a character x from the string and change it to the character y at a cost of z
if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.

Return the minimum cost to convert the string source to the string target using any number of operations.
If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].

Example 1:
Input: source = "abcd", target = "acbe",
original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert the string "abcd" to string "acbe":
- Change value at index 1 from 'b' to 'c' at a cost of 5.
- Change value at index 2 from 'c' to 'e' at a cost of 1.
- Change value at index 2 from 'e' to 'b' at a cost of 2.
- Change value at index 3 from 'd' to 'e' at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28.
It can be shown that this is the minimum possible cost.

Example 2:
Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
Output: 12
Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1,
followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3.
To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.

Example 3:
Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
Output: -1
Explanation: It is impossible to convert source to target
because the value at index 3 cannot be changed from 'd' to 'e'.

Constraints:
1 <= source.length == target.length <= 10^5
source, target consist of lowercase English letters.
1 <= cost.length == original.length == changed.length <= 2000
original[i], changed[i] are lowercase English letters.
1 <= cost[i] <= 10^6
original[i] != changed[i]
```

<details><summary>Hint</summary>

```text
1. Construct a graph with each letter as a node, and construct an edge (a, b) with weight c
   if we can change from character a to letter b with cost c.
   (Keep the one with the smallest cost in case there are multiple edges between a and b).
2. Calculate the shortest path for each pair of characters (source[i], target[i]).
   The sum of cost over all i in the range [0, source.length - 1].
   If there is no path between source[i] and target[i], the answer is -1.
3. Any shortest path algorithms will work since we only have 26 nodes.
   Since we only have at most 26 * 26 pairs, we can save the result to avoid re-calculation.
4. We can also use Floyd Warshall's algorithm to precompute all the results.
```

</details>

</details>

<details><summary>C</summary>

```c
// source, target consist of lowercase English letters. original[i], changed[i] are lowercase English letters.
#define MAX_LETTERS (26)
long long minimumCost(char* source, char* target, char* original, int originalSize, char* changed, int changedSize,
                      int* cost, int costSize) {
    long long retVal = 0;

    int i, j, k;

    long long distance[MAX_LETTERS][MAX_LETTERS];
    for (i = 0; i < MAX_LETTERS; i++) {
        for (j = 0; j < MAX_LETTERS; j++) {
            distance[i][j] = INT_MAX;
        }
        distance[i][i] = 0;
    }
    int originalIdx, changedIdx;
    for (i = 0; i < originalSize; i++) {
        originalIdx = original[i] - 'a';
        changedIdx = changed[i] - 'a';
        distance[originalIdx][changedIdx] = fmin(cost[i], distance[originalIdx][changedIdx]);
    }
    for (k = 0; k < MAX_LETTERS; k++) {
        for (i = 0; i < MAX_LETTERS; i++) {
            for (j = 0; j < MAX_LETTERS; j++) {
                distance[i][j] = fmin(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    int sourceIdx, targetIdx;
    int sourceSize = strlen(source);
    for (i = 0; i < sourceSize; i++) {
        if (source[i] == target[i]) {
            continue;
        }

        sourceIdx = source[i] - 'a';
        targetIdx = target[i] - 'a';
        if (distance[sourceIdx][targetIdx] >= INT_MAX) {
            retVal = -1;  // If it is impossible to convert source to target, return -1.
            return retVal;
        }
        retVal += (distance[sourceIdx][targetIdx]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // source, target consist of lowercase English letters.
    // original[i], changed[i] are lowercase English letters.
    int letters = 26;

    vector<long long> dijkstra(int startChar, const vector<vector<pair<int, int>>>& adjacencyList) {
        vector<long long> retVal(letters, -1);

        // Priority queue to store characters with their conversion cost, sorted by cost
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> priorityQueue;
        priorityQueue.push({0, startChar});
        while (priorityQueue.empty() == false) {
            auto [currentCost, currentChar] = priorityQueue.top();
            priorityQueue.pop();

            if ((retVal[currentChar] != -1) && (retVal[currentChar] < currentCost)) {
                continue;
            }

            // Explore all possible conversions from the current character
            for (auto& [targetChar, conversionCost] : adjacencyList[currentChar]) {
                long long newTotalCost = currentCost + conversionCost;

                // If we found a cheaper conversion, update its cost
                if ((retVal[targetChar] == -1) || (newTotalCost < retVal[targetChar])) {
                    retVal[targetChar] = newTotalCost;
                    priorityQueue.push({newTotalCost, targetChar});
                }
            }
        }

        return retVal;
    }

   public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed,
                          vector<int>& cost) {
        long long retVal = 0;

        vector<vector<pair<int, int>>> adjacencyList(letters);
        int originalSize = original.size();
        for (int i = 0; i < originalSize; i++) {
            adjacencyList[original[i] - 'a'].push_back({changed[i] - 'a', cost[i]});
        }

        vector<vector<long long>> minConversionCosts(26, vector<long long>(letters));
        for (int i = 0; i < letters; i++) {
            minConversionCosts[i] = dijkstra(i, adjacencyList);
        }

        int sourceSize = source.length();
        for (int i = 0; i < sourceSize; i++) {
            if (source[i] != target[i]) {
                long long charConversionCost = minConversionCosts[source[i] - 'a'][target[i] - 'a'];
                if (charConversionCost == -1) {
                    retVal = -1;  // If it is impossible to convert source to target, return -1.
                    return retVal;
                }
                retVal += charConversionCost;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        # source, target consist of lowercase English letters.
        # original[i], changed[i] are lowercase English letters.
        self.letters = 26

    def dijkstra(self, startChar: int, adjacencyList: List[List[tuple]]) -> List[int]:
        retVal = [float("inf")] * self.letters

        # Priority queue to store characters with their conversion cost, sorted by cost
        priorityQueue = [(0, startChar)]
        while priorityQueue:
            currentCost, currentChar = heappop(priorityQueue)

            if retVal[currentChar] != float("inf"):
                continue
            retVal[currentChar] = currentCost

            # Explore all possible conversions from the current character
            for targetChar, conversionCost in adjacencyList[currentChar]:
                newTotalCost = currentCost + conversionCost

                # If we found a cheaper conversion, update its cost
                if retVal[targetChar] == float("inf"):
                    heappush(priorityQueue, (newTotalCost, targetChar))

        return retVal

    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        retVal = 0

        adjacencyList = [[] for _ in range(self.letters)]
        originalSize = len(original)
        for i in range(originalSize):
            originalIdx = ord(original[i]) - ord("a")
            changedIdx = ord(changed[i]) - ord("a")
            adjacencyList[originalIdx].append((changedIdx, cost[i]))

        # Calculate shortest paths for all possible character conversions
        minConversionCosts = []
        for i in range(self.letters):
            minCost = self.dijkstra(i, adjacencyList)
            minConversionCosts.append(minCost)

        # Calculate the total cost of converting source to target
        for s, t in zip(source, target):
            if s == t:
                continue

            sIdx = ord(s) - ord("a")
            tIdx = ord(t) - ord("a")
            charConversionCost = minConversionCosts[sIdx][tIdx]
            if charConversionCost == float("inf"):
                # If it is impossible to convert source to target, return -1.
                retVal = -1
                return retVal
            retVal += charConversionCost

        return retVal
```

</details>

## [3203. Find Minimum Diameter After Merging Two Trees](https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/)  2266

- [Official](https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/editorial/)

<details><summary>Description</summary>

```text
There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively.
You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1,
respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and
edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.

You must connect one node from the first tree with another node from the second tree with an edge.

Return the minimum possible diameter of the resulting tree.

The diameter of a tree is the length of the longest path between any two nodes in the tree.

Example 1:
Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
Output: 3
Explanation:
We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.

Example 2:
Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
Output: 5
Explanation:
We can obtain a tree of diameter 5 by connecting node 0 from the first tree with node 0 from the second tree.

Constraints:
1 <= n, m <= 10^5
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
```

<details><summary>Hint</summary>

```text
1. Suppose that we connected node a in tree1 with node b in tree2.
   The diameter length of the resulting tree will be the largest of the following 3 values:
   - The diameter of tree 1.
   - The diameter of tree 2.
   - The length of the longest path that starts at node a and
     that is completely within Tree 1 + The length of the longest path
     that starts at node b and that is completely within Tree 2 + 1.
   The added one in the third value is due to the additional edge that we have added between trees 1 and 2.
2. Values 1 and 2 are constant regardless of our choice of a and b.
   Therefore, we need to pick a and b in such a way that minimizes value 3.
3. If we pick a and b optimally, they will be in the diameters of Tree 1 and Tree 2, respectively.
   Exactly which nodes of the diameter should we pick?
4. a is the center of the diameter of tree 1, and b is the center of the diameter of tree 2.
```

</details>

</details>

<details><summary>C</summary>

```c
int** buildAdjList(int** edges, int edgesSize, int* edgesColSize, int** returnColSize) {
    int** pRetVal = NULL;

    int returnSize = edgesSize + 1;

    (*returnColSize) = (int*)malloc(returnSize * sizeof(int));
    if ((*returnColSize) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColSize), 0, (returnSize * sizeof(int)));
    for (int i = 0; i < edgesSize; ++i) {
        (*returnColSize)[edges[i][0]]++;
        (*returnColSize)[edges[i][1]]++;
    }

    pRetVal = (int**)malloc(returnSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColSize));
        (*returnColSize) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < returnSize; ++i) {
        pRetVal[i] = (int*)malloc((*returnColSize)[i] * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColSize));
            (*returnColSize) = NULL;
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnColSize)[i] * sizeof(int)));
    }

    memset((*returnColSize), 0, (returnSize * sizeof(int)));
    int src, dst;
    for (int i = 0; i < edgesSize; ++i) {
        src = edges[i][0];
        dst = edges[i][1];
        pRetVal[src][(*returnColSize)[src]++] = dst;
        pRetVal[dst][(*returnColSize)[dst]++] = src;
    }

    return pRetVal;
};
void findDiameter(int** adjList, int* adjListColSize, int node, int parent, int* first, int* second) {
    (*first) = 0;
    (*second) = 0;

    int childDiameter, depth;
    int maxDepth1 = 0;
    int maxDepth2 = 0;
    int diameter = 0;
    for (int i = 0; i < adjListColSize[node]; ++i) {
        // Skip the parent to avoid cycles
        if (adjList[node][i] == parent) {
            continue;
        }

        // Recursively calculate the diameter and depth of the neighbor's subtree
        findDiameter(adjList, adjListColSize, adjList[node][i], node, first, second);
        childDiameter = (*first);
        depth = (*second);

        // Update the maximum diameter of the subtree
        diameter = fmax(diameter, childDiameter);

        // Increment the depth to include the edge to this neighbor
        depth++;

        // Update the two largest depths from the current node
        if (depth > maxDepth1) {
            maxDepth2 = maxDepth1;
            maxDepth1 = depth;
        } else if (depth > maxDepth2) {
            maxDepth2 = depth;
        }
    }

    // Update the diameter to include the path through the current node
    diameter = fmax(diameter, maxDepth1 + maxDepth2);

    (*first) = diameter;
    (*second) = maxDepth1;
}
int minimumDiameterAfterMerge(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size,
                              int* edges2ColSize) {
    int retVal = 0;

    int* adjListColSize1 = NULL;
    int** adjList1 = buildAdjList(edges1, edges1Size, edges1ColSize, &adjListColSize1);
    int diameter1 = 0;
    findDiameter(adjList1, adjListColSize1, 0, -1, &diameter1, &retVal);

    int* adjListColSize2 = NULL;
    int** adjList2 = buildAdjList(edges2, edges2Size, edges2ColSize, &adjListColSize2);
    int diameter2 = 0;
    findDiameter(adjList2, adjListColSize2, 0, -1, &diameter2, &retVal);

    int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

    retVal = diameter1;
    retVal = fmax(retVal, diameter2);
    retVal = fmax(retVal, combinedDiameter);

    //
    free(adjListColSize1);
    adjListColSize1 = NULL;
    for (int i = 0; i <= edges1Size; ++i) {
        free(adjList1[i]);
        adjList1[i] = NULL;
    }
    free(adjList1);
    adjList1 = NULL;
    free(adjListColSize2);
    adjListColSize2 = NULL;
    for (int i = 0; i <= edges2Size; ++i) {
        free(adjList2[i]);
        adjList2[i] = NULL;
    }
    free(adjList2);
    adjList2 = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<vector<int>> buildAdjList(int size, vector<vector<int>>& edges) {
        vector<vector<int>> retVal(size);

        for (auto& edge : edges) {
            retVal[edge[0]].push_back(edge[1]);
            retVal[edge[1]].push_back(edge[0]);
        }

        return retVal;
    };

    pair<int, int> findDiameter(vector<vector<int>>& adjList, int node, int parent) {
        pair<int, int> retVal = {0, 0};

        int maxDepth1 = 0;
        int maxDepth2 = 0;
        int diameter = 0;
        for (int neighbor : adjList[node]) {
            // Skip the parent to avoid cycles
            if (neighbor == parent) {
                continue;
            }

            // Recursively calculate the diameter and depth of the neighbor's subtree
            auto [childDiameter, depth] = findDiameter(adjList, neighbor, node);

            // Update the maximum diameter of the subtree
            diameter = max(diameter, childDiameter);

            // Increment the depth to include the edge to this neighbor
            depth++;

            // Update the two largest depths from the current node
            if (depth > maxDepth1) {
                maxDepth2 = maxDepth1;
                maxDepth1 = depth;
            } else if (depth > maxDepth2) {
                maxDepth2 = depth;
            }
        }

        // Update the diameter to include the path through the current node
        diameter = max(diameter, maxDepth1 + maxDepth2);

        retVal = {diameter, maxDepth1};

        return retVal;
    }

   public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int retVal = 0;

        int edges1Size = edges1.size() + 1;
        vector<vector<int>> adjList1 = buildAdjList(edges1Size, edges1);
        int diameter1 = findDiameter(adjList1, 0, -1).first;

        int edges2Size = edges2.size() + 1;
        vector<vector<int>> adjList2 = buildAdjList(edges2Size, edges2);
        int diameter2 = findDiameter(adjList2, 0, -1).first;

        int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

        retVal = max({diameter1, diameter2, combinedDiameter});

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def buildAdjList(self, size: int, edges: list[list[int]]) -> list[list[int]]:
        retVal = [[] for _ in range(size)]

        for edge in edges:
            retVal[edge[0]].append(edge[1])
            retVal[edge[1]].append(edge[0])

        return retVal

    def findDiameter(self, adjList: list[list[int]], node: int, parent: int) -> tuple[int, int]:
        retVal = 0, 0

        maxDepth1 = 0
        maxDepth2 = 0
        diameter = 0
        for neighbor in adjList[node]:
            # Skip the parent to avoid cycles
            if neighbor == parent:
                continue

            # Recursively calculate the diameter and depth of the neighbor's subtree
            childDiameter, depth = self.findDiameter(adjList, neighbor, node)

            # Increment depth to include edge to neighbor
            depth += 1

            # Update the maximum diameter of the subtree
            diameter = max(diameter, childDiameter)

            # Update the two largest depths from the current node
            if depth > maxDepth1:
                maxDepth2 = maxDepth1
                maxDepth1 = depth
            elif depth > maxDepth2:
                maxDepth2 = depth

        # Update the diameter to include the path through the current node
        diameter = max(diameter, maxDepth1 + maxDepth2)

        # Return the diameter and the longest depth
        retVal = diameter, maxDepth1

        return retVal

    def minimumDiameterAfterMerge(self, edges1: List[List[int]], edges2: List[List[int]]) -> int:
        retVal = 0

        edges1Size = len(edges1) + 1
        adjList1 = self.buildAdjList(edges1Size, edges1)
        diameter1, _ = self.findDiameter(adjList1, 0, -1)

        edges2Size = len(edges2) + 1
        adjList2 = self.buildAdjList(edges2Size, edges2)
        diameter2, _ = self.findDiameter(adjList2, 0, -1)

        combinedDiameter = ceil(diameter1 / 2) + ceil(diameter2 / 2) + 1

        retVal = max(diameter1, diameter2, combinedDiameter)

        return retVal
```

</details>

## [3243. Shortest Distance After Road Addition Queries I](https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/)  1567

- [Official](https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/editorial/)
- [Official](https://leetcode.cn/problems/shortest-distance-after-road-addition-queries-i/solutions/2984418/xin-zeng-dao-lu-cha-xun-hou-de-zui-duan-9smce/)

<details><summary>Description</summary>

```text
You are given an integer n and a 2D integer array queries.

There are n cities numbered from 0 to n - 1.
Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.

queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi.
After each query, you need to find the length of the shortest path from city 0 to city n - 1.

Return an array answer where for each i in the range [0, queries.length - 1],
answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.

Example 1:
Input: n = 5, queries = [[2,4],[0,2],[0,4]]
Output: [3,2,1]
Explanation:
After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.

Example 2:
Input: n = 4, queries = [[0,3],[0,2]]
Output: [1,1]
Explanation:
After the addition of the road from 0 to 3, the length of the shortest path from 0 to 3 is 1.
After the addition of the road from 0 to 2, the length of the shortest path remains 1.

Constraints:
3 <= n <= 500
1 <= queries.length <= 500
queries[i].length == 2
0 <= queries[i][0] < queries[i][1] < n
1 < queries[i][1] - queries[i][0]
There are no repeated roads among the queries.
```

<details><summary>Hint</summary>

```text
1. Maintain the graph and use an efficient shortest path algorithm after each update.
2. We use BFS/Dijkstra for each query.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct Node {
    int val;
    struct Node *next;
} Node;
typedef struct List {
    Node *node;
} List;
int push(List *pObj, int val) {
    int retVal = EXIT_SUCCESS;

    Node *pNew = (Node *)malloc(sizeof(Node));
    if (pNew == NULL) {
        perror("malloc");
        retVal = EXIT_FAILURE;
        return retVal;
    }
    pNew->next = pObj->node;
    pNew->val = val;

    pObj->node = pNew;

    return retVal;
}
void freeList(List *pObj) {
    Node *pFree;
    Node *pCurrent;
    for (pCurrent = pObj->node; pCurrent != NULL;) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *shortestDistanceAfterQueries(int n, int **queries, int queriesSize, int *queriesColSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    List *adjacency = (List *)malloc(n * sizeof(List));
    if (adjacency == NULL) {
        perror("malloc");
        goto exit;
    }
    memset(adjacency, 0, n * sizeof(List));

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        perror("malloc");
        goto exit_adjacency;
    }
    memset(dp, 0, n * sizeof(int));

    for (i = 1; i < n; ++i) {
        if (push(&adjacency[i], i - 1) == EXIT_FAILURE) {
            goto exit_dp;
        }
        dp[i] = i;
    }

    pRetVal = (int *)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_dp;
    }

    Node *pCurrent;
    for (i = 0; i < queriesSize; ++i) {
        if (push(&adjacency[queries[i][1]], queries[i][0]) == EXIT_FAILURE) {
            i = n;
            goto exit_dp;
        }

        for (j = queries[i][1]; j < n; ++j) {
            for (pCurrent = adjacency[j].node; pCurrent != NULL; pCurrent = pCurrent->next) {
                dp[j] = fmin(dp[j], dp[pCurrent->val] + 1);
            }
        }
        pRetVal[i] = dp[n - 1];
    }
    (*returnSize) = queriesSize;
    i = n;

exit_dp:
    free(dp);
    dp = NULL;

    for (j = 0; j < i; ++j) {
        freeList(&adjacency[j]);
    }

exit_adjacency:
    free(adjacency);
    adjacency = NULL;

exit:
    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMinDistance(vector<vector<int>>& adjList, int n) {
        int retVal = 0;

        vector<int> dp(n);
        dp[n - 1] = 0;
        for (int currentNode = n - 2; currentNode >= 0; currentNode--) {
            int minDistance = n;
            for (auto neighbor : adjList[currentNode]) {
                minDistance = min(minDistance, dp[neighbor] + 1);
            }
            dp[currentNode] = minDistance;
        }
        retVal = dp[0];

        return retVal;
    }
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> retVal;

        vector<vector<int>> adjacency(n, vector<int>(0));
        for (int i = 0; i < n - 1; i++) {
            adjacency[i].push_back(i + 1);
        }

        for (auto& road : queries) {
            int src = road[0];
            int dst = road[1];
            adjacency[src].push_back(dst);

            retVal.push_back(findMinDistance(adjacency, n));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMinDistance(self, adjacency: List[List[int]], n: int) -> int:
        retVal = 0

        dp = [0] * n
        dp[n - 1] = 0
        for currentNode in range(n - 2, -1, -1):
            minDistance = n
            for neighbor in adjacency[currentNode]:
                minDistance = min(minDistance, dp[neighbor] + 1)
            dp[currentNode] = minDistance
        retVal = dp[0]

        return retVal

    def shortestDistanceAfterQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        retVal = []

        adjacency = [[] for _ in range(n)]
        for i in range(n - 1):
            adjacency[i].append(i + 1)

        for src, dst in queries:
            adjacency[src].append(dst)
            retVal.append(self.findMinDistance(adjacency, n))

        return retVal
```

</details>
