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
    def check(self, s1: str, s2: str) -> bool:
        retVal = False

        s1Size = len(s1)
        s2Size = len(s2)
        if s1Size != s2Size:
            return retVal

        diff = 0
        for c1, c2 in zip(s1, s2):
            if c1 == c2:
                continue
            diff += 1
            if diff > 1:
                return retVal
        if diff == 1:
            retVal = True

        return retVal

    def getWordsInLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        retVal = []

        groupsSize = len(groups)

        dp = [1] * groupsSize
        prev = [-1] * groupsSize
        maxIndex = 0
        for i in range(1, groupsSize):
            for j in range(i):
                if ((self.check(words[i], words[j]) == True) and (dp[j] + 1 > dp[i]) and (groups[i] != groups[j])):
                    dp[i] = dp[j] + 1
                    prev[i] = j
            if dp[i] > dp[maxIndex]:
                maxIndex = i

        i = maxIndex
        while i >= 0:
            retVal.append(words[i])
            i = prev[i]
        retVal.reverse()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, groups in zip([["bab", "dab", "cab"], ["a", "b", "c", "d"]], [[1, 2, 2], [1, 2, 3, 4]]):
            # /* Example
            #  *  Input: words = ["bab","dab","cab"], groups = [1,2,2]
            #  *  Output: ["bab","cab"]
            #  *
            #  *  Input: words = ["a","b","c","d"], groups = [1,2,3,4]
            #  *  Output: ["a","b","c","d"]
            #  */
            logging.info("Input: words = %s, groups = %s", words, groups)

            retVal = pSolution.getWordsInLongestSubsequence(words, groups)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
