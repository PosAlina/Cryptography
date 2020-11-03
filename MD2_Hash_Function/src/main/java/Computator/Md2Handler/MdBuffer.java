package Computator.Md2Handler;

import AdditionalClasses.Matrix;
import AdditionalClasses.Printer;

import java.util.Arrays;

class MdBuffer {
    private int[] M;
    private  int N;
    private int t = 0;
    private int[] X = new int[48];
    private int[] result = new int[16];

    MdBuffer(int[] M) {
        this.M = new int[M.length];
        System.arraycopy(M, 0, this.M, 0, M.length);
        this.N = M.length;
    }

    int[] append() {
        process();
        System.arraycopy(X, 0, result, 0, 16);
        return result;
    }

    private void process() {
        for (int i = 0; i < N / 16; i++) {
            copyBlock(i);
            t = 0;
            rounds_18();
        }
    }

    private void copyBlock(int i) {
        for(int j = 0; j < 16; j++) {
            X[16 + j] = M[ i * 16 + j];
            X[32 + j] = X[16 + j] ^ X[j];
        }
    }

    private void rounds_18() {
        for (int j = 0; j <= 17; j++) {
            round_j();
            t = (t + j) % 4;
        }
    }

    private void round_j() {
        for (int k = 0; k <= 47; k++) {
            X[k] ^= Matrix.S(t);
            t = X[k];
        }
    }
}
