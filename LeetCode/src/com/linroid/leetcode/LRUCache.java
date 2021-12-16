package com.linroid.leetcode;

import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.Queue;

/**
 * Created by linroid on 4/23/15.
 * @link https://leetcode.com/problems/lru-cache/
 * <p/>
 * Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
 * <p/>
 * get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 * set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 */
public class LRUCache {
    private int maxSize;
    private int size = 0;

    private HashMap<Integer, Entry> map;
    private Entry head;
    private Entry last;

    public LRUCache(int capacity) {
        if (capacity < 0) {
            throw new IllegalArgumentException("capacity must bigger than 0!");
        }
        this.maxSize = capacity;
        this.map = new HashMap<>(capacity);
    }

    public int get(int key) {
        if (!map.containsKey(key)) {
            return -1;
        }

        Entry entry = map.get(key);
        if (entry != last) {
            //is the head?
            if (entry == head) {
                head = entry.next;
            } else {
                entry.prev.next = entry.next;
            }
            entry.next.prev = entry.prev;
            entry.prev = last;
            entry.next = null;
            last.next = entry;
            last = entry;
        }

        return entry.val;
    }

    public void set(int key, int value) {
        if (get(key) == -1) {
            Entry entry = new Entry(key, value);
            map.put(key, entry);
            this.size++;

            if (head == null) {
                head = entry;
                last = entry;
                return;
            }

            last.next = entry;
            entry.prev = last;
            last = entry;
            ensureCapacity();
        } else {
            map.get(key).val = value;
        }
    }

    private void ensureCapacity() {
        while (true) {
            if (size <= maxSize) {
                break;
            }
            map.remove(head.key);
            head = head.next;
            head.prev = null;
            size--;
        }
    }

    public static void main(String[] args) {
        LRUCache cache = new LRUCache(2);
        cache.set(2, 1);
        cache.set(3, 2);
        System.out.println(cache.get(3));
        System.out.println(cache.get(2));
        cache.set(4, 3);
        System.out.println(cache.get(2));
        System.out.println(cache.get(3));
        System.out.println(cache.get(4));

    }

    class Entry {
        Entry prev;
        Entry next;
        int val;
        int key;

        public Entry(int key, int val) {
            this.key = key;
            this.val = val;
        }

        @Override
        public String toString() {
            return key + " => " + val;
        }
    }
}