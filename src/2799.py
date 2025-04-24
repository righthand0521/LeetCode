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
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        distinct = set(nums)
        distinctSize = len(distinct)

        hashTable = {}
        numsSize = len(nums)
        right = 0
        for left in range(numsSize):
            if left > 0:
                remove = nums[left - 1]
                hashTable[remove] -= 1
                if hashTable[remove] == 0:
                    hashTable.pop(remove)

            hashTableSize = len(hashTable)
            while right < numsSize:
                if hashTableSize >= distinctSize:
                    break
                add = nums[right]
                hashTable[add] = hashTable.get(add, 0) + 1
                hashTableSize = len(hashTable)
                right += 1

            if hashTableSize == distinctSize:
                retVal += (numsSize - right + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 3, 1, 2, 2], [5, 5, 5, 5]]:
            # /* Example
            #  *  Input: nums = [1,3,1,2,2]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [5,5,5,5]
            #  *  Output: 10
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.countCompleteSubarrays(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
