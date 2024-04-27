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
    # Find the minimum steps between two indexes of ring
    def count_steps(self, ring: str, curr: int, next: int) -> int:
        retVal = 0

        ringSize = len(ring)
        steps_between = abs(curr - next)
        steps_around = ringSize - steps_between
        retVal = min(steps_between, steps_around)

        return retVal

    def findRotateSteps(self, ring: str, key: str) -> int:
        retVal = 0

        ringSize = len(ring)
        keySize = len(key)

        # For each occurrence of the character at keyIndex of key in ring
        # Stores minimum steps to the character from ring_index of ring
        curr = [float('inf') for _ in range(ringSize)]
        prev = [0 for _ in range(ringSize)]
        for key_index in range(keySize - 1, -1, -1):
            curr = [float('inf') for _ in range(ringSize)]
            for ring_index in range(ringSize):
                for character in range(ringSize):
                    if ring[character] == key[key_index]:
                        curr[ring_index] = min(
                            curr[ring_index], 1 + self.count_steps(ring, ring_index, character) + prev[character])
            prev = curr.copy()

        retVal = prev[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for ring, key in zip(["godding", "godding"], ["gd", "godding"]):
            # /* Example
            #  *  Input: ring = "godding", key = "gd"
            #  *  Output: 4
            #  *
            #  *  Input: ring = "godding", key = "godding"
            #  *  Output: 13
            #  */
            logging.info("Input: ring = \"%s\", key = \"%s\"", ring, key)

            retVal = pSolution.findRotateSteps(ring, key)
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
