package ArgumentHandler.Checkers;

import ArgumentHandler.ArgumentStorage;
import AdditionalClasses.Modes;
import Exceptions.ArgumentException;

public class SyntaxChecker implements Checker {
    private ArgumentStorage argumentStorage;
    private BlockChecker blockChecker = new BlockChecker();

    SyntaxChecker(ArgumentStorage argumentStorage) {
        this.argumentStorage = argumentStorage;
    }

    @Override
    public void check() throws ArgumentException {
        checkModeSyntax();
        checkParametersSyntax();
    }

    private void checkModeSyntax() throws ArgumentException {
        if (Modes.isUnknownMode(argumentStorage.getMode())) {
            throw new ArgumentException("Please restart the program by specifying one of three modes:\n" +
                    "md2 - the calculation of the md2 to a given series of 16 - byte blocks\n" +
                    "compress - the computation of the compression function for a given Hi and the message block Mi\n" +
                    "preimage - the calculation type for the specified units Hi and Hi + 1\n");
        }
    }

    private void checkParametersSyntax() throws ArgumentException {
        String[] parameters = argumentStorage.getParameters();
        for (int index = 0; index < parameters.length - 1; index++)
            blockChecker.isBlock(parameters[index]);
        if (Modes.isMd2(argumentStorage.getMode())) blockChecker.isLastBlock(parameters[parameters.length - 1]);
        else blockChecker.isBlock(parameters[parameters.length - 1]);
    }
}
