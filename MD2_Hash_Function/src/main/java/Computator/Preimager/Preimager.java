package Computator.Preimager;

import AdditionalClasses.Matrix;
import AdditionalClasses.Printer;
import Computator.HandlerImpl;

import java.util.Arrays;
import java.util.Collection;

public class Preimager extends HandlerImpl {
    private int[] H_i = new int[BLOCK_SIZE];
    private int[] H_i_1 = new int[BLOCK_SIZE];
    private MatrixActions matrix = new MatrixActions();

    public Preimager(String[] parameters) {
        setParameters(parameters);
    }

    @Override
    public String compute() {
        matrix.attack(H_i, H_i_1);
        Collection<int[]> messages = matrix.getM();
        StringBuilder result = new StringBuilder();
        for (int[] m : messages) result.append(getResult(m));
        return result.toString();
    }

    private void setParameters(String[] parameters) {
        for (int index = 0; index < (parameters[0].length() + 1) / 2; index++)
            this.H_i[index] = Integer.parseInt(String.valueOf(parameters[0].charAt(index * 2)));
        for (int index = 0; index < (parameters[1].length() + 1) / 2; index++)
            this.H_i_1[index] = Integer.parseInt(String.valueOf(parameters[1].charAt(index * 2)));
    }
}
