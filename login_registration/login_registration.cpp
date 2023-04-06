#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> // For std::system()

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

void clear()
{
    system(CLEAR);
}

void delay(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

class User
{
private:
    std::string login;
    std::string psswrd;
    float money;
    static std::vector<User> storage;

    // public functions
public:
    // check if the input exist in the database
    static bool verifyLogin(std::string login)
    {
        for (int i = 0; i < storage.size(); i++)
        {
            if (storage[i].login == login)
                return true;
        }
        return false;
    }

    // adds new user to the database
    void registration(std::string login, std::string psswrd)
    {
        this->login = login;
        this->psswrd = psswrd;
        this->money = 5000;
        storage.push_back(*this);
    }

    // remove an user from the database
    static void removeUser(std::string username)
    {
        for (int i = 0; i < storage.size(); i++)
        {
            if (storage[i].login == username)
            {
                storage.erase(storage.begin() + i);
                return;
            }
        }
    }

    // check information to login
    static bool verify(std::string login, std::string psswrd, User *&user)
    {
        for (int i = 0; i < storage.size(); i++)
        {
            if (storage[i].login == login && storage[i].psswrd == psswrd)
            {
                user = &storage[i];
                return true;
            }
        }
        return false;
    }

    // simple users count
    static int usersNum()
    {
        return storage.size();
    }

    // list the users login
    static void listUsers()
    {
        for (int i = 0; i < storage.size(); i++)
        {
            std::cout << storage[i].login << std::endl;
        }
    }

    // return users cash
    static float cash(User *user)
    {
        return user->money;
    }

    // withdraw
    static bool withdraw(User *user, float ammount)
    {
        if (user->money >= ammount)
        {
            user->money -= ammount;
            return true;
        }
        else
            return false;
    }
};

std::vector<User> User::storage; // Definition of static storage

// Display the menu
void menu()
{
    std::cout << "(1) Login" << '\n'
              << "(2) Register" << '\n'
              << "(3) Exit" << '\n'
              << "(4) List Users" << '\n'
              << "User count: " << User::usersNum() << std::endl;
}
int main()
{
    int option;            // user's choice
    bool main_loop = true; // loop controller
    while (main_loop)
    {
        menu();
        std::cin >> option;
        std::cin.ignore();
        clear();

        switch (option)
        {
        case 1:
        {
            int i = 0;
            bool logout = true;
            while (logout)
            {
                std::string login, psswrd;
                if (i == 3)
                {
                    std::cout << "You failed 3 times, try again later! " << std::endl;
                    delay(3000);
                    break;
                }
                std::cout << "Enter username: ";
                std::getline(std::cin, login);

                // Validate the username input
                if (login.empty() || std::all_of(login.begin(), login.end(), [](char c)
                                                 { return std::isspace(c); }))
                {
                    std::cout << "Invalid username, please try again!" << std::endl;
                    continue;
                }

                std::cout << "Enter password: ";
                std::getline(std::cin, psswrd);

                // Validate the password input
                if (psswrd.empty() || std::all_of(psswrd.begin(), psswrd.end(), [](char c)
                                                  { return std::isspace(c); }))
                {
                    std::cout << "Invalid password, please try again!" << std::endl;
                    continue;
                }
                User *user = nullptr;
                if (User::verify(login, psswrd, user)) // successfully logged in
                {
                    bool logged = true;
                    while (logged)
                    {
                        clear();
                        float user_cash = User::cash(user);
                        std::cout << "Welcome " << login << "!\n\n";
                        int option2;
                        std::cout << "     $ " << user_cash << "\n\n"
                                  << "(1) Logout" << '\n'
                                  << "(2) Withdraw" << '\n'
                                  << "(3) Delete account" << std::endl;
                        std::cin >> option2;
                        switch (option2)
                        {
                        case 1:
                        {
                            clear();
                            logout = false, logged = false;
                            break;
                        }
                        case 2:
                        {
                            clear();
                            while (true)
                            {
                                
                                std::cout << "Current: $" << user_cash << "\nAmmount: ";
                                float ammount;
                                std::cin >> ammount;
                                if (User::withdraw(user, ammount))
                                {
                                    std::cout << "Successfully withdrawed $" << ammount << std::endl;
                                    delay(3000);
                                    break;
                                }
                                else
                                {
                                    std::cout << "Insufficient funds!" << std::endl;
                                }
                            }
                            break;
                        }
                        case 3:
                        {
                            User::removeUser(login);
                            logout = false, logged = false;
                            break;
                        }
                        default:
                        {
                            std::cout << "Invalid option, please try again!" << std::endl;
                            clear();
                            break;
                        }
                        }
                    }
                }
                else
                {
                    clear();
                    std::cout << "Username or password incorrect, please try again!" << std::endl;
                    i++;
                }
            }
            break;
        }
        case 2:
        {
            User user;
            std::string login, psswrd;
            while (true)
            {
                std::cout << "Enter username: ";
                std::getline(std::cin, login);
                if (User::verifyLogin(login) == true)
                {
                    std::cout << "Username already exists, please choose another one !" << std::endl;
                    continue;
                }
                else
                    break;
            }
            std::cout << "Enter password: ";
            std::getline(std::cin, psswrd);
            user.registration(login, psswrd);
            break;
        }
        case 3:
            main_loop = false;
            break;

        case 4:
        {
            int i{0};
            while (true)
            {
                clear();
                if (i > 0)
                    std::cout << "You can only exit :)" << std::endl;
                User::listUsers();
                int exit;
                std::cout << "(0) Exit" << std::endl;
                std::cin >> exit;
                if (exit == 0)
                    break;
                i++;
            }
            break;
        }
        default:
            std::cout << "Invalid option, please try again !" << std::endl;
            break;
        }
        clear();
    }

    return 0;
}
