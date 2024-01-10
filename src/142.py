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
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = None

        if (head == None):
            return retVal

        pOne = head
        pTwo = head
        while ((pOne.next != None) and (pTwo.next != None) and (pTwo.next.next != None)):
            pOne = pOne.next
            pTwo = pTwo.next.next
            if pOne == pTwo:
                retVal = head
                break
        if retVal != head:
            return retVal

        while retVal != pOne:
            retVal = retVal.next
            pOne = pOne.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, pos in zip([[3, 2, 0, -4], [1, 2], [1]], [-1, 0, -1]):
            # /* Example
            #  *  Input: head = [3,2,0,-4], pos = 1
            #  *  Output: tail connects to node index 1
            #  *
            #  *  Input: head = [1,2], pos = 0
            #  *  Output: tail connects to node index 0
            #  *
            #  *  Input: head = [1], pos = -1
            #  *  Output: no cycle
            #  */
            logging.info("Input: head = %s, pos = %s", head, pos)
            pHead = ListNode.buildList(head)
            ListNodeCommon().addListNodeCycle(pHead, pos)

            retVal = pSolution.detectCycle(pHead)
            if (retVal == None):
                print("Output: no cycle\n")
            else:
                print("Output: tail connects to node index", pos)

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
