package SecureAuthenticationSystem;

import javax.swing.*;
import java.awt.*;

public class LoginScreen extends JFrame
{
    JTextField usernameField;
    JPasswordField passwordField;
    JLabel messageLabel;

    public LoginScreen()
    {
        setTitle("Login");
        setSize(350,250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        setLayout(new BorderLayout(10,10));

        JPanel panel = new JPanel(new GridLayout(4,2,10,10));
        panel.setBorder(BorderFactory.createEmptyBorder(20,20,20,20));

        usernameField = new JTextField();
        passwordField = new JPasswordField();

        JButton eyeButton = new JButton("👁");

        eyeButton.addActionListener(e -> {
            if (passwordField.getEchoChar() == '\u0000') {
                passwordField.setEchoChar('•');
            } else {
                passwordField.setEchoChar((char) 0);
            }
        });

        JPanel passwordPanel = new JPanel(new BorderLayout());
        passwordPanel.add(passwordField, BorderLayout.CENTER);
        passwordPanel.add(eyeButton, BorderLayout.EAST);

        JButton loginBtn = new JButton("Login");

        messageLabel = new JLabel("");
        messageLabel.setForeground(Color.RED);

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordPanel);
        panel.add(new JLabel(""));
        panel.add(loginBtn);
        panel.add(new JLabel(""));
        panel.add(messageLabel);

        add(panel, BorderLayout.CENTER);

        loginBtn.addActionListener(e -> login());

        setVisible(true);
    }

    private void login()
    {
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());
        String hashed = PasswordHasher.hash(password);

        if (AccountManager.authenticate(username, hashed))
        {
            dispose();
            new DashboardScreen(username);
        }
        else
        {
            messageLabel.setText("Invalid Credentials!");
        }
    }
}
