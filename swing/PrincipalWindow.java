package swing;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JPanel;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JToolBar;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;


/** 
 * The main window of the application.
 */
public class PrincipalWindow extends JFrame {

    private static final long serialVersionUID = 1L;
    
    private JTextArea textArea;
    private JButton button1;
    private JButton button2;
    private JButton quitButton;
    private Action button1Action;
    private Action button2Action;
    private Action quitButtonAction;
    private JTextField nameField;
    private Client client;
    
    /**
     * Constructor for PrincipalWindow.
     */
    public PrincipalWindow() {
        super("Principal Window");
        setTitle("Principal Window");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.textArea = new JTextArea("Welcome to the application!");
        this.nameField = new JTextField(15);

        try {
            this.client = new Client(Client.DEFAULT_HOST, Client.DEFAULT_PORT);
        } catch (Exception e) {
            this.client = null;
            textArea.append("\nConnection error: " + e.getMessage());
        }

        this.button1Action = new AbstractAction("Search") {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = nameField.getText().trim();
                if (name.isEmpty()) {
                    JOptionPane.showMessageDialog(PrincipalWindow.this, "Enter a name to search.");
                    return;
                }
                sendRequestAsync("search " + name);
            }
        };
        this.button2Action = new AbstractAction("Play") {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = nameField.getText().trim();
                if (name.isEmpty()) {
                    JOptionPane.showMessageDialog(PrincipalWindow.this, "Enter a name to play.");
                    return;
                }
                sendRequestAsync("play " + name);
            }
        };
        this.quitButtonAction = new AbstractAction("Quit") {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        };

        this.button1 = new JButton(button1Action);
        this.button2 = new JButton(button2Action);
        this.quitButton = new JButton(quitButtonAction);

        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Actions");
        menu.add(new JMenuItem(button1Action));
        menu.add(new JMenuItem(button2Action));
        menu.add(new JMenuItem(quitButtonAction));
        menuBar.add(menu);
        setJMenuBar(menuBar);

        setLayout(new BorderLayout());

        JToolBar toolBar = new JToolBar();
        toolBar.add(new JLabel("Name: "));
        toolBar.add(nameField);
        toolBar.add(button1Action);
        toolBar.add(button2Action);
        toolBar.add(quitButtonAction);
        add(toolBar, BorderLayout.NORTH);

        add(new JScrollPane(textArea), BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        buttonPanel.add(button1);
        buttonPanel.add(button2);
        buttonPanel.add(quitButton);
        add(buttonPanel, BorderLayout.SOUTH);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }   

    private void sendRequestAsync(String request) {
        if (client == null) {
            textArea.append("\nClient not connected.");
            return;
        }
        new Thread(() -> {
            String response = client.send(request);
            if (response == null) {
                response = "No response from server.";
            }
            final String resp = response;
            SwingUtilities.invokeLater(() -> textArea.append("\n" + resp));
        }).start();
    }

}
