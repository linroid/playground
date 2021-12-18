package com.linroid.airhockey

import android.app.Application
import timber.log.Timber

/**
 * @author linroid <linroid@gmail.com>
 * @since 12/05/2017
 */
class App : Application() {

    companion object {
        @JvmStatic private lateinit var instance: App
        @JvmStatic fun get(): App = instance
    }

    override fun onCreate() {
        super.onCreate()
        instance = this
        if (BuildConfig.DEBUG) {
            Timber.plant(Timber.DebugTree())
        }
    }
}
