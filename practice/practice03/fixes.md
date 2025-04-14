# Fixes for practice03.cpp

## 1. sumRange function
- **Bug:** Used `for (int i = start; i < end; i++)` — off-by-one error.
- **Fix:** Changed to `i <= end` to include the end value.
- **Impact:** Without the fix, the function excluded the last value in the range.

## 2. containsNegative function
- **Bug:** Used `if (numbers[i] > 0)` — should check `< 0` for negatives.
- **Fix:** Changed condition to `numbers[i] < 0`.
- **Bug:** Loop condition was `i <= numbers.size()` — out-of-bounds.
- **Fix:** Changed to `i < numbers.size()`.

## 3. findMax function
- **Bug:** Loop goes to `i <= numbers.size()` — out-of-bounds.
- **Fix:** Changed to `i < numbers.size()`.
- **Bug:** Accessed `numbers[i]` before checking if the vector is empty.
- **Fix:** Added an early return for empty vector.