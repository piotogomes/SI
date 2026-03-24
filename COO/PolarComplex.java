public class PolarComplex implements Complex {
    final double r;
    final double theta;

    public PolarComplex(double rad, double ang) {
        this.r = rad;
        this.theta = ang;
    }

    public double realPart() { return r*Math.cos(theta);}
    public double imagPart() { return r*Math.sin(theta);}

    public Complex plus(Complex b) {
        //impementar
        return b;

    }
    public Complex times(Complex b) {
        //impementar
        return b;
    }
}
