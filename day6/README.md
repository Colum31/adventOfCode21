## Reflections on the solution of Day 6

# Part 1

I feel like have taken the low hanging fruit for part one. I reused code to create a linked list,
as this was my first idea, on how to solve the task.

# Part 2

When confronted with part two, the code did not terminate. It got slower and slower, and I killed it  after it taking around 32g of RAM.  
  
I then thought about an alternative way, and I came up with an array, that holds the amount of fish
in every "cycle". This way, I would only use around 72 bytes of memory. To calculate the next cycle,
I would just shift the numbers in the array to the left, resulting in O(c * 9) time complexity.  
I feel stupid, for not having came up with this for part 1.
