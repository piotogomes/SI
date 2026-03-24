public class Main {
  public static void main(String[] args) {
    Complex a = new EComplex(4, 3);
    Complex b = new EComplex(2, 5);
    System.out.println(a.times(b).realPart());
  
  }
}
