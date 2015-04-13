package com.linroid.java.jvm;

/**
 * VM option -Xss128k
 * Created by linroid on 4/13/15.
 */
public class VMStackSOFTest {
    private int stackLength = 1;
    public void stackLeak() {
        stackLength++;
        stackLeak();
    }
    public static void main(String[] args) {
        VMStackSOFTest test = new VMStackSOFTest();
        try {
            test.stackLeak();
        }catch (Throwable error){
            System.err.println("栈的深度: " + test.stackLength);
            throw error;
        }
    }
}
