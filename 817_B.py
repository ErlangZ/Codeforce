def C(N, m):
    if m == 1: return N
    if m == 2: return N * (N-1) / 2
    else: return N * (N-1) / 2 * (N-2) / 3

a = int(raw_input())
num = [int(n) for n in raw_input().split()]
num.sort()

nums_greater_than_min = [n for n in num if n > num[0]]
nums_greater_than_second_min = [n for n in nums_greater_than_min
                                if n > nums_greater_than_min[0]]
nums_greater_than_third_min = [n for n in nums_greater_than_second_min
                               if n > nums_greater_than_second_min[0]]
if len(num) - len(nums_greater_than_min) >= 3:
    print C(len(num) - len(nums_greater_than_min), 3)
if len(num) - len(nums_greater_than_min) == 2:
    print C(len(num) - 2 - len(nums_greater_than_second_min), 1)
if len(num) - len(nums_greater_than_min) == 1:
    if len(nums_greater_than_min) - len(nums_greater_than_second_min) >= 2:
        print C(len(nums_greater_than_min) - len(nums_greater_than_second_min), 2)
    else:
        print len(nums_greater_than_second_min) - len(nums_greater_than_third_min)
