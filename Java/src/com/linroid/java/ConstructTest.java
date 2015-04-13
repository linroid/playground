package com.linroid.java;

/**
 * Created by linroid on 4/12/15.
 */
public class ConstructTest {
    private TestInner inner = new TestInner();
    static {
        System.out.println("ConstructTest static");
    }
    public ConstructTest() {
        System.out.println("ConstructTest constructor");
    }

    private class TestInner{
        public TestInner() {
            System.out.println("TestInner constructor");
        }
    }

    public static void main(String[] args) {
        new ConstructTest();
    }
}
