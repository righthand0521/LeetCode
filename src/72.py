import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


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
    def minDistance(self, word1: str, word2: str) -> int:
        retVal = 0

        word1Size = len(word1)
        word2Size = len(word2)
        dp = [[0 for _ in range(word2Size+1)] for _ in range(word1Size+1)]

        # /* Example: Input: word1 = "horse", word2 = "ros"
        #  *      r o s
        #  *    0 1 2 3
        #  *  h 1 1 2 3
        #  *  o 2 2 1 2
        #  *  r 3 2 2 2
        #  *  s 4 3 3 2
        #  *  e 5 4 4 3
        #  */
        for idx1 in range(word1Size+1):
            dp[idx1][0] = idx1
        for idx2 in range(word2Size+1):
            dp[0][idx2] = idx2
        for idx1 in range(1, word1Size+1):
            for idx2 in range(1, word2Size+1):
                insert = dp[idx1][idx2 - 1]
                delete = dp[idx1 - 1][idx2]
                replace = dp[idx1 - 1][idx2 - 1]
                if word1[idx1 - 1] == word2[idx2 - 1]:
                    dp[idx1][idx2] = replace
                else:
                    dp[idx1][idx2] = 1 + min(insert, delete, replace)
        retVal = dp[word1Size][word2Size]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word1, word2 in zip(["horse", "intention"], ["ros", "execution"]):
            # /* Example
            #  *  Input: word1 = "horse", word2 = "ros"
            #  *  Output: 3
            #  *
            #  *  Input: word1 = "intention", word2 = "execution"
            #  *  Output: 5
            #  */
            logging.info("Input: word1 = \"%s\", word2 = \"%s\"", word1, word2)

            retVal = pSolution.minDistance(word1, word2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
