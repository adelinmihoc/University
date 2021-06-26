package ro.ubb.coffeeshop.exceptions;

public class InternalErrorException extends RuntimeException{
    public InternalErrorException() {
        super();
    }

    public InternalErrorException(String message) {
        super(message);
    }
}
