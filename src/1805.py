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
    def numDifferentIntegers(self, word: str) -> int:
        retVal = 0

        hashTable = set()

        wordSize = len(word)
        left = 0
        while True:
            while (left < wordSize) and (word[left].isdigit() == False):
                left += 1
            if left == wordSize:
                break

            right = left
            while (right < wordSize) and (word[right].isdigit() == True):
                right += 1

            while (right - left > 1) and (word[left] == '0'):
                left += 1
            hashTable.add(word[left:right])

            left = right

        retVal = len(hashTable)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word in ["a123bc34d8ef34", "leet1234code234", "a1b01c001"]:
            # /* Example
            #  *  Input: word = "a123bc34d8ef34"
            #  *  Output: 3
            #  *
            #  *  Input: word = "leet1234code234"
            #  *  Output: 2
            #  *
            #  *  Input: word = "a1b01c001"
            #  *  Output: 1
            #  */
            logging.info("Input: word = \"%s\"", word)

            retVal = pSolution.numDifferentIntegers(word)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
