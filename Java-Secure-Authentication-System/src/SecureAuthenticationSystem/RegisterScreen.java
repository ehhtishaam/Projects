package SecureAuthenticationSystem;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class RegisterScreen extends JFrame
{
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JLabel strengthLabel;

    public RegisterScreen()
    {
        setTitle("Create Account");
        setSize(400,250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        initializeUI();
        setVisible(true);
    }

    private void initializeUI()
    {
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

        passwordField.getDocument().addDocumentListener(new javax.swing.event.DocumentListener() {

            public void insertUpdate(javax.swing.event.DocumentEvent e) {
                checkStrength();
            }

            public void removeUpdate(javax.swing.event.DocumentEvent e) {
                checkStrength();
            }

            public void changedUpdate(javax.swing.event.DocumentEvent e) {
                checkStrength();
            }

            private void checkStrength() {
                String password = new String(passwordField.getPassword());

                int score = 0;

                // Length minimum check
                if (password.length() >= 6) score++;

                if (password.matches(".*[A-Z].*")) score++;
                if (password.matches(".*[a-z].*")) score++;
                if (password.matches(".*\\d.*")) score++;
                if (password.matches(".*[^a-zA-Z0-9].*")) score++;

                // If length < 6, always Weak
                if(password.length() < 6) {
                    strengthLabel.setText("Weak");
                    strengthLabel.setForeground(Color.RED);
                    return;
                }

                // Normal scoring classification
                if (score <= 2) {
                    strengthLabel.setText("Weak");
                    strengthLabel.setForeground(Color.RED);
                } else if (score == 3 || score == 4) {
                    strengthLabel.setText("Fair");
                    strengthLabel.setForeground(Color.ORANGE);
                } else {
                    strengthLabel.setText("Strong");
                    strengthLabel.setForeground(new Color(0, 128, 0));
                }
            }
        });

        JPanel passwordPanel = new JPanel(new BorderLayout());
        passwordPanel.add(passwordField, BorderLayout.CENTER);
        passwordPanel.add(eyeButton, BorderLayout.EAST);

        strengthLabel = new JLabel(" ");
        strengthLabel.setFont(new Font("Arial", Font.BOLD, 12));

        JButton registerBtn = new JButton("Register");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordPanel);
        panel.add(new JLabel(" "));
        panel.add(strengthLabel);
        panel.add(new JLabel(""));
        panel.add(registerBtn);

        add(panel);

        registerBtn.addActionListener(e -> register());
    }

    private void register()
    {
        String username = usernameField.getText().trim();
        String password = new String(passwordField.getPassword());

        if (username.isEmpty())
        {
            showError("Username cannot be empty.");
            return;
        }

        if (AccountManager.usernameExists(username))
        {
            showError("Username already taken.");
            return;
        }

        // BREACH CHECK
        if (BreachChecker.isBreached(password))
        {
            JOptionPane.showMessageDialog(this,
                    "This password has appeared in data breaches.\nChoose a different password.",
                    "Registration Error",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }

        // PASSWORD RULES CHECK ONLY IF NOT BREACHED
        List<String> errors = PasswordValidator.validate(password);
        if (!errors.isEmpty())
        {
            JOptionPane.showMessageDialog(this,
                    String.join("\n", errors),
                    "Registration Error",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }

        // ALL GOOD
        String hashed = PasswordHasher.hash(password);
        AccountManager.saveAccount(username, hashed);

        JOptionPane.showMessageDialog(this,
                "Registered Successfully!");

        dispose();
        new StartScreen();
    }

    private void showError(String message)
    {
        JOptionPane.showMessageDialog(this,
                message,
                "Registration Error",
                JOptionPane.ERROR_MESSAGE);
    }
}
