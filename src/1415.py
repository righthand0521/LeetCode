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
    def getHappyString(self, n: int, k: int) -> str:
        retVal = ""

        # Calculate the total number of happy strings of length n
        total = 3 * (1 << (n - 1))

        # If k is greater than the total number of happy strings, return an empty string
        if k > total:
            return retVal

        # Initialize result with 'a' characters
        result = ["a"] * n
        # Define mappings for the next smallest and greatest valid characters
        nextSmallest = {"a": "b", "b": "a", "c": "a"}
        nextGreatest = {"a": "c", "b": "c", "c": "b"}
        # Calculate the starting indices for strings beginning with 'a', 'b', and 'c'
        startA = 1
        startB = startA + (1 << (n - 1))
        startC = startB + (1 << (n - 1))
        # Determine the first character based on the value of k
        if k < startB:
            result[0] = "a"
            k -= startA
        elif k < startC:
            result[0] = "b"
            k -= startB
        else:
            result[0] = "c"
            k -= startC

        # Iterate through the remaining positions in the result string
        for charIndex in range(1, n):
            # Calculate the midpoint of the group for the current character position
            midpoint = 1 << (n - charIndex - 1)
            # Determine the next character based on the value of k
            if k < midpoint:
                result[charIndex] = nextSmallest[result[charIndex - 1]]
            else:
                result[charIndex] = nextGreatest[result[charIndex - 1]]
                k -= midpoint
        retVal = "".join(result)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([1, 1, 3], [3, 4, 9]):
            # /* Example
            #  *  Input: n = 1, k = 3
            #  *  Output: "c"
            #  *
            #  *  Input: n = 1, k = 4
            #  *  Output: ""
            #  *
            #  *  Input: n = 3, k = 9
            #  *  Output: "cab"
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.getHappyString(n, k)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
