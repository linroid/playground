package com.linroid.algorithms.dp;

/**
 * Created by linroid on 4/24/15.
 * 如果我们有面值为n元的硬币若干枚，如何用最少的硬币凑够m元？
 */
public class CoinCount {
    private int[] coins;

    public CoinCount(int[] coins) {
        this.coins = coins;
    }

    public int minConsist(int m) {
        return dp(m, m);
    }

    private int dp(int m, int minCount) {
        if (m == 0) {
            return 0;
        }

        for (int coin : coins) {
            if (coin <= m) {
                minCount = Math.min(dp(m - coin, minCount) + 1, minCount);
            }
        }
        return minCount;
    }

    public static void main(String[] args) {
        CoinCount solution = new CoinCount(new int[]{1, 3, 5});
        for (int i = 0; i <= 11; i++) {
            System.out.printf("凑够%d元至少需要 %d枚硬币\n", i, solution.minConsist(i));
        }
    }
}
