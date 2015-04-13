package com.linroid.java.jvm;

/**
 * Created by linroid on 4/13/15.
 */
public class VMStackSOFTest {
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
        VMStackSOFTest oom = new VMStackSOFTest();
        oom.stackLeakByThread();
    }
}
