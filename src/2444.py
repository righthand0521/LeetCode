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
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        retVal = 0

        # /* Ref
        #  *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
        #  *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
        #  *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
        #  */
        numsSize = len(nums)
        badIdx = -1
        minIdx = -1
        maxIdx = -1
        for i in range(numsSize):
            if (nums[i] < minK) or (nums[i] > maxK):
                badIdx = i

            if (nums[i] == minK):
                minIdx = i

            if (nums[i] == maxK):
                maxIdx = i

            # /* avoid different type between a and b in max function
            #  *  Because std::max is a function template whose signature is, for example,
            #  *  template< class T >
            #  *  const T& max( const T& a, const T& b );
            #  */

            n1 = 0
            n2 = min(minIdx, maxIdx) - badIdx
            retVal += max(n1, n2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, minK, maxK in zip([[1, 3, 5, 2, 7, 5], [1, 1, 1, 1]], [1, 1], [5, 1]):
            # /* Example
            #  *  Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,1,1,1], minK = 1, maxK = 1
            #  *  Output: 10
            #  */
            logging.info("Input: nums = %s, minK = %s, maxK = %s", nums, minK, maxK)

            retVal = pSolution.countSubarrays(nums, minK, maxK)
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
