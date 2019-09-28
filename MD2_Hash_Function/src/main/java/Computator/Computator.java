package Computator;

import AdditionalClasses.Printer;
import ArgumentHandler.ArgumentStorage;
import AdditionalClasses.Modes;
import Computator.Compressor.Compressor;
import Computator.Md2Handler.Md2Handler;
import Computator.Preimager.Preimager;
import Exceptions.ArgumentException;
import Exceptions.CommonException;

public class Computator {
    private HandlerImpl handler;
    private String result;

    public Computator(ArgumentStorage argumentStorage) throws CommonException {
        setHandler(argumentStorage.getMode(), argumentStorage.getParameters());
    }

    public void compute() {
        result = handler.compute();
    }

    public void printResult() {
        Printer.print(result);
    }

    private void setHandler(Modes mode, String[] parameters) throws CommonException {
        try {
        switch (mode) {
            case MD2:
                handler = new Md2Handler(parameters);
                break;
            case COMPRESS:
                handler = new Compressor(parameters);
                break;
            case PREIMAGE:
                handler = new Preimager(parameters);
                break;
            case UNKNOWN_MODE:
            default:
                throw new ArgumentException("Unknown program mode");
        }
        } catch (ArgumentException exception) {
            throw new CommonException(exception.getMessage());
        }
    }
}
