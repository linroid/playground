package com.linroid.leetcode.searchInsert;

/**
 * Created by linroid on 4/23/15.
 * @link https://leetcode.com/problems/search-insert-position/
 * <p/>
 * Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
 * <p/>
 * You may assume no duplicates in the array.
 * <p/>
 * Here are few examples.
 * <pre>
 * [1,3,5,6], 5 → 2
 * [1,3,5,6], 2 → 1
 * [1,3,5,6], 7 → 4
 * [1,3,5,6], 0 → 0
 * </pre>
 */

public class Solution {
    public int searchInsert(int[] A, int target) {
        int index = 0;
        while (index < A.length && target > A[index]) {
            if (A[index] == target) {
                return index;
            }
            index++;
        }
        return index;
    }

    public static void main(String[] args) {
        int[] input = new int[]{1, 3, 5, 6};
        Solution solution = new Solution();
        int result = solution.searchInsert(input, 5);
        System.out.println(result);
    }
}