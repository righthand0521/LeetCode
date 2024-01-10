import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO  # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S",
    )


class Solution:
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:
        retVal = 0

        # /* Brainteaser
        #  *  最後一隻螞蟻從木板上掉下來的時刻，所以並不需要區分每隻螞蟻。
        #  *  由於改變移動方向不花費額外時間，而且改變移動方向後的移動速度不變。
        #  *  因此，兩隻相遇的螞蟻同時改變移動方向之後的情形等價於兩隻螞蟻都不改變移動方向，繼續以原來的方向和速度移動。
        #  *  這樣問題就簡化成根據每隻螞蟻的初始位置和移動方向得到最後一隻螞蟻到達木板邊界的時刻。
        #  *  假設一隻螞蟻在位置 p。
        #  *  如果這隻螞蟻向左移動，則它到達木板邊界所需的時間是 p。
        #  *  如果這隻螞蟻向右移動，則它到達木板邊界所需的時間是 n−p。
        #  */
        for p in left:
            retVal = max(retVal, p)
        for p in right:
            retVal = max(retVal, n - p)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, left, right in zip(
            [4, 7, 7],
            [[4, 3], [], [0, 1, 2, 3, 4, 5, 6, 7]],
            [[0, 1], [0, 1, 2, 3, 4, 5, 6, 7], []],
        ):
            # /* Example
            #  *  Input: n = 4, left = [4,3], right = [0,1]
            #  *  Output: 4
            #  *
            #  *  Input: n = 7, left = [], right = [0,1,2,3,4,5,6,7]
            #  *  Output: 7
            #  *
            #  *  Input: n = 7, left = [0,1,2,3,4,5,6,7], right = []
            #  *  Output: 7
            #  */
            logging.info("Input: n = %s, nums1 = %s, nums2 = %s", n, left, right)

            retVal = pSolution.getLastMoment(n, left, right)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
