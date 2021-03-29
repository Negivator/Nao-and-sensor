package model;

public class Output<T> {
    private int code=500;
    private T result;

    public void setResult(T result) {
        this.result = result;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public int getCode() {
        return code;
    }

    public T getResult() {
        return result;
    }
}
