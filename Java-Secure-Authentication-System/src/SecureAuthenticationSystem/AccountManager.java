package SecureAuthenticationSystem;

import java.io.*;
import java.util.*;

public class AccountManager
{
    private static final String FILE_NAME = "accounts.txt";

    public static boolean usernameExists(String username)
    {
        try (Scanner scanner = new Scanner(new File(FILE_NAME)))
        {
            while (scanner.hasNextLine())
            {
                String[] parts = scanner.nextLine().split(",");
                if (parts[0].equals(username))
                    return true;
            }
        }
        catch (Exception ignored) {}
        return false;
    }

    public static void saveAccount(String username, String hashedPassword)
    {
        try (FileWriter fw = new FileWriter(FILE_NAME, true);
             BufferedWriter bw = new BufferedWriter(fw))
        {
            bw.write(username + "," + hashedPassword);
            bw.newLine();
        }
        catch (IOException e)
        {
            System.out.println("Error saving account.");
        }
    }

    public static boolean authenticate(String username, String hashedPassword)
    {
        try (Scanner scanner = new Scanner(new File(FILE_NAME)))
        {
            while (scanner.hasNextLine())
            {
                String[] parts = scanner.nextLine().split(",");
                if (parts[0].equals(username) && parts[1].equals(hashedPassword))
                    return true;
            }
        }
        catch (Exception ignored) {}
        return false;
    }

    public static void changePassword(String username, String newHashedPassword)
    {
        File file = new File(FILE_NAME);
        List<String> lines = new ArrayList<>();

        try (Scanner scanner = new Scanner(file))
        {
            while (scanner.hasNextLine())
            {
                String line = scanner.nextLine();
                String[] parts = line.split(",");

                if (parts[0].equals(username))
                    lines.add(username + "," + newHashedPassword);
                else
                    lines.add(line);
            }

        }
        catch (Exception ignored) {}

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file)))
        {
            for (String l : lines)
            {
                writer.write(l);
                writer.newLine();
            }
        }
        catch (IOException e)
        {
            System.out.println("Error updating password.");
        }
    }
}
