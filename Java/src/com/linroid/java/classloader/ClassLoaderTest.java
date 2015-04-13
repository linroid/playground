package com.linroid.java.classloader;

import sun.misc.Launcher;

import java.net.URL;
import java.util.Properties;

/**
 * Created by linroid on 4/12/15.
 */
public class ClassLoaderTest {
    public static void main(String[] args){
        dumpPaths();
    }

    public static void dumpPaths() {
        URL[] urls = Launcher.getBootstrapClassPath().getURLs();
        for (URL url : urls) {
            System.out.println(url.toExternalForm());
        }
        Properties properties = System.getProperties();
        for(Object key : properties.keySet()){
            System.out.println("\t"+key+"=\t"+properties.getProperty(key.toString()));
        }
        System.out.println(properties.getProperty("sun.boot.class.path"));
    }
}
