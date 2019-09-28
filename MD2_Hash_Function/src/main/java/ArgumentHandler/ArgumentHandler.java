package ArgumentHandler;

import ArgumentHandler.Checkers.ArgumentChecker;
import Exceptions.ArgumentException;
import Exceptions.CommonException;

public class ArgumentHandler {
    private ArgumentChecker argumentChecker;
    private ArgumentStorage argumentStorage;

    public ArgumentHandler(String[] args) {
        argumentStorage = new ArgumentStorage(args);
        argumentChecker = new ArgumentChecker(argumentStorage);
    }

    public void process() throws CommonException {
        try {
            argumentChecker.checkArguments();
            argumentStorage.setArguments();
        } catch (ArgumentException exception) {
            throw new CommonException(exception.getMessage());
        }
    }

    public ArgumentStorage getArgumentStorage() {
        return argumentStorage;
    }
}
