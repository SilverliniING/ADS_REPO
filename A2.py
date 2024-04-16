from collections import deque

def reverse_first_k(queue, k):
    if k <= 0 or k > len(queue):
        return "Invalid value of k"
    
    stack = []
    for _ in range(k):
        stack.append(queue.popleft())
    
    while stack:
        queue.appendleft(stack.pop())
    
    return queue

def rearrange_queue(queue):
    if len(queue) % 2 != 0:
        return "Queue length must be even"
    
    stack = []
    half_size = len(queue) // 2
    
    for _ in range(half_size):
        stack.append(queue.popleft())
    
    while stack:
        queue.append(stack.pop())
    
    for _ in range(half_size):
        queue.append(queue.popleft())
    
    return queue

def can_be_arranged_increasing_order(queue):
    expected_num = 1
    stack = []
    
    while queue:
        if queue[0] == expected_num:
            queue.popleft()
            expected_num += 1
        elif stack and stack[-1] == expected_num:
            stack.pop()
            expected_num += 1
        else:
            stack.append(queue.popleft())
    
    while stack:
        if stack[-1] == expected_num:
            stack.pop()
            expected_num += 1
        else:
            return False
    
    return True

from collections import deque

def rearrange_with_stack(queue):
    if len(queue) % 2 != 0:
        return "Queue length must be even"

    stack = deque()
    half_size = len(queue) // 2

    # Push the first half of the queue onto the stack
    for _ in range(half_size):
        stack.append(queue.popleft())

    # Interleave elements from the stack and the remaining queue
    while stack:
        queue.append(stack.pop())
        queue.append(queue.popleft())

    return queue

from collections import deque

def rearrange_with_queue(queue):
    if len(queue) % 2 != 0:
        return "Queue length must be even"

    half_size = len(queue) // 2
    first_half = deque()
    second_half = deque()

    # Split the queue into two halves
    for _ in range(half_size):
        first_half.append(queue.popleft())
    for _ in range(half_size):
        second_half.append(queue.popleft())

    # Interleave elements from the two halves
    while first_half and second_half:
        queue.append(first_half.popleft())
        queue.append(second_half.popleft())

    return queue





def main():
    # 1. Reverse the first k elements of a queue
    print("1. Reverse the first k elements of a queue:")
    queue = deque([1, 2, 3, 4, 5])
    k = 3
    print("Original queue:", queue)
    print("Reversed first", k, "elements:", reverse_first_k(queue.copy(), k))

    # 2. Rearrange elements of a queue by interleaving the first half with the second half

    # Example usage:
    queue = deque([1, 2, 3, 4, 5, 6])
    print("Original queue:", queue)
    print("Rearranged queue with stack:", rearrange_with_stack(queue.copy()))

    print("Original queue:", queue)
    print("Rearranged queue with queue:", rearrange_with_queue(queue.copy()))

    # 3. Check if a queue of first n natural numbers can be arranged in increasing order using a stack
    print("\n3. Check if a queue of first n natural numbers can be arranged in increasing order using a stack:")
    queue = deque([4, 1, 2, 3])
    print("Original queue:", queue)
    print("Can be arranged in increasing order:", can_be_arranged_increasing_order(queue.copy()))
    print("""
4. Ordering Functions by Asymptotic Complexity:
   - The sequence is as follows, from smallest to largest asymptotic complexity:
     1. 8^logn
     2. Log n^n
     3. n^3/2
     4. 3.n^2
     5. n^log7
     6. 3.n^2+2.n^3
     7. 2.3^n
     8. 3.2^n
   - Functions f and g that are asymptotically equivalent: None in the provided list.
5. Proving or Disproving Statements:
   a) True. 8n + n·log2n is O(n) because it grows linearly with n.
   b) True. (n + a)b is Ω(nb) because it grows at least as fast as nb for all real numbers a, b > 0.
   c) False. n^a is Θ(nb) if and only if a = b for all real numbers a, b > 0 is not always true. For example, n^2 is Θ(n^3) but 2 ≠ 3.
""")

if __name__ == "__main__":
    main()
