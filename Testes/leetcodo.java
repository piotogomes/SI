package Testes;

import java.util.*;

class Solution {
    public int timeRequiredToBuy(int[] tickets, int k) {
        int sec = 0;
        for(int i = 0; tickets[k] != 0; i = (i + 1) % tickets.length) {
            if(tickets[i] > 0) {
                tickets[i]--;
                sec++;
            }
        }
        return sec;
    }

    public static void main(String[] args) {
        int[] vec = {5,1,1,1};

        Solution sol = new Solution();
        System.out.println(sol.timeRequiredToBuy(vec, 1));

    }
}
