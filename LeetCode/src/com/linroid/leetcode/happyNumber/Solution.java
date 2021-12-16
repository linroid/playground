package com.linroid.leetcode.happyNumber;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by linroid on 4/24/15.
 * @link https://leetcode.com/problems/happy-number/
 */
public class Solution {
    public boolean isHappy(int n) {
        Map<Integer, Void> map = new HashMap<>();
        while (true) {
            n = sumSquare(n);
            if(n == 1){
                return true;
            }
            if(map.containsKey(n)){
                return false;
            }
            map.put(n, null);
        }
    }
    private int sumSquare(int n) {
        System.out.print(n);
        int r = 0;
        while (n>0) {
            r += (n%10) * (n%10);
            n = n /10;
        }
        System.out.println(" => "+r);
        return r;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        System.out.println(solution.isHappy(19));
    }
}