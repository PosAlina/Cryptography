package ArgumentHandler.Checkers;

import Exceptions.ArgumentException;

class BlockChecker {
    void isBlock(String block) throws ArgumentException {
        isCorrectBlockLength(block);
        for (int index = 0; index < block.length() - 1; index += 2) {
            isDigit(block.charAt(index));
            isSpace(block.charAt(index + 1));
        }
        isDigit(block.charAt(block.length() - 1));
    }

    void isLastBlock(String block) throws ArgumentException {
        isCorrectLastBlockLength(block);
        for (int index = 0; index < block.length() - 1; index += 2) {
            isDigit(block.charAt(index));
            isSpace(block.charAt(index + 1));
        }
        isDigit(block.charAt(block.length() - 1));
    }

    private void isCorrectBlockLength(String block) throws ArgumentException {
        if (block.length() != 31) {
            throw new ArgumentException("Please restart the program by specifying one of three modes\n" +
                    "and two arguments consisting of numbers and spaces, surrounding paranthesis\n");
        }
    }

    private void isCorrectLastBlockLength(String block) throws ArgumentException {
        if (block.length() > 31) {
            throw new ArgumentException("Please restart the program by specifying one of three modes\n" +
                    "and two arguments consisting of numbers and spaces, surrounding paranthesis\n");
        }
    }

    private void isDigit(char digit) throws ArgumentException {
        if ((digit != '0') && (digit != '1') && (digit != '2') && (digit != '3')) {
            throw new ArgumentException("Please restart the program by specifying one of three modes\n" +
                    "and two arguments consisting of numbers and spaces, surrounding paranthesis\n");
        }
    }

    private void isSpace(char digit) throws ArgumentException {
        if (digit != ' ') {
            throw new ArgumentException("Please restart the program by specifying one of three modes\n" +
                    "and two arguments consisting of numbers and spaces, surrounding paranthesis\n");
        }
    }
}
