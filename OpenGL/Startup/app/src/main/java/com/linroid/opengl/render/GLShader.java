package com.linroid.opengl.render;

import android.opengl.GLES20;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class GLShader {
    public static int loadShader(int type, String shaderCode) {
        int shader = GLES20.glCreateShader(type);
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);
        return shader;
    }
}
