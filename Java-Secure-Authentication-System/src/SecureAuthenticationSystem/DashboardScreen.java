package SecureAuthenticationSystem;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class DashboardScreen extends JFrame
{
    private String username;

    public DashboardScreen(String username)
    {
        this.username = username;

        setTitle("Dashboard");
        setSize(400,250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JLabel welcomeLabel = new JLabel("Welcome " + username + "!", SwingConstants.CENTER);

        JButton changePasswordBtn = new JButton("Change Password");
        JButton logoutBtn = new JButton("Logout");

        setLayout(new BorderLayout(10,10));

        add(welcomeLabel, BorderLayout.NORTH);

        JPanel panel = new JPanel();
        panel.add(changePasswordBtn);
        panel.add(logoutBtn);

        add(panel, BorderLayout.CENTER);

        changePasswordBtn.addActionListener(e -> changePassword());
        logoutBtn.addActionListener(e -> {
            dispose();
            new StartScreen();
        });

        setVisible(true);
    }

    private void changePassword()
    {
        String newPassword = JOptionPane.showInputDialog("Enter New Password:");

        if (newPassword == null) return;

        List<String> errors = PasswordValidator.validate(newPassword);

        if (!errors.isEmpty())
        {
            JOptionPane.showMessageDialog(this,
                    String.join("\n", errors));
            return;
        }

        String hashed = PasswordHasher.hash(newPassword);
        AccountManager.changePassword(username, hashed);

        JOptionPane.showMessageDialog(this,
                "Password Changed Successfully!");
    }
}
