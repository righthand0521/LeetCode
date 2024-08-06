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
    def __init__(self) -> None:
        self.letters = 26   # word consists of lowercase English letters.

    def minimumPushes(self, word: str) -> int:
        retVal = 0

        frequency = [0] * self.letters
        for c in word:
            frequency[ord(c) - ord("a")] += 1
        frequency.sort(reverse=True)

        for i in range(self.letters):
            if frequency[i] == 0:
                break
            retVal += (i // 8 + 1) * frequency[i]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word in ["abcde", "xyzxyzxyzxyz", "aabbccddeeffgghhiiiiii"]:
            # /* Example
            #  *  Input: word = "abcde"
            #  *  Output: 5
            #  *
            #  *  Input: word = "xyzxyzxyzxyz"
            #  *  Output: 12
            #  *
            #  *  Input: word = "aabbccddeeffgghhiiiiii"
            #  *  Output: 24
            #  */
            logging.info("Input: word = \"%s\"", word)

            retVal = pSolution.minimumPushes(word)
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
