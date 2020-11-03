import ArgumentHandler.ArgumentHandler;
import Computator.Computator;
import AdditionalClasses.Printer;
import Exceptions.CommonException;

public class Main {
    public static void main(String[] args) {
        try {
            ArgumentHandler argumentHandler = new ArgumentHandler(args);
            argumentHandler.process();
            Computator computator = new Computator(argumentHandler.getArgumentStorage());
            computator.compute();
            computator.printResult();
        } catch (CommonException exception) {
            exception.printMessage();
        } catch (Exception exception) {
            Printer.print(exception.getMessage());
        }
    }
}
