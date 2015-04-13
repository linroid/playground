package com.linroid.java;
/**
 * Created by linroid on 4/12/15.
 */
public class SingleInstanceTest {
    static {
        System.out.println("SingleInstanceTest static");
    }
    private SingleInstanceTest() {
        System.out.println("SingleInstance构造了");
    }

    public static SingleInstanceTest getInstance() {
        return SingleInstanceHolder.sInstance;
    }

    private static class SingleInstanceHolder {
        static {
            System.out.println("SingleInstanceHolder static");
        }
        private static SingleInstanceTest sInstance = new SingleInstanceTest();
    }

    public static void main(String[] args) {
        SingleInstanceTest.getInstance();
    }
}
