package com.linroid.java.jvm;

import java.util.ArrayList;
import java.util.List;

/**
 * Warning: 在jdk1.7及以上会一直运行下去
 * VM option: -XX:PermSize=10M -XX:MaxPermSize=10M
 * Created by linroid on 4/13/15.
 */
public class RuntimeConstantPoolOOMTest {
    public static void main(String[] args) throws IllegalAccessException {
        List<String> list = new ArrayList<>();
        int i = 0;

        while (true) {
            list.add(String.valueOf(i++).intern());
        }
    }
}
