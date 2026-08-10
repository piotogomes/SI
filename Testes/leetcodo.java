
package Testes;

import java.util.*;

class Solution {
    public int[] plusOne(int[] digits) {
        // Percorre do último dígito até o primeiro
        for (int i = digits.length - 1; i >= 0; i--) {
            // Se o dígito for menor que 9, basta somar 1 e retornar!
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            // Se for 9, vira 0 e o loop continua para somar 1 no anterior
            digits[i] = 0;
        }

        // Se chegou até aqui, significa que todos os dígitos eram 9 (ex: 999 -> 000)
        // Precisamos de um novo array com tamanho + 1 (ex: [1, 0, 0, 0])
        int[] result = new int[digits.length + 1];
        result[0] = 1; // Em Java, os outros elementos já iniciam como 0 por padrão
        return result;
    }c

    public static void main(String[] args) {
        int[] temperatures = { 9, 9, 9, 9 };
        Solution sol = new Solution();
        System.out.println(sol.plusOne(temperatures));

    }
}
