import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Font;
import java.awt.Color;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ExemploFonte extends Frame {

    public ExemploFonte() {
        // Configurações básicas da janela (Frame do AWT)
        setTitle("Exemplo de Fonte em Java AWT");
        setSize(500, 300);
        setVisible(true);

        // Código para fechar a janela corretamente ao clicar no "X"
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we) {
                System.exit(0);
            }
        });
    }

    public void paint(Graphics g) {
        super.paint(g);

        // 1. Criando uma fonte comum (Nome, Estilo, Tamanho)
        // Opções comuns de fontes lógicas: "Arial", "Serif", "SansSerif", "Monospaced"
        Font minhaFonte = new Font("Arial", Font.BOLD, 24);

        // 2. Aplicando a fonte e uma cor ao contexto gráfico
        g.setFont(minhaFonte);
        g.setColor(Color.BLUE);

        // 3. Desenhando o texto na tela (Texto, Posição X, Posição Y)
        g.drawString("Olá, Java AWT!", 50, 150);

        // Exemplo com outra fonte comum e nativa do Java
        Font outraFonte = new Font("Monospaced", Font.ITALIC, 16);
        g.setFont(outraFonte);
        g.setColor(Color.DARK_GRAY);
        g.drawString("Texto com fonte Monospaced e Itálico.", 50, 200);
    }

    public static void main(String[] args) {
        new ExemploFonte();
    }
}