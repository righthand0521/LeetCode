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
    def minHeightShelves(self, books: List[List[int]], shelfWidth: int) -> int:
        retVal = 0

        booksSize = len(books)

        # dp[i] will store the minimum height of the bookcase containing all books up to and excluding i
        dp = [0] * (booksSize + 1)
        dp[0] = 0
        dp[1] = books[0][1]

        for i in range(2, booksSize + 1):
            # new shelf built to hold current book
            remainingShelfWidth = shelfWidth - books[i - 1][0]
            maxHeight = books[i - 1][1]
            dp[i] = books[i - 1][1] + dp[i - 1]

            # calculate the height when previous books are added to new shelf
            j = i - 1
            while (j > 0) and (remainingShelfWidth - books[j - 1][0] >= 0):
                maxHeight = max(maxHeight, books[j - 1][1])
                remainingShelfWidth -= books[j - 1][0]
                dp[i] = min(dp[i], maxHeight + dp[j - 1])
                j -= 1

        retVal = dp[booksSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for books, shelfWidth in zip(
                [[[1, 1], [2, 3], [2, 3], [1, 1], [1, 1], [1, 1], [1, 2]], [[1, 3], [2, 4], [3, 2]]], [4, 6]):
            # /* Example
            #  *  Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelfWidth = 4
            #  *  Output: 6
            #  *
            #  *  Input: books = [[1,3],[2,4],[3,2]], shelfWidth = 6
            #  *  Output: 4
            #  */
            logging.info("Input: edges = %s, shelfWidth = %s", books, shelfWidth)

            retVal = pSolution.minHeightShelves(books, shelfWidth)
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
