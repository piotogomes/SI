import java.nio.MappedByteBuffer;
import java.util.List;

public class tests {
    public static void main() {
        Base a = new Derivada();
        a.executar();
        System.out.println(a.getClass().getConstructors());
        MappedByteBuffer
    }

}

class Base {
    public void teste() {
        System.out.println("Base");
    }

    public void executar() {
        teste();
    }
}

class Derivada extends Base {
    public void teste() {
        System.out.println("Derivada");
    }
}
