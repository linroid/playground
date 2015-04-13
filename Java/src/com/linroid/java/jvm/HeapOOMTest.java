package com.linroid.java.jvm;

import java.util.ArrayList;
import java.util.List;

/**
 * VM option: -Xms20m -Xmx20m -XX:+HeapDumpOnOutOfMemoryError
 * Created by linroid on 4/13/15.
 */
public class HeapOOMTest {
    static class OOMObject {

    }
    public static void main(String[] args) {
        List<OOMObject> list = new ArrayList<>();
        try {
            while (true) {
                list.add(new OOMObject());
            }
        } catch (OutOfMemoryError error){
            error.printStackTrace();
            System.err.println("共实例化了: " + list.size() + " 个OOMObject对象");
        }

    }
}
