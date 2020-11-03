package Exceptions;

import AdditionalClasses.Printer;

public class CommonException extends Exception {
    private String message;

    public CommonException(String message) {
        super(message);
        this.message = message;
    }

    public String getMessage() {
        return message;
    }

    public void printMessage() {
        Printer.print(message);
    }
}
