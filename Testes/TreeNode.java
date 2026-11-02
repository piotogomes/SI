package Testes;

import java.util.*;

class Solution {
    public int minPartitions(String n) {
        String s = n;
        char count = '0';
        for (char c : s.toCharArray()) {
            if (count < c) {
                count = c;
            }
        }
        return count - 48;
    }

    public static void main(String[] args) {
        String a1 = "27346209830709182346";
        Solution sol = new Solution();
        System.out.println(sol.minPartitions(a1));
    }
}
