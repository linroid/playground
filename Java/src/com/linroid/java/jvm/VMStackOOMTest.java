package com.linroid.java.jvm;

/**
 * VM option: -Xss 2M
 * Created by linroid on 4/13/15.
 */
public class VMStackOOMTest {
    private void dontStop(){
        for(;;){

        }
    }
    public void stackLeakByThread(){
        for(;;){
            Thread thread = new Thread(() -> {
                dontStop();
            });
            thread.start();
        }
    }

    public static void main(String[] args) {
        VMStackOOMTest oom = new VMStackOOMTest();
        oom.stackLeakByThread();
    }
}
