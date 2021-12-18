package com.linroid.opengl;

import android.content.res.Resources;
import android.opengl.GLES20;
import android.support.annotation.RawRes;

import java.io.IOException;
import java.io.InputStream;

import okio.BufferedSource;
import okio.Okio;
import timber.log.Timber;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class GLUtils {
    final static int[] status = new int[1];

    public static void dumpIfHasError() {
        int error = GLES20.glGetError();
    }

    public static int loadShader(int type, String shaderCode) {
        int shader = GLES20.glCreateShader(type);
        if (shader == 0) {
            Timber.e("Count not create new shader.");
            return 0;
        }
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);
        GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, status, 0);
        Timber.i("Code:\n%s\n\nStatus: %d\n\nInfo: %s", shaderCode, status[0], GLES20.glGetShaderInfoLog(shader));
        if (status[0] == 0) {
            GLES20.glDeleteShader(shader);
            Timber.e("Compilation of shader failed.");
            return 0;
        }
        return shader;
    }

    public static int loadShader(int type, @RawRes int resId) {
        Resources resources = App.get().getResources();
        InputStream input = resources.openRawResource(resId);
        BufferedSource reader = Okio.buffer(Okio.source(input));
        try {
            String shaderCode = reader.readUtf8();
            return loadShader(type, shaderCode);
        } catch (IOException e) {
            Timber.e(e, "read shader raw resource[%d] failed", resId);
        }
        return 0;
    }

    public static int linkProgram(int vertexShader, int fragmentShader) {
        int program = GLES20.glCreateProgram();
        if (program == 0) {
            Timber.e("Could not create new program.");
            return 0;
        }
        GLES20.glAttachShader(program, vertexShader);
        GLES20.glAttachShader(program, fragmentShader);
        GLES20.glLinkProgram(program);
        GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, status, 0);
        if (status[0] == 0) {
            GLES20.glDeleteProgram(program);
            Timber.e("link program failed: %d", status[0]);
            return 0;
        }
        return program;
    }

    public static boolean validateProgram(int program) {
        GLES20.glValidateProgram(program);
        GLES20.glGetProgramiv(program, GLES20.GL_VALIDATE_STATUS, status, 0);
        Timber.d("validateProgram: %d, Status: %d, Log:%s", program, status[0], GLES20.glGetProgramInfoLog(program));
        return status[0] != 0;
    }

}
