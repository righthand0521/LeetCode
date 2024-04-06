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
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        retVal = -1

        # Breadth-First Search
        queue = deque([(start, 0)])  # a queue to store each gene string
        seen = {start}  # a hash table to record visited gene string
        while queue:
            node, steps = queue.popleft()
            if node == end:
                retVal = steps
                return retVal

            for c in "ACGT":
                for i in range(len(node)):
                    neighbor = node[:i] + c + node[i+1:]
                    if neighbor not in seen and neighbor in bank:
                        queue.append((neighbor, steps+1))
                        seen.add(neighbor)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for start, end, bank in zip(
            ["AACCGGTT", "AACCGGTT", "AAAAACCC"],
            ["AACCGGTA", "AAACGGTA", "AACCCCCC"],
            [["AACCGGTA"], ["AACCGGTA", "AACCGCTA", "AAACGGTA"], ["AAAACCCC", "AAACCCCC", "AACCCCCC"]]):
            # /* Example
            #  *  Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
            #  *  Output: 1
            #  *
            #  *  Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
            #  *  Output: 2
            #  *
            #  *  Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
            #  *  Output: 3
            #  */
            logging.info("Input: start = \"%s\", end = \"%s\", bank = %s", start, end, bank)

            retVal = pSolution.minMutation(start, end, bank)
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
