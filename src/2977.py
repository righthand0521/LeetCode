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
    # https://leetcode.cn/problems/minimum-cost-to-convert-string-ii/solutions/2577877/zi-dian-shu-floyddp-by-endlesscheng-oi2r/
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        retVal = -1

        len_to_strs = defaultdict(set)
        dis = defaultdict(lambda: defaultdict(lambda: float('inf')))
        for x, y, c in zip(original, changed, cost):
            len_to_strs[len(x)].add(x)
            len_to_strs[len(y)].add(y)
            dis[x][y] = min(dis[x][y], c)
            dis[x][x] = 0
            dis[y][y] = 0

        for strs in len_to_strs.values():
            for k in strs:
                for i in strs:
                    if dis[i][k] == float('inf'):
                        continue
                    for j in strs:
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j])

        sourceSize = len(source)
        dp = [0] + [float('inf')] * sourceSize
        for i in range(1, sourceSize + 1):
            if source[i - 1] == target[i - 1]:
                dp[i] = dp[i - 1]
            for size, strs in len_to_strs.items():
                if i < size:
                    continue
                s = source[i - size: i]
                t = target[i - size: i]
                if (s in strs) and (t in strs):
                    dp[i] = min(dp[i], dis[s][t] + dp[i - size])

        if dp[sourceSize] < float('inf'):
            retVal = dp[sourceSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for source, target, original, changed, cost in [
            ["abcd", "acbe", ["a", "b", "c", "c", "e", "d"], ["b", "c", "b", "e", "b", "e"], [2, 5, 5, 1, 2, 20]],
            ["abcdefgh", "acdeeghh", ["bcd", "fgh", "thh"], ["cde", "thh", "ghh"], [1, 3, 5]],
            ["abcdefgh", "addddddd", ["bcd", "defgh"], ["ddd", "ddddd"], [100, 1578]]
        ]:
            # /* Example
            #  *  Input:
            #  *  source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"],
            #  *  changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
            #  *  Output: 28
            #  *
            #  *  Input:
            #  *  source = "abcdefgh", target = "acdeeghh", original = ["bcd","fgh","thh"],
            #  *  changed = ["cde","thh","ghh"], cost = [1,3,5]
            #  *  Output: 9
            #  *
            #  *  Input:
            #  *  source = "abcdefgh", target = "addddddd", original = ["bcd","defgh"],
            #  *  changed = ["ddd","ddddd"], cost = [100,1578]
            #  *  Output: -1
            #  */
            logging.info("Input: source = \"%s\", target = \"%s\", original = %s, changed = %s, cost = %s",
                         source, target, original, changed, cost)

            retVal = pSolution.minimumCost(source, target, original, changed, cost)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
