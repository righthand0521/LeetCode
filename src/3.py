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
    def lengthOfLongestSubstring(self, s: str) -> int:
        retVal = 0

        hashTable = defaultdict(dict)
        sSize = len(s)
        head = 0
        tail = 0
        while head < sSize and tail < sSize:
            if hashTable[s[head]] and hashTable[s[tail]]:
                hashTable.pop(s[head])
                head += 1
            else:
                hashTable[s[tail]] = 1
                tail += 1
            retVal = max(retVal, tail - head)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abcabcbb", "bbbbb", "pwwkew"]:
            # /* Example
            #  *  Input: s = "abcabcbb"
            #  *  Output: 3
            #  *
            #  *  Input: s = "bbbbb"
            #  *  Output: 1
            #  *
            #  *  Input: s = "pwwkew"
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.lengthOfLongestSubstring(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
