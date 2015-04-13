package com.linroid.leetcode.combinationSum2;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Solution {
    public List<List<Integer>> combinationSum2(int[] num, int target) {
        List<List<Integer>> ans;
        Arrays.sort(num);
        ans = restItems(num, target, 0);
        List<Integer> prev = null;
        for(int i=0; i<ans.size(); i++){
            List<Integer> item = ans.get(i);
            if(item.equals(prev)) {
                ans.remove(item);
            } else {
                prev = item;
            }
        }
        return ans;
    }
    private List<List<Integer>> restItems(int[] num, int target, int startIndex){
        List<List<Integer>> ans = new LinkedList<>();
        for(int i=startIndex; i<num.length; i++){
            if(num[i] > target){
                continue;
            }else if(num[i] == target){
                List<Integer> item = new LinkedList<>();
                item.add(num[i]);
                ans.add(item);
            }else{
                List<List<Integer>> items = restItems(num, target-num[i], i+1);
                for (List<Integer> child : items) {
                    List<Integer> item = new ArrayList<>();
                    item.add(num[i]);
                    item.addAll(child);
                    ans.add(item);
                }
            }
        }
        return ans;
    }

}
