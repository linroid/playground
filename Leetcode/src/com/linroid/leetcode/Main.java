package com.linroid.leetcode;

import java.util.*;

public class Main {

    private List<List<Character>> result = new ArrayList<>();

    public static  void main(String[] args){
//        ArrayList<Integer> test = new ArrayList<>();
//        test.add(5);
//        test.add(6);
//        test.add(0, 1);
//        System.out.println(test.toString());
        TreeNode a = new TreeNode('A');
        TreeNode b = new TreeNode('B');
        TreeNode c = new TreeNode('C');
        TreeNode d = new TreeNode('D');
        TreeNode e = new TreeNode('E');
        TreeNode f = new TreeNode('F');
        TreeNode g = new TreeNode('G');
        b.left = d;
        b.right = e;
        c.left = f;
        c.right = g;
        a.left = b;
        a.right = c;
        new Main().print(a);
    }

    public void print(TreeNode root) {
        traversal(root, 0);
        for(List<Character> line : result){
            for(Character val: line){
                System.out.print(" " + val);
            }
        }
    }

    //refactor
    private void traversal(TreeNode node, int depth){
        if(node == null){
            return;
        }

        List<Character> line;
        if(depth >= result.size()){
            line = new LinkedList<>();
            result.add(line);
        } else{
            line = result.get(depth);
        }
        if(depth%2 == 0){
            line.add(node.val);
        }else{
            line.add(0, node.val);
        }

        traversal(node.left, depth+1);
        traversal(node.right, depth+1);

    }
}

