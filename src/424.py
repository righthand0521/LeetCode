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
    def characterReplacement(self, s: str, k: int) -> int:
        retVal = 0

        # s consists of only uppercase English letters.
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        sSize = len(s)
        left = 0
        right = 0
        while right < sSize:
            idx = ord(s[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(s[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["ABAB", "AABABBA", "ABAA"], [2, 1, 0]):
            # /* Example
            #  *  Input: s = "ABAB", k = 2
            #  *  Output: 4
            #  *
            #  *  Input: s = "AABABBA", k = 1
            #  *  Output: 4
            #  *
            #  *  Input: s = "ABAA", k = 0
            #  *  Output: 2
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.characterReplacement(s, k)
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
