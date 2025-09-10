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
    def minimumTeachings(self, n: int, languages: List[List[int]], friendships: List[List[int]]) -> int:
        retVal = 0

        cncon = set()
        for friendship in friendships:
            mp = {}
            for lan in languages[friendship[0] - 1]:
                mp[lan] = 1

            conm = False
            for lan in languages[friendship[1] - 1]:
                if lan in mp:
                    conm = True
                    break
            if conm == False:
                cncon.add(friendship[0] - 1)
                cncon.add(friendship[1] - 1)

        maxCnt = 0
        cnt = [0] * (n + 1)
        for friendship in cncon:
            for lan in languages[friendship]:
                cnt[lan] += 1
                maxCnt = max(maxCnt, cnt[lan])

        retVal = len(cncon) - maxCnt

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, languages, friendships in [
            [2, [[1], [2], [1, 2]], [[1, 2], [1, 3], [2, 3]]],
            [3, [[2], [1, 3], [1, 2], [3]], [[1, 4], [1, 2], [3, 4], [2, 3]]]
        ]:
            # /* Example
            #  *  Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
            #  *  Output: 1
            #  *
            #  *  Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
            #  *  Output: 2
            #  */
            logging.info("Input: n = %ds, languages = %s, friendships = %s", n, languages, friendships)

            retVal = pSolution.minimumTeachings(n, languages, friendships)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
