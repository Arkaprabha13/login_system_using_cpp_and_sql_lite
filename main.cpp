#include <bits/stdc++.h>
using namespace std;

// Function to check if the username meets the specified format
bool is_valid_username(const string& username) {
    if (username.length() < 5 || username.length() > 15) {
        cout << "Username must be between 5 and 15 characters long." << endl;
        return false;
    }

    // Username must start with a letter
    if (!isalpha(username[0])) {
        cout << "Username must start with a letter." << endl;
        return false;
    }

    // Username can only contain letters, digits, underscores, or periods
    for (char c : username) {
        if (!(isalnum(c) || c == '_' || c == '.')) {
            cout << "Username can only contain letters, digits, underscores, or periods." << endl;
            return false;
        }
    }

    return true;
}

// Function to check if the password meets the required format
bool is_valid_password(const string& password) {
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long." << endl;
        return false;
    }

    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;
    for (char c : password) {
        if (isupper(c)) has_upper = true;
        else if (islower(c)) has_lower = true;
        else if (isdigit(c)) has_digit = true;
        else if (ispunct(c)) has_special = true;  // Checks for special characters
    }

    if (!has_upper) {
        cout << "Password must contain at least one uppercase letter." << endl;
        return false;
    }
    if (!has_lower) {
        cout << "Password must contain at least one lowercase letter." << endl;
        return false;
    }
    if (!has_digit) {
        cout << "Password must contain at least one digit." << endl;
        return false;
    }
    if (!has_special) {
        cout << "Password must contain at least one special character (!@#$%^&*())." << endl;
        return false;
    }

    return true;
}

class User {
public:
    string username;
    string password;
    string email;
    string phone;
    string address;
    string role;

    User(string username, string password, string email, string phone, string address, string role) {
        this->username = username;
        this->password = password;
        this->email = email;
        this->phone = phone;
        this->address = address;
        this->role = role;
    }

    void display() const {
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "Role: " << role << endl;
    }
};

// Custom Database Class
class Database {
private:
    vector<User> users;

public:
    // Find user by username
    User* find_user_by_username(const string& username) {
        for (auto& user : users) {
            if (user.username == username) {
                return &user;
            }
        }
        return nullptr;
    }

    // Add a new user
    bool add_user(const User& user) {
        if (find_user_by_username(user.username) != nullptr) {
            cout << "User already exists with username: " << user.username << endl;
            return false;
        }
        users.push_back(user);
        return true;
    }

    // Update user
    bool update_user(const string& username, const User& updated_user) {
        User* user = find_user_by_username(username);
        if (user == nullptr) {
            cout << "User not found with username: " << username << endl;
            return false;
        }
        *user = updated_user;
        return true;
    }

    // Delete user
    bool delete_user(const string& username) {
        auto it = find_if(users.begin(), users.end(), [&username](const User& user) {
            return user.username == username;
        });

        if (it != users.end()) {
            users.erase(it);  // Remove user from vector
            return true;
        }
        cout << "User not found!" << endl;
        return false;
    }

    // Display all users
    void display_all_users() const {
        if (users.empty()) {
            cout << "No users found." << endl;
            return;
        }

        for (const auto& user : users) {
            user.display();
            cout << "----------------------" << endl;
        }
    }
};

// Login system
void login_system(Database& db) {
    int choice;
    do {
        cout << "\n1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Update" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Display all users" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string username, password, email, phone, address, role;

        switch (choice) {
        case 1:
            // Register a new user
            cout << "Enter username: ";
            cin >> username;

            if (!is_valid_username(username)) {
                break;  // If the username is invalid, break out of the case
            }

            cout << "Enter password: ";
            cin >> password;

            if (!is_valid_password(password)) {
                break;  // If the password is invalid, break out of the case
            }

            cout << "Enter email: ";
            cin >> email;
            cout << "Enter phone: ";
            cin >> phone;
            cout << "Enter address: ";
            cin >> address;
            cout << "Enter role: ";
            cin >> role;

            db.add_user(User(username, password, email, phone, address, role));
            break;

        case 2: {
            // Login a user
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            User* user = db.find_user_by_username(username);
            if (user && user->password == password) {
                cout << "Login successful! Welcome, " << user->username << endl;
                user->display();
            } else {
                cout << "Invalid username or password." << endl;
            }
            break;
        }

        case 3: {
            // Update user
            cout << "Enter username of the user to update: ";
            cin >> username;

            User* user = db.find_user_by_username(username);
            if (user) {
                cout << "Enter new password: "; cin >> password;
                if (!is_valid_password(password)) {
                    break;  // If the password is invalid, break out of the case
                }

                cout << "Enter new email: "; cin >> email;
                cout << "Enter new phone: "; cin >> phone;
                cout << "Enter new address: "; cin >> address;
                cout << "Enter new role: "; cin >> role;

                User updated_user(username, password, email, phone, address, role);
                db.update_user(username, updated_user);
                cout << "User updated successfully!" << endl;
            } else {
                cout << "User not found!" << endl;
            }
            break;
        }

        case 4:
            // Delete a user
            cout << "Enter the username to delete: ";
            cin >> username;
            db.delete_user(username);
            break;

        case 5:
            // Display all users
            db.display_all_users();
            break;

        case 6:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

int main() {
    Database db;
    login_system(db);
    return 0;
}
