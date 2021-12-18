package com.linroid.opengl;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class Sizeof {
    public static final int INT = 4;

    public static final int SHORT = 2;
    public static final int FLOAT = 4;
    public static final int DOUBLE = 8;
    public static final int CHAR = 1;

    public static int INT(int count) {
        return count * INT;
    }

    public static int SHORT(int count) {
        return count * SHORT;
    }

    public static int FLOAT(int count) {
        return count * FLOAT;
    }

    public static int DOUBLE(int count) {
        return count * DOUBLE;
    }

    public static int CHAR(int count) {
        return count * CHAR;
    }
}
