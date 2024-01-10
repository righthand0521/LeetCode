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
        # a queue to store each gene string
        queue = deque([(start, 0)])

        # a hash table to record visited gene string
        seen = {start}

        # Breadth-First Search
        while queue:
            node, steps = queue.popleft()
            if node == end:
                return steps

            for c in "ACGT":
                for i in range(len(node)):
                    neighbor = node[:i] + c + node[i+1:]
                    if neighbor not in seen and neighbor in bank:
                        queue.append((neighbor, steps+1))
                        seen.add(neighbor)

        return -1


if __name__ == "__main__":
    logging_setting()

    logging.info("sys.version: %s", sys.version)
    print("")
    try:
        testCase = [Counter(start="AACCGGTT", end="AACCGGTA", bank=["AACCGGTA"]),
                    Counter(start="AACCGGTT", end="AAACGGTA", bank=[
                            "AACCGGTA", "AACCGCTA", "AAACGGTA"]),
                    Counter(start="AAAAACCC", end="AACCCCCC", bank=["AAAACCCC", "AAACCCCC", "AACCCCCC"])]

        pSolution = Solution()
        for i in range(0, len(testCase)):
            print('Input: start = "{}", end = "{}", bank = {}'
                  .format(testCase[i]['start'], testCase[i]['end'], testCase[i]['bank']))

            retVal = pSolution.minMutation(
                testCase[i]['start'], testCase[i]['end'], testCase[i]['bank'])
            print('Output: {}'.format(retVal))

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
