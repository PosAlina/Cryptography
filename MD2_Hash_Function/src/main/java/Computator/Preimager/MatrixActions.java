package Computator.Preimager;

import AdditionalClasses.Matrix;
import AdditionalClasses.Printer;
import Computator.Compressor.Compressor;
import org.jetbrains.annotations.NotNull;

import javax.lang.model.type.PrimitiveType;
import java.util.*;

class MatrixActions {
    // Matrix for compression function
    private int LINE_NUMBER = 19;
    private int COLUMN_NUMBER = 16;
    private int BLOCK_SIZE = 16;
    private String S_H_i_1 = null;
    private int[] H_i = new int[BLOCK_SIZE];
    private int[] H_i_1 = new int[BLOCK_SIZE];
    private int[][] A = new int[LINE_NUMBER][COLUMN_NUMBER];
    private int[][] B = new int[LINE_NUMBER][COLUMN_NUMBER];
    private int[][] C = new int[LINE_NUMBER][COLUMN_NUMBER];

    static class Block implements Comparable<Block> {
        int[] bytes;

        Block(int[] bytes) {
            this.bytes = bytes;
        }

        @Override
        public int compareTo(@NotNull MatrixActions.Block o) {
            for (int i = 0; i < 8; i++)
                if (this.bytes[i] != o.bytes[i]) return this.bytes[i] - o.bytes[i];
            return 0;
        }

        private int[] getBytes() {
            return bytes;
        }
    }

    private List<Block> T1 = new ArrayList<>();
    private List<Block> T2 = new ArrayList<>();
    private List<Block> T = new ArrayList<>();
    private List<int[]> T_ = new ArrayList<>();

    List<int[]> getM() {
        return getMes();
    }

    private List<int[]> getMes() {
        for (Block ms : T) {
            int[] mes = new int[16];
            System.arraycopy(ms.getBytes(), 0, mes, 0, BLOCK_SIZE);
            Compressor compressor = new Compressor(H_i, mes);
            String h_j_1 = compressor.compute();
            if (S_H_i_1.equals(h_j_1)) T_.add(mes);
        }
        return T_;
    }

    void attack(int[] H_i, int[] H_i_1) {
        System.arraycopy(H_i, 0, this.H_i, 0, BLOCK_SIZE);
        System.arraycopy(H_i_1, 0, this.H_i_1, 0, BLOCK_SIZE);
        S_H_i_1 = toStr(H_i_1);
        compute();
    }

    private String toStr(int[] array) {
        StringBuilder result = new StringBuilder();
        for (int index = 0; index < BLOCK_SIZE; index++)
            result.append(array[index]).append(" ");
        return result.toString();
    }

    private void compute() {
        initA();
        computeFirstLineA();
        computeLowTriangleA();
        computeLastColumnA();
        for (int i = 0; i < 4; i++) {
            computeSecondLineA(i);
            processBandC();
        }
    }

    private void initA() {
        System.arraycopy(H_i, 0, A[0], 0, COLUMN_NUMBER);
        System.arraycopy(H_i_1, 0, A[LINE_NUMBER - 1], 0, COLUMN_NUMBER);
    }

    private void computeFirstLineA() {
        A[1][0] = fi(0, A[0][0]);
        for (int i = 1; i < COLUMN_NUMBER; i++) A[1][i] = fi(A[1][i - 1], A[0][i]);
    }

    private void computeSecondLineA(int i) {
        A[2][0] = fi((i + 1) % 4, A[1][0]);
        for (int j = 1; j < COLUMN_NUMBER; j++) A[2][j] = fi(A[2][j - 1], A[1][j]);
    }

    private void computeLowTriangleA() {
        for (int t = LINE_NUMBER - 1; t > 2; t--)
            for (int i = (LINE_NUMBER - t); i < COLUMN_NUMBER; i++)
                A[t - 1][i] = fi(A[t][i - 1], A[t][i]);
    }


    private void computeLastColumnA() {
        for (int i = 3; i < LINE_NUMBER - 1; i++)
            A[i][COLUMN_NUMBER - 1] = fi(A[i][COLUMN_NUMBER - 2], A[i - 1][COLUMN_NUMBER - 1]);
    }

    private void processBandC() {
        for (int i1 = 0; i1 < 4; i1++) {
            B[1][15] = i1;
            for (int i2 = 0; i2 < 4; i2++) {
                B[2][15] = i2;
                for (int i3 = 0; i3 < 4; i3++) {
                    B[3][15] = i3;
                    for (int i4 = 0; i4 < 4; i4++) {
                        B[4][15] = i4;
                        computeWithSomeBElement();
                        compute2WithSomeBElement();
                        createT();
                        T1.clear();
                        T2.clear();
                    }
                }
            }
        }
    }

    private void createT() {
        Collections.sort(T1);
        Collections.sort(T2);
        for (Block block : T1) {
            boolean flag = true;
            int j = 0;
            while (j < T2.size()) {
                addElem(block, T2.get(j));
                if (compare(block.getBytes(), (T2.get(j)).getBytes()) > 0) T2.remove(j);
                else if ((flag) && (compare(block.getBytes(), T2.get(j).getBytes()) == 0)) {
                    T2.remove(j);
                    flag = false;
                }
                j++;
            }
        }
    }

    private int compare(int[] a, int[] b) {
        for (int i = 0; i < 8; i++)
            if (a[i] != b[i]) return a[i] - b[i];
        return 0;
    }

    private void addElem(Block a, Block b) {
        if (a.compareTo(b) != 0) return;
        int[] elem = new int[16];
        System.arraycopy(a.getBytes(), 8, elem, 0, 8);
        System.arraycopy(b.getBytes(), 8, elem, 8, BLOCK_SIZE - 8);
        Block block = new Block(elem);
        if (!T.contains(block)) T.add(block);
    }

    private void computeWithSomeBElement() {
        int[] m = new int[8];
        for (int i1 = 0; i1 < 4; i1++) {
            m[0] = i1;
            for (int i2 = 0; i2 < 4; i2++) {
                m[1] = i2;
                for (int i3 = 0; i3 < 4; i3++) {
                    m[2] = i3;
                    for (int i4 = 0; i4 < 4; i4++) {
                        m[3] = i4;
                        for (int i5 = 0; i5 < 4; i5++) {
                            m[4] = i5;
                            for (int i6 = 0; i6 < 4; i6++) {
                                m[5] = i6;
                                for (int i7 = 0; i7 < 4; i7++) {
                                    m[6] = i7;
                                    for (int i8 = 0; i8 < 4; i8++) {
                                        m[7] = i8;
                                        computeBandC(m);
                                        createT1();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    private void computeBandC(int[] m) {
        computeB(m);
        computeC(m);
    }

    private void computeB(int[] m) {
        System.arraycopy(m, 0, B[0], 0, 8);
        for (int i = 1; i < 5; i++)
            B[i][0] = fi(A[i - 1][15] + i - 2, B[i - 1][0]);
        for (int t = 1; t < 5; t++)
            for (int i = 1; i < 8; i++)
                B[t][i] = fi(B[t][i - 1], B[t - 1][i]);
    }

    private void computeC(int[] m) {
        for (int i = 0; i < 8; i++) C[0][i] = m[i] ^ H_i[i];
        for (int i = 1; i < 5; i++)
            C[i][0] = fi(B[i - 1][15] + i - 2, C[i - 1][0]);
        for (int t = 1; t < 5; t++)
            for (int i = 1; i < 8; i++)
                C[t][i] = fi(C[t][i - 1], C[t - 1][i]);
    }

    private void createT1() {
        int[] element = new int[16];
        for (int i = 1; i < 5; i++) element[i - 1] = B[i][7];
        for (int i = 1; i < 5; i++) element[i + 3] = C[i][7];
        System.arraycopy(B[0], 0, element, 8, 8);
        T1.add(new Block(element));
    }

    private void compute2WithSomeBElement() {
        int[] m = new int[16];
        for (int i1 = 0; i1 < 4; i1++) {
            m[0] = i1;
            for (int i2 = 0; i2 < 4; i2++) {
                m[1] = i2;
                for (int i3 = 0; i3 < 4; i3++) {
                    m[2] = i3;
                    for (int i4 = 0; i4 < 4; i4++) {
                        m[3] = i4;
                        for (int i5 = 0; i5 < 4; i5++) {
                            m[4] = i5;
                            for (int i6 = 0; i6 < 4; i6++) {
                                m[5] = i6;
                                for (int i7 = 0; i7 < 4; i7++) {
                                    m[6] = i7;
                                    for (int i8 = 0; i8 < 4; i8++) {
                                        m[7] = i8;
                                        compute2BandC(m);
                                        createT2();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    private void compute2BandC(int[] m) {
        compute2B(m);
        compute2C(m);
    }

    private void compute2B(int[] m) {
        System.arraycopy(m, 0, B[0], 8, COLUMN_NUMBER - 8);
        for (int t = 1; t < 5; t++)
            for (int i = COLUMN_NUMBER - 1; i > 7; i--)
                B[t][i - 1] = fi_(B[t][i], B[t - 1][i]);
    }

    private void compute2C(int[] m) {
        for (int i = 8; i < COLUMN_NUMBER; i++) C[0][i] = m[i - 8] ^ H_i[i];
        System.arraycopy(H_i, 0, C[0], 0, 8);
        for (int i = 1; i < 5; i++)
            C[i][0] = fi(B[i - 1][15] + i - 2, C[i - 1][0]);
        for (int t = 1; t < 5; t++)
            for (int i = 1; i < 8; i++)
                C[t][i] = fi(C[t][i - 1], C[t - 1][i]);
    }

    private void createT2() {
        int[] element = new int[16];
        for (int i = 1; i < 5; i++) element[i - 1] = B[i][7];
        for (int i = 1; i < 5; i++) element[i + 3] = C[i][7];
        System.arraycopy(B[0], 0, element, 8, 8);
        T2.add(new Block(element));
    }

    private int fi(int a, int c) {
        while (a < 0) a += 4;
        while (c < 0) c += 4;
        return (Matrix.S(a % 4) ^ c) % 4;
    }

    private int fi_(int a, int c) {
        while (a < 0) a += 4;
        while (c < 0) c += 4;
        return Matrix.revS((a ^ c) % 4);
    }
}
