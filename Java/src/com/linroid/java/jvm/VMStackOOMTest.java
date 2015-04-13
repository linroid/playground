package com.linroid.java.jvm;

/**
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
