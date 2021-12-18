package com.linroid.airhockey.utils

import android.graphics.BitmapFactory
import android.opengl.GLES20.*
import android.opengl.GLUtils
import android.support.annotation.DrawableRes
import android.support.annotation.IntDef
import android.support.annotation.RawRes
import com.linroid.airhockey.App
import okio.Okio
import timber.log.Timber
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

/**
 * @author linroid <linroid@gmail.com>
 * @since 12/05/2017
 */
object GLLoader {
    private val GL_STATUS = IntArray(1)

    fun shader(@RawRes resId: Int, type: Int): Int {
        // read glsl
        val context = App.get()
        val stream = context.resources.openRawResource(resId)
        val buffer = Okio.buffer(Okio.source(stream))
        val content = buffer.readString(Charsets.UTF_8)

        // create and compile shader
        val shader = glCreateShader(type)

        if (shader == 0) {
            Timber.e("create shader failed")
            return 0
        }
        glShaderSource(shader, content)
        glCompileShader(shader)

        Timber.d("Compile shader\n======\n%s\n=========\n%s", content, glGetShaderInfoLog(shader))
        glGetShaderiv(shader, GL_COMPILE_STATUS, GL_STATUS, 0)
        if (GL_STATUS[0] == 0) {
            glDeleteShader(shader)
            Timber.e("Compilation of shader failed.")
            return 0
        }
        return shader
    }

    fun vertex(data: FloatArray): FloatBuffer {
        val bb = ByteBuffer.allocateDirect(data.size * Sizeof.FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
        bb.put(data)
        return bb
    }

    fun program(vertexShader: Int, fragShader: Int): Int {
        val program = glCreateProgram()
        if (program == 0) {
            Timber.e("Create program failed")
            return 0
        }
        glAttachShader(program, vertexShader)
        glAttachShader(program, fragShader)
        glLinkProgram(program)

        glGetProgramiv(program, GL_LINK_STATUS, GL_STATUS, 0)
        Timber.d("Link program: %d %d => %d, Status: %s", vertexShader, fragShader, program, glGetProgramInfoLog(program))
        if (GL_STATUS[0] == 0) {
            glDeleteProgram(program)
            Timber.e("link program failed: vertex=%d, fragment=%d", vertexShader, fragShader)
            return 0
        }
        glValidateProgram(program)
        glGetProgramiv(program, GL_VALIDATE_STATUS, GL_STATUS, 0)
        if (GL_STATUS[0] == 0) {
            Timber.e("Link program: %d, Status: %s", program, glGetProgramInfoLog(program))
            return 0
        }
        return program
    }

    fun texture(@DrawableRes resId: Int): Int {
        val ids = IntArray(1)
        glGenTextures(1, ids, 0)
        if (ids[0] == 0) {
            Timber.e("glGenTextures failed")
            return 0
        }
        glBindTexture(GL_TEXTURE_2D, ids[0])
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)


        val options = BitmapFactory.Options()
        options.inScaled = false
        val bitmap = BitmapFactory.decodeResource(App.get().resources, resId, options)
        GLUtils.texImage2D(GL_TEXTURE_2D, 0, bitmap, 0)
        bitmap.recycle()

        glGenerateMipmap(GL_TEXTURE_2D)

        glBindTexture(GL_TEXTURE_2D, ids[0])

        return ids[0]

    }
}