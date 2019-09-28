package Computator.Md2Handler;

import Computator.HandlerImpl;

public class Md2Handler extends HandlerImpl {
    private  String[] message;
    private int[] M;

    public Md2Handler(String... message) {
        this.M = new int[message[message.length - 1].length() != (BLOCK_SIZE * 2 - 1) ?
                (message.length + 1) * BLOCK_SIZE :
                (message.length + 2) * BLOCK_SIZE];
        this.message = message;
    }

    @Override
    public String compute() {
        setParameters(message);
        int length = applyPaddingRule(BLOCK_SIZE - (message[message.length - 1].length() + 1) / 2,
                (message.length - 1) * BLOCK_SIZE + (message[message.length - 1].length() - 1) / 2);
        appendChecksum();
        return processMessage();
    }

    private void setParameters(String... message) {
        for (int paramIndex = 0; paramIndex < message.length; paramIndex++)
            for (int index = 0; index < (message[paramIndex].length() - 1) / 2; index++)
                this.M[paramIndex * BLOCK_SIZE + index] = Integer.parseInt(String.valueOf(message[paramIndex].charAt(index * 2)));
    }

    private int applyPaddingRule(int i, int length) {
        if (i == 0) {
            for (int index = length; index < length + BLOCK_SIZE; index++) M[index] = 0;
            return length + BLOCK_SIZE;
        }
        for (int index = length; index < length + i; index++) M[index] = i % 4;
        return length + i;
    }

    private void appendChecksum() {
        Checksum checksum = new Checksum(M);
        M = checksum.append();
    }

    private String processMessage() {
        MdBuffer mdBuffer = new MdBuffer(M);
        return getResult(mdBuffer.append());
    }
}
