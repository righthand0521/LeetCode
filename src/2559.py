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
    def vowelStrings(self, words: List[str], queries: List[List[int]]) -> List[int]:
        retVal = None

        queriesSize = len(queries)
        retVal = [0] * queriesSize

        wordsSize = len(words)
        prefixSum = [0] * wordsSize

        vowels = {"a", "e", "i", "o", "u"}
        vowelCount = 0
        for i in range(wordsSize):
            word = words[i]
            if (word[0] in vowels) and (word[-1] in vowels):
                vowelCount += 1
            prefixSum[i] = vowelCount

        for i in range(queriesSize):
            query = queries[i]
            retVal[i] = prefixSum[query[1]]
            if query[0] != 0:
                retVal[i] -= prefixSum[query[0] - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, queries in zip([["aba", "bcb", "ece", "aa", "e"], ["a", "e", "i"]],
                                  [[[0, 2], [1, 4], [1, 1]], [[0, 2], [0, 1], [2, 2]]]):
            # /* Example
            #  *  Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
            #  *  Output: [2,3,0]
            #  *
            #  *  Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
            #  *  Output: [3,2,1]
            #  */
            logging.info("Input: words = %s, queries = %s", words, queries)

            retVal = pSolution.vowelStrings(words, queries)
            logging.info("Output: %s", retVal)

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
