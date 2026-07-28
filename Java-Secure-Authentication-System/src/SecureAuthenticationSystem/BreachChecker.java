package SecureAuthenticationSystem;

import java.io.File;
import java.util.Scanner;

public class BreachChecker
{
    private static final String FILE_NAME = "src/SecureAuthenticationSystem/breached_passwords.txt";

    public static boolean isBreached(String password)
    {
        String hashedInput = PasswordHasher.hash(password);

        try (Scanner scanner = new Scanner(new File(FILE_NAME)))
        {
            while (scanner.hasNextLine())
            {
                String breachedPassword = scanner.nextLine().trim();
                String breachedHash = PasswordHasher.hash(breachedPassword);

                if (hashedInput.equals(breachedHash))
                {
                    return true;
                }
            }

        }
        catch (Exception e)
        {
            System.out.println("Breach file not found.");
        }

        return false;
    }
}
