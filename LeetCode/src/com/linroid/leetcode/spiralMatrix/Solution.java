package com.linroid.leetcode.spiralMatrix;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by linroid on 4/23/15.
 * @link https://leetcode.com/problems/spiral-matrix/
 * <p/>
 * Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
 * <p/>
 * For example,
 * Given the following matrix:
 * <p/>
 * <pre>
 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 * </pre>
 * You should return [1,2,3,6,9,8,7,4,5].
 * <pre>
 * 1    2   3   4
 * 5    6   7   8
 * 9    10  11  12
 * 13   14  15  16
 * </pre>
 */
public class Solution {
    public static void main(String[] args) {
        int[][] matrix = new int[][]{
//                { 1, 2, 3, 4 },
//                { 5, 6, 7, 8 },
//                { 9, 10, 11, 12 },
//                { 13, 14, 15, 16 }
                {6, 9, 7}
        };
        Solution solution = new Solution();
        System.out.println(solution.spiralOrder(matrix));
    }

    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> result = new ArrayList<>();

        if (matrix.length == 0) {
            return result;
        }
        int colMin = 0;
        int colMax = matrix[0].length - 1;
        int rowMin = 0;
        int rowMax = matrix.length - 1;


        //每次迭代一圈,然后缩小范围
        while (colMin <= colMax && rowMin <= rowMax) {

            if (colMin == colMax && rowMin == rowMax) {
                result.add(matrix[rowMin][rowMax]);
                break;
            }

            //when only one col
            if (colMin == colMax) {
                for (int i = rowMin; i <= rowMax; i++) {
                    result.add(matrix[i][colMin]);
                }
                break;
            }
            //when only one row
            if (rowMin == rowMax) {
                for (int i = colMin; i <= colMax; i++) {
                    result.add(matrix[rowMin][i]);
                }
                break;
            }


            //left to right
            for (int i = colMin; i <= colMax - 1; i++) {
                result.add(matrix[rowMin][i]);
            }

            //top to bottom
            for (int i = rowMin; i <= rowMax - 1; i++) {
                result.add(matrix[i][colMax]);
            }

            //right to left
            for (int i = colMax; i > colMin; i--) {
                result.add(matrix[rowMax][i]);
            }

            //bottom to top
            for (int i = rowMax; i > colMin; i--) {
                result.add(matrix[i][colMin]);
            }

            colMin++;
            colMax--;
            rowMin++;
            rowMax--;
        }
        return result;
    }
}