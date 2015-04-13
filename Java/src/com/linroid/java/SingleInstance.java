package com.linroid.java;
/**
 * Created by linroid on 4/12/15.
 */
public class SingleInstance {
    static {
        System.out.println("SingleInstance static");
    }
    private SingleInstance() {
        System.out.println("SingleInstance构造了");
    }

    public static SingleInstance getInstance() {
        return SingleInstanceHolder.sInstance;
    }

    private static class SingleInstanceHolder {
        static {
            System.out.println("SingleInstanceHolder static");
        }
        private static SingleInstance sInstance = new SingleInstance();
    }

    public static void main(String[] args) {
        SingleInstance.getInstance();
    }
}
