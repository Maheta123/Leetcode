from dataclasses import dataclass
from typing import List


@dataclass
class Factory:
    pos: int
    capacity: int
    used: int = 0
    first_bot_idx: int = -1  # Index of the first robot currently in this factory
    shift_penalty: int = 0 # Cost to move the first robot to the previous factory


class Solution:
    def minimumTotalDistance(self, robots: List[int], factory: List[List[int]]) -> int:
        robots.sort()
        
        # Add boundary sentinels to avoid index-out-of-bounds
        factories_data = [[-int(1e15), 1]] + sorted(f for f in factory if f[1] > 0) + [[int(1e15), 1]]
        
        factories = [
            Factory(pos=f[0], capacity=f[1]) for f in factories_data
        ]

        def update_shift_penalty(f_idx: int):
            """Calculates penalty to move the 'first' robot of factory[f_idx] to factory[f_idx-1]."""
            curr_f = factories[f_idx]
            prev_f = factories[f_idx - 1]
            bot_pos = robots[curr_f.first_bot_idx]
            
            # Penalty = (Distance to previous factory) - (Distance to current factory)
            curr_f.shift_penalty = abs(bot_pos - prev_f.pos) - abs(bot_pos - curr_f.pos)

        def assign_and_shift(bot_idx: int, f_idx: int):
            """Recursively shifts robots left if the chosen factory is full."""
            target_f = factories[f_idx]
            
            while target_f.used == target_f.capacity:
                # Kick the leftmost robot out of this factory
                displaced_bot_idx = target_f.first_bot_idx
                target_f.first_bot_idx += 1
                update_shift_penalty(f_idx)
                
                # The displaced robot now needs to be handled by the previous factory
                bot_idx = displaced_bot_idx
                f_idx -= 1
                target_f = factories[f_idx]
                
            if target_f.used == 0:
                target_f.first_bot_idx = bot_idx
                
            target_f.used += 1
            if target_f.used > 0:
                update_shift_penalty(f_idx)

        total_ans = 0
        factory_ptr = 1 # Start at the first real factory (skipping -inf)

        for bot_idx, bot_pos in enumerate(robots):
            # 1. Find the current factory
            if factories[factory_ptr].pos < bot_pos:
                while factories[factory_ptr + 1].pos < bot_pos:
                    factory_ptr += 1
            
            # 2. Calculate cost to go RIGHT
            right_cost = factories[factory_ptr + 1].pos - bot_pos
            
            # 3. Calculate cost to go LEFT (including all shift penalties)
            left_cost = abs(factories[factory_ptr].pos - bot_pos)
            
            # If the left factory is full, we must add the penalties of shifting its robots
            temp_idx = factory_ptr
            while factories[temp_idx].used == factories[temp_idx].capacity:
                left_cost += factories[temp_idx].shift_penalty
                temp_idx -= 1
                
            # 4. Make the greedy decision
            if left_cost <= right_cost:
                total_ans += left_cost
                assign_and_shift(bot_idx, factory_ptr)
            else:
                factory_ptr += 1
                total_ans += right_cost
                assign_and_shift(bot_idx, factory_ptr)

        return total_ans                
            