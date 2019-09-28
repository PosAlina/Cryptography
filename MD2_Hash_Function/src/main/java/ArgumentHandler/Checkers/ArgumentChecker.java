package ArgumentHandler.Checkers;

import ArgumentHandler.ArgumentStorage;
import Exceptions.ArgumentException;

public class ArgumentChecker {
    private SyntaxChecker syntaxChecker;
    private NumberChecker numberChecker;

    public ArgumentChecker(ArgumentStorage argumentStorage) {
        this.syntaxChecker = new SyntaxChecker(argumentStorage);
        this.numberChecker = new NumberChecker(argumentStorage);
    }

    public void checkArguments() throws ArgumentException {
        numberChecker.check();
        syntaxChecker.check();
    }
}
