package Computator;

import AdditionalClasses.Printer;

import java.util.Arrays;

public abstract class HandlerImpl {
    protected int BLOCK_SIZE = 16;

    public abstract String compute();

    protected String getResult(int[] array) {
        StringBuilder result = new StringBuilder();
        for (int index = 0; index < BLOCK_SIZE; index++)
            result.append(array[index]).append(" ");
        return result.toString();
    }
}
