package Computator.Md2Handler;

import AdditionalClasses.Matrix;

class Checksum {
    private int C_SIZE = 16;
    private int[] C = new int[C_SIZE];
    private int[] M;
    private int L;
    private int N;

    Checksum(int[] M) {
        this.M = new int[M.length];
        System.arraycopy(M, 0, this.M, 0, M.length);
        this.N = M.length - 16;
    }

    int[] append() {
        clear();
        L = 0;
        blockProcess();
        updateMessage();
        return M;
    }

    private void clear() { for (int i = 0; i < C_SIZE; i++) C[i] = 0; }

    private void blockProcess() {
        for (int i = 0; i < N / C_SIZE; i++) {
            blockChecksum(i);
        }
    }

    private void blockChecksum(int i) {
        for (int j = 0; j < C_SIZE; j++) {
            int c = M[i * 16 + j];
            C[j] ^= Matrix.S(c ^ L);
            L = C[j];
        }
    }

    private void updateMessage() {
        System.arraycopy(C, 0, M, M.length - 16, 16);
    }
}
