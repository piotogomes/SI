public class EComplex implements Complex {
    private final double re;
    private final double im;

    public EComplex(double real, double imag) {
        re = real;
        im = imag;
    }

    public double realPart() { return re;}
    public double imagPart() { return im;}

    public Complex plus(Complex b) {
        EComplex a = this;
        double real = a.re + b.realPart();
        double imag = a.im + b.imagPart();
        return new EComplex(real, imag);

    }
    public Complex times(Complex b) {
        EComplex a = this;
        double real = a.re * b.realPart() - a.im * b.imagPart();
        double imag = a.re * b.realPart() + a.im * b.imagPart();
        return new EComplex(real, imag);
    }
}
