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
    def __init__(self) -> None:
        # 2 <= k <= 9, 1 <= n <= 30
        self.answer = [
            [
                1, 3, 5, 7, 9, 33, 99, 313, 585, 717,
                7447, 9009, 15351, 32223, 39993, 53235, 53835, 73737, 585585, 1758571,
                1934391, 1979791, 3129213, 5071705, 5259525, 5841485, 13500531, 719848917, 910373019, 939474939,],
            [
                1, 2, 4, 8, 121, 151, 212, 242, 484, 656,
                757, 29092, 48884, 74647, 75457, 76267, 92929, 93739, 848848, 1521251,
                2985892, 4022204, 4219124, 4251524, 4287824, 5737375, 7875787, 7949497, 27711772, 83155138,
            ],
            [
                1, 2, 3, 5, 55, 373, 393, 666, 787, 939,
                7997, 53235, 55255, 55655, 57675, 506605, 1801081, 2215122, 3826283, 3866683,
                5051505, 5226225, 5259525, 5297925, 5614165, 5679765, 53822835, 623010326, 954656459, 51717171715,
            ],
            [
                1, 2, 3, 4, 6, 88, 252, 282, 626, 676,
                1221, 15751, 18881, 10088001, 10400401, 27711772, 30322303, 47633674, 65977956, 808656808,
                831333138, 831868138, 836131638, 836181638, 2512882152, 2596886952, 2893553982, 6761551676, 12114741121, 12185058121,
            ],
            [
                1, 2, 3, 4, 5, 7, 55, 111, 141, 191,
                343, 434, 777, 868, 1441, 7667, 7777, 22022, 39893, 74647,
                168861, 808808, 909909, 1867681, 3097903, 4232324, 4265624, 4298924, 4516154, 4565654,
            ],
            [
                1, 2, 3, 4, 5, 6, 8, 121, 171, 242,
                292, 16561, 65656, 2137312, 4602064, 6597956, 6958596, 9470749, 61255216, 230474032,
                466828664, 485494584, 638828836, 657494756, 858474858, 25699499652, 40130703104, 45862226854, 61454945416, 64454545446,
            ],
            [
                1, 2, 3, 4, 5, 6, 7, 9, 121, 292,
                333, 373, 414, 585, 3663, 8778, 13131, 13331, 26462, 26662,
                30103, 30303, 207702, 628826, 660066, 1496941, 1935391, 1970791, 4198914, 55366355,
            ],
            [
                1, 2, 3, 4, 5, 6, 7, 8, 191, 282,
                373, 464, 555, 646, 656, 6886, 25752, 27472, 42324, 50605,
                626626, 1540451, 1713171, 1721271, 1828281, 1877781, 1885881, 2401042, 2434342, 2442442,
            ],
        ]

    def isPalindrome(self, k: int, x: int) -> bool:
        retVal = False

        digit = list()
        while x:
            digit.append(x % k)
            x //= k
        retVal = (digit == digit[::-1])

        return retVal

    def kMirror(self, k: int, n: int) -> int:
        retVal = 0

        left = 1
        cnt = 0
        while cnt < n:
            right = left * 10

            # op = 0 indicates enumerating odd-length palindromes
            # op = 1 indicates enumerating even-length palindromes
            for op in [0, 1]:
                for i in range(left, right):
                    if cnt == n:
                        break
                    combined = i

                    x = i
                    if op == 0:
                        x = i // 10
                    while x:
                        combined = combined * 10 + x % 10
                        x //= 10

                    if self.isPalindrome(k, combined) == True:
                        cnt += 1
                        retVal += combined

            left = right

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k, n in zip([2, 3, 7], [5, 7, 17]):
            # /* Example
            #  *  Input: k = 2, n = 5
            #  *  Output: 25
            #  *
            #  *  Input: k = 3, n = 7
            #  *  Output: 499
            #  *
            #  *  Input: k = 7, n = 17
            #  *  Output: 20379000
            #  */
            logging.info("Input: k = %s, n = %s", k, n)

            retVal = pSolution.kMirror(k, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
