package ArgumentHandler;

import AdditionalClasses.Modes;

public class ArgumentStorage {
    private String[] args;
    private Modes mode = Modes.UNKNOWN_MODE;
    private String[] parameters = null;

    ArgumentStorage(String[] args) {
        this.args = new String[args.length];
        System.arraycopy(args, 0, this.args, 0, args.length);
    }

    public void setArguments() {
        setMode();
        setParameters();
    }

    private void setMode() {
        switch (args[0]) {
            case "md2": {
                this.mode = Modes.MD2;
                break;
            }
            case "compress": {
                this.mode = Modes.COMPRESS;
                break;
            }
            case "preimage": {
                this.mode = Modes.PREIMAGE;
                break;
            }
            default:
                this.mode = Modes.UNKNOWN_MODE;
        }
    }

    private void setParameters() {
        this.parameters = new String[args.length - 1];
        System.arraycopy(args, 1, this.parameters, 0, args.length - 1);
    }

    public String[] getArgs() {
        return args;
    }

    public Modes getMode() {
        return mode;
    }

    public String[] getParameters() {
        return parameters;
    }
}
