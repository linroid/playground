package com.linroid.leetcode.mergeSortedArray;

import com.linroid.leetcode.Testable;

import java.util.Random;

/**
 * Created by linroid on 4/1/15.
 */
public class Solution implements Testable {
    public void merge(int A[], int m, int B[], int n) {
        int[] C = A.clone();
        int i=0, j=0;
        for(int k=0; k<m+n; k++){
            if(i>=m){
                A[k] = B[j++];
            }else if(j>=n){
                A[k] = C[i++];
            }else if(C[i] < B[j]){
                A[k] = C[i++];
            }else{
                A[k] = B[j++];
            }
        }
    }

    @Override
    public boolean test() {
        Random random = new Random();
        int A[] = new int[50];
        int B[] = new int[50];
        int m = 5, n=0;
        for(int i=0; i<m; i++){
            A[i] = 50+i*5;
        }
        for (int i=0; i<n; i++){
            B[i] = 30+i*7;
        }

        merge(A, m, B, n);
        for (int i=0; i<m+n-1; i++){
            if(A[i] > A[i+1]){
                return false;
            }
        }
        return true;
    }
}