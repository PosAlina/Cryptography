package AdditionalClasses;

public enum Modes {
    MD2,
    COMPRESS,
    PREIMAGE,
    UNKNOWN_MODE;

    public static boolean isCorrectMode(Modes mode) {
        return isMd2(mode) || isCompress(mode) || isPreimage(mode);
    }

    public static boolean isMd2(Modes mode) {
        return MD2.equals(mode);
    }

    public static boolean isCompress(Modes mode) {
        return COMPRESS.equals(mode);
    }

    public static boolean isPreimage(Modes mode) {
        return PREIMAGE.equals(mode);
    }

    public static boolean isUnknownMode(Modes mode) {
        return !(isCorrectMode(mode));
    }
}
