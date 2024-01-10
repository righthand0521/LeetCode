import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from list import ListNode, ListNodeCommon


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pRetVal = head

        # // The number of nodes is 1
        if head.next == None:
            pRetVal = None
            return pRetVal

        # // Middle of the Linked List: https://leetcode.com/problems/middle-of-the-linked-list/
        pOne = head
        pTwo = head
        while (pTwo != None) and (pTwo.next != None):
            pPrevious = pOne
            pOne = pOne.next
            pTwo = pTwo.next
            if pTwo != None:
                pTwo = pTwo.next

        # // The number of nodes is 2
        if pOne.next == None:
            pRetVal.next = None
            return pRetVal

        # // Delete Node in a Linked List: https://leetcode.com/problems/delete-node-in-a-linked-list/
        pPrevious.next = pOne.next
        pOne = None

        return pRetVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[1, 3, 4, 7, 1, 2, 6], [1, 2, 3, 4], [2, 1]]:
            # /* Example
            #  *  Input: head = [1,3,4,7,1,2,6]
            #  *  Output: [1,3,4,1,2,6]
            #  *
            #  *  Input: head = [1,2,3,4]
            #  *  Output: [1,2,4]
            #  *
            #  *  Input: head = [2,1]
            #  *  Output: [2]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.deleteMiddle(pHead)
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
