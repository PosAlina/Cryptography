package ArgumentHandler.Checkers;

import ArgumentHandler.ArgumentStorage;
import AdditionalClasses.Modes;
import Exceptions.ArgumentException;

public class NumberChecker implements Checker {
    private ArgumentStorage argumentStorage;

    NumberChecker(ArgumentStorage argumentStorage) {
        this.argumentStorage = argumentStorage;
    }

    @Override
    public void check() throws ArgumentException {
        if (argumentStorage.getArgs().length == 0) {
            throw new ArgumentException("Please restart the program by specifying one of three modes:\n" +
                    "md2 - the calculation of the md2 to a given series of 16 - byte blocks\n" +
                    "compress - the computation of the compression function for a given Hi and the message block Mi\n" +
                    "preimage - the calculation type for the specified units Hi and Hi + 1\n");
        }
        argumentStorage.setArguments();
        if ((!Modes.isMd2(argumentStorage.getMode())) && (argumentStorage.getParameters().length != 2)) {
            throw new ArgumentException("Please restart the program in this mode with two 16-byte blocks in parentheses \"\", consisting of space and digits\n");
        }
    }
}
