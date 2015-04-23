package com.linroid.leetcode.rangeBitwiseAnd;

/**
 * Created by linroid on 4/24/15.
 * 问题简化:求m和n的最高相同位
 * @link https://leetcode.com/problems/bitwise-and-of-numbers-range/
 */
public class Solution {
    public int rangeBitwiseAnd(int m, int n) {
        for(int i=0; i<31; i++){
            if((m>>(30-i)) != n>>(30-i)){
                return n>>(31-i)<<(31-i);
            }
        }
        return m;
    }

    public int rangeBitwiseAndVerify(int m, int n) {
        int ans = 0xFFFFFFFF;

        for (; m <= n; m++) {
            System.out.println("\t" + Integer.toBinaryString(m) + "\t" + m);
            ans = ans & m;
        }
        System.out.println("\t" + Integer.toBinaryString(ans) + "\t" + ans);
        System.out.println("\n\n\n");
        return ans;
    }

    public static void main(String[] args) {

        Solution solution = new Solution();

        for (int i = 1; i < 30; i++) {
            for (int j = i + 1; j <= 30; j++) {
                int s = solution.rangeBitwiseAndVerify(i, j);
                int q = solution.rangeBitwiseAnd(i, j);
                if (s != q) {
                    throw new IllegalStateException("error");
                }
            }
        }
    }
}