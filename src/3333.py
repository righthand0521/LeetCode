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
        self.MODULO = 10 ** 9 + 7

    def possibleStringCount(self, word: str, k: int) -> int:
        retVal = 1

        wordSize = len(word)
        count = 1
        frequency = list()
        for i in range(1, wordSize):
            if word[i] == word[i - 1]:
                count += 1
            else:
                frequency.append(count)
                count = 1
        frequency.append(count)
        frequencySize = len(frequency)

        for value in frequency:
            retVal = retVal * value % self.MODULO

        if frequencySize >= k:
            return retVal

        g = [1] * k
        for i in range(frequencySize):
            fNext = [0] * k
            for j in range(1, k):
                fNext[j] = g[j - 1]
                if j - frequency[i] - 1 >= 0:
                    fNext[j] = (fNext[j] - g[j - frequency[i] - 1]) % self.MODULO

            gNext = [fNext[0]] + [0] * (k - 1)
            for j in range(1, k):
                gNext[j] = (gNext[j - 1] + fNext[j]) % self.MODULO

            g = gNext

        retVal = (retVal - g[k - 1]) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word, k in [["aabbccdd", 7], ["aabbccdd", 8], ["aaabbb", 3]]:
            # /* Example
            #  *  Input: word = "aabbccdd", k = 7
            #  *  Output: 5
            #  *
            #  *  Input: word = "aabbccdd", k = 8
            #  *  Output: 1
            #  *
            #  *  Input: word = "aaabbb", k = 3
            #  *  Output: 8
            #  */
            logging.info("Input: word = \"%s\", k = %s", word, k)

            retVal = pSolution.possibleStringCount(word, k)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
