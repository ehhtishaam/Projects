package SecureAuthenticationSystem;

import javax.swing.*;
import java.awt.*;

public class StartScreen extends JFrame
{
    public StartScreen()
    {
        setTitle("Authentication System");
        setSize(350,200);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JButton loginBtn = new JButton("Login");
        JButton registerBtn = new JButton("Register");

        setLayout(new GridLayout(2,1,10,10));
        add(loginBtn);
        add(registerBtn);

        loginBtn.addActionListener(e -> {
            dispose();
            new LoginScreen();
        });

        registerBtn.addActionListener(e -> {
            dispose();
            new RegisterScreen();
        });

        setVisible(true);
    }
}
