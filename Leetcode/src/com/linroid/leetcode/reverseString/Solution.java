package com.linroid.leetcode.reverseString;

import java.util.Stack;

/**
 * @author linroid @ Zhihu Inc.
 * @since 10-09-2016
 */
public class Solution {
    public String reverseString(String s) {
        if (s == null) {
            return s;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = s.length() - 1; i >= 0; i--) {
            sb.append(s.charAt(i));
        }
        return sb.toString();
    }

    public boolean isValid(String s) {
        if (s == null) {
            return true;
        }
        int len = s.length();
        Stack<Character> stack = new Stack<>();
        for (int i = 0; i < len; i++) {
            char ch = s.charAt(i);
            if (ch == '[' || ch == '(' || ch == '{') {
                stack.push(ch);
            } else if (ch == ']' || ch == ')' || ch == '}') {
                if (stack.isEmpty()) {
                    return false;
                }
                char pop = stack.pop();
                if (ch==']' && pop !='[') {
                    return false;
                }
                if (ch==')' && pop !='(') {
                    return false;
                }
                if (ch=='}' && pop !='{') {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }
}