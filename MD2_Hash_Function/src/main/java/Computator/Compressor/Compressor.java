package Computator.Compressor;

import Computator.HandlerImpl;

public class Compressor extends HandlerImpl {
    private int[] H_i = new int[BLOCK_SIZE];
    private int[] M_i = new int[BLOCK_SIZE];

    public Compressor(String[] parameters) {
        setParameters(parameters);
    }

    public Compressor(int[] h, int[] m) {
        setParameters(h, m);
    }

    @Override
    public String compute() {
        return getResult(F());
    }

    private void setParameters(String[] parameters) {
        for (int index = 0; index < (parameters[0].length() - 1) / 2; index++)
            this.H_i[index] = Integer.parseInt(String.valueOf(parameters[0].charAt(index * 2)));
        for (int index = 0; index < (parameters[1].length() - 1) / 2; index++)
            this.M_i[index] = Integer.parseInt(String.valueOf(parameters[1].charAt(index * 2)));
    }

    private void setParameters(int[] h, int[] m) {
        System.arraycopy(h, 0, this.H_i, 0, BLOCK_SIZE);
        System.arraycopy(m, 0, this.M_i, 0, BLOCK_SIZE);
    }

    private int[] F() {
        MdBuffer mdBuffer = new MdBuffer(H_i, M_i);
        return mdBuffer.append();
    }
}
