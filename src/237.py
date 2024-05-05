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
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        node.val = node.next.val
        node.next = node.next.next


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, node in zip([[4, 5, 1, 9], [4, 5, 1, 9]], [5, 1]):
            # /* Example
            #  *  Input: head = [4,5,1,9], node = 5
            #  *  Output: [4,1,9]
            #  *
            #  *  Input: head = [4,5,1,9], node = 1
            #  *  Output: [4,5,9]
            #  */
            logging.info("Input: head = %s, node = %s", head, node)

            pHead = ListNode.buildList(head)
            pNode = pHead
            while pNode != None:
                if pNode.val == node:
                    break
                pNode = pNode.next
            pSolution.deleteNode(pNode)
            logging.info("Output: %s", pHead)

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
