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
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        if head is None:
            return retVal

        retVal = ListNode(0, head)

        current = retVal
        while current.next and current.next.next:
            if current.next.val == current.next.next.val:
                duplicateVal = current.next.val
                while current.next and current.next.val == duplicateVal:
                    current.next = current.next.next
            else:
                current = current.next

        retVal = retVal.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[1, 2, 3, 3, 4, 4, 5], [1, 1, 1, 2, 3]]:
            # /* Example
            #  *  Input: head = [1,2,3,3,4,4,5]
            #  *  Output: [1,2,5]
            #  *
            #  *  Input: head = [1,1,1,2,3]
            #  *  Output: [2,3]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.deleteDuplicates(pHead)
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
