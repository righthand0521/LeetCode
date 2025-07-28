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
        self.letters = 26   # words[i] consists of lowercase English letters.

    def makeEqual(self, words: List[str]) -> bool:
        retVal = True

        wordsSize = len(words)

        hashTable = [0] * self.letters
        for word in words:
            for c in word:
                idx = ord(c)-ord('a')
                hashTable[idx] += 1

        for value in hashTable:
            if value % wordsSize != 0:
                retVal = False
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["abc", "aabc", "bc"], ["ab", "a"]]:
            # /* Example
            #  *  Input: words = ["abc","aabc","bc"]
            #  *  Output: true
            #  *
            #  *  Input: words = ["ab","a"]
            #  *  Output: false
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.makeEqual(words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
