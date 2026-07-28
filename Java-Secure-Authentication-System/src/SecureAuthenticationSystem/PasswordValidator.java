package SecureAuthenticationSystem;

import java.util.ArrayList;
import java.util.List;

public class PasswordValidator
{
    public static List<String> validate(String password)
    {
        List<String> errors = new ArrayList<>();

        if (password.length() < 6)
            errors.add("Password must be at least 6 characters.");

        if (password.length() > 64)
            errors.add("Password must not exceed 64 characters.");

        if (!password.matches(".*[A-Z].*"))
            errors.add("Add at least one uppercase letter.");

        if (!password.matches(".*[a-z].*"))
            errors.add("Add at least one lowercase letter.");

        if (!password.matches(".*[0-9].*"))
            errors.add("Add at least one number.");

        if (!password.matches(".*[!@#$%^&*()].*"))
            errors.add("Add at least one special character.");

        return errors;
    }
}
