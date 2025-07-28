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


# https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/917779/java-c-python-space-o-n/
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numWays(self, words: List[str], target: str) -> int:
        retVal = 0

        targetSize = len(target)
        dp = [1] + [0] * targetSize
        for i in range(len(words[0])):
            count = Counter(word[i] for word in words)
            for j in range(targetSize, 0, -1):
                dp[j] += dp[j-1] * count[target[j-1]] % self.MODULO
        retVal = dp[targetSize] % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, target in zip([["acca", "bbbb", "caca"], ["abba", "baab"]], ["aba", "bab"]):
            # /* Example
            #  *  Input: words = ["acca","bbbb","caca"], target = "aba"
            #  *  Output: 6
            #  *
            #  *  Input: words = ["abba","baab"], target = "bab"
            #  *  Output: 4
            #  */
            logging.info("Input: words = %s, target = \"%s\"", words, target)

            retVal = pSolution.numWays(words, target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
