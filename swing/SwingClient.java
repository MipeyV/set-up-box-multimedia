package swing;

public class SwingClient {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new PrincipalWindow();
            }
        });
    }
}