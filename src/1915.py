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
    def wonderfulSubstrings(self, word: str) -> int:
        retVal = 0

        # Create the frequency map: Key = bitmask, Value = frequency of bitmask key
        frequency = {}
        frequency[0] = 1

        mask = 0
        for c in word:
            # a string word that consists of the first ten lowercase English letters
            bit = ord(c) - ord('a')

            # Flip the parity of the c-th bit in the running prefix mask
            mask ^= (1 << bit)
            if mask in frequency:   # Count smaller prefixes that create substrings with no odd occurring letters
                retVal += frequency[mask]
                frequency[mask] += 1
            else:
                frequency[mask] = 1

            # Loop through every possible letter that can appear an odd number of times in a substring
            for odd in range(0, 10):
                bitmask = mask ^ (1 << odd)
                if bitmask in frequency:
                    retVal += frequency[bitmask]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word in ["aba", "aabb", "he"]:
            # /* Example
            #  *  Input: word = "aba"
            #  *  Output: 4
            #  *
            #  *  Input: word = "aabb"
            #  *  Output: 9
            #  *
            #  *  Input: word = "he"
            #  *  Output: 2
            #  */
            logging.info("Input: word = \"%s\"", word)

            retVal = pSolution.wonderfulSubstrings(word)
            logging.info("Output: %d", retVal)

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
