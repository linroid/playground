package com.linroid.algorithms.dp;

/**
 * Created by linroid on 4/24/15.
 * <p/>
 * 一个序列有N个数：A[1],A[2],…,A[N]，求出最长非降子序列的长度。
 */
public class LongestIncreasingSubsequence {
    private int[] sequence;

    public LongestIncreasingSubsequence(int[] sequence) {
        this.sequence = sequence;
    }

    private int longestLength() {

    }

    public static void main(String[] args) {
        int[] sequence = new int[]{ 5, 3, 4, 8, 6, 7};
        LongestIncreasingSubsequence solution = new LongestIncreasingSubsequence(sequence);
        System.out.printf("%d\n", solution.longestLength());
    }
}
