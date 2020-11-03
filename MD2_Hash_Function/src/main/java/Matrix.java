package AdditionalClasses;

import java.util.Arrays;

public class Matrix {
    // Matrix for Md2
    private static int[] PI_SUBST = {1, 3, 0, 2};
    private static int[] REV_PI_SUBST = {2, 0, 3, 1};

    public static int S(int i) {
        return PI_SUBST[i % 4];
    }

    public static int revS(int i) {
        return REV_PI_SUBST[i % 4];
    }

    public static void print(int[][] matrix) {
        for (int[] ints : matrix)
            Printer.print(Arrays.toString(ints));
    }
}
