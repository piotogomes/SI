package OAC1;

public class mdc {
    
    public static int acharMdc(int a, int b) {
        if(b == 0) {
            return a;
        }
        else {
            return acharMdc(b, a % b);
        }
    }

    public static void main(String[] args) {
        int cu = acharMdc(0, 18);
        System.out.println(Math.abs(cu));
    }

}
