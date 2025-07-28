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
    def maximumLength(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        hashTable = {}
        for start in range(sSize):
            character = s[start]
            substringLength = 0
            for end in range(start, sSize):
                # If the string is empty, or the current character is equal to the previously added character,
                # then add it to the map. Otherwise, break the iteration.
                if character != s[end]:
                    break
                substringLength += 1
                hashTable[(character, substringLength)] = hashTable.get((character, substringLength), 0) + 1

        for (character, substringLength), count in hashTable.items():
            if (count >= 3) and (substringLength > retVal):
                retVal = substringLength
        if retVal == 0:
            retVal = - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aaaa", "abcdef", "abcaba"]:
            # /* Example
            #  *  Input: s = "aaaa"
            #  *  Output: 2
            #  *
            #  *  Input: s = "abcdef"
            #  *  Output: -1
            #  *
            #  *  Input: s = "abcaba"
            #  *  Output: 1
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.maximumLength(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
