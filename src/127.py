import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Solution:
    def __init__(self) -> None:
        self.wordId = None
        self.edge = None
        self.nodeNum = 0

    def addWord(self, word: str) -> None:
        if word not in self.wordId:
            self.wordId[word] = self.nodeNum
            self.nodeNum += 1

    def addEdge(self, word: str) -> None:
        self.addWord(word)

        id1 = self.wordId[word]
        chars = list(word)
        charsSize = len(chars)
        for i in range(charsSize):
            tmp = chars[i]

            chars[i] = "*"
            newWord = "".join(chars)
            self.addWord(newWord)

            id2 = self.wordId[newWord]
            self.edge[id1].append(id2)
            self.edge[id2].append(id1)

            chars[i] = tmp

    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        retVal = 0

        self.wordId = dict()
        self.edge = defaultdict(list)
        self.nodeNum = 0

        for word in wordList:
            self.addEdge(word)

        self.addEdge(beginWord)
        if endWord not in self.wordId:
            return retVal

        beginId = self.wordId[beginWord]
        endId = self.wordId[endWord]

        distance = [float("inf")] * self.nodeNum
        distance[beginId] = 0

        bfsQueue = deque([beginId])
        while bfsQueue:
            x = bfsQueue.popleft()
            if x == endId:
                retVal = distance[endId] // 2 + 1
                break

            for it in self.edge[x]:
                if distance[it] == float("inf"):
                    distance[it] = distance[x] + 1
                    bfsQueue.append(it)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for beginWord, endWord, wordList in zip(
            ["hit", "hit"],
            ["cog", "cog"],
            [["hot", "dot", "dog", "lot", "log", "cog"], ["hot", "dot", "dog", "lot", "log"]]):
            # /* Example
            #  *  Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
            #  *  Output: 5
            #  *
            #  *  Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
            #  *  Output: 0
            #  */
            logging.info("Input: beginWord = \"%s\", endWord = \"%s\", wordList = %s", beginWord, endWord, wordList)

            answer = pSolution.ladderLength(beginWord, endWord, wordList)
            logging.info("Output: %s", answer)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
