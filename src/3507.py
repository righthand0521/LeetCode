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


class Node:
    def __init__(self, value: int, left: int) -> None:
        self.value = value
        self.left = left
        self.prev = None
        self.next = None


class PQItem:
    def __init__(self, first: Node, second: Node, cost: int) -> None:
        self.first = first
        self.second = second
        self.cost = cost

    def __lt__(self, other: "PQItem") -> bool:
        retVal = (self.cost < other.cost)

        if self.cost == other.cost:
            retVal = (self.first.left < other.first.left)

        return retVal


class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        pq = []
        head = Node(nums[0], 0)
        current = head
        decreaseCount = 0
        for i in range(1, numsSize):
            newNode = Node(nums[i], i)
            current.next = newNode
            newNode.prev = current
            heappush(pq, PQItem(current, newNode, current.value + newNode.value))
            if nums[i - 1] > nums[i]:
                decreaseCount += 1
            current = newNode

        merged = [False] * numsSize
        while decreaseCount > 0:
            item = heappop(pq)
            first = item.first
            second = item.second
            cost = item.cost

            if (merged[first.left] == True) or (merged[second.left] == True) or (first.value + second.value != cost):
                continue

            retVal += 1

            if first.value > second.value:
                decreaseCount -= 1

            prevNode = first.prev
            nextNode = second.next
            first.next = nextNode
            if nextNode:
                nextNode.prev = first
            if prevNode:
                if (prevNode.value > first.value) and (prevNode.value <= cost):
                    decreaseCount -= 1
                elif (prevNode.value <= first.value) and (prevNode.value > cost):
                    decreaseCount += 1
                heappush(pq, PQItem(prevNode, first, prevNode.value + cost))
            if nextNode:
                if (second.value > nextNode.value) and (cost <= nextNode.value):
                    decreaseCount -= 1
                elif (second.value <= nextNode.value) and (cost > nextNode.value):
                    decreaseCount += 1
                heappush(pq, PQItem(first, nextNode, cost + nextNode.value))

            first.value = cost
            merged[second.left] = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 2, 3, 1], [1, 2, 2]]:
            # /* Example
            #  *  Input: nums = [5,2,3,1]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,2,2]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minimumPairRemoval(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
