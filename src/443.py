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
    def compress(self, chars: List[str]) -> int:
        retVal = 0

        count = 1
        charsSize = len(chars)
        i = 1
        while i < charsSize:
            if chars[i-1] == chars[i]:
                count += 1
                i += 1
                continue

            chars[retVal] = chars[i-1]
            retVal += 1
            if count != 1:
                for c in str(count):
                    chars[retVal] = c
                    retVal += 1
            count = 1
            i += 1

        chars[retVal] = chars[i - 1]
        retVal += 1
        if count != 1:
            for c in str(count):
                chars[retVal] = c
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for chars in [["a", "a", "b", "b", "c", "c", "c"],
                      ["a"],
                      ["a", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b"]]:
            # /* Example
            #  *  Input: chars = ["a","a","b","b","c","c","c"]
            #  *  Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
            #  *
            #  *  Input: chars = ["a"]
            #  *  Output: Return 1, and the first character of the input array should be: ["a"]
            #  *
            #  *  Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
            #  *  Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
            #  */
            logging.info("Input: chars = %s", chars)

            retVal = pSolution.compress(chars)
            logging.info("Output: %s, %s", retVal, chars[0:retVal])

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
