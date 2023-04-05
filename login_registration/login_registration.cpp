#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> // For std::system()

#if defined(_WIN32) || defined(_WIN64) // For Windows
#define CLEAR "cls"
#else // For Linux and others
#define CLEAR "clear"
#endif

class User
{
private:
    std::string login;
    std::string psswrd;
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
        storage.push_back(*this);
    }

    // check information to login
    static bool verify(std::string login, std::string psswrd)
    {
        for (int i = 0; i < storage.size(); i++)
        {
            if (storage[i].login == login && storage[i].psswrd == psswrd)
                return true;
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
    int option; // user's choice
    bool main_loop = true; // loop controller
    while (main_loop)
    {
        menu();
        std::cin >> option;
        std::cin.ignore();
        std::system(CLEAR);

        switch (option)
        {
        case 1:
        {
            int i = 0;
            while (true)
            {
                std::string login, psswrd;
                if (i == 3)
                {
                    std::cout << "You failed 3 times, try again later! " << std::endl;
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
                if (User::verify(login, psswrd))
                {
                    std::system(CLEAR);
                    std::cout << "You are now logged" << std::endl;
                    int option2;
                    std::cout << "(1)Logout" << std::endl;
                    std::cin >> option2;
                    if (option2 == 1)
                    {
                        std::system(CLEAR);
                        break;
                    }
                    std::cout << "Invalid option, please try again!" << std::endl;
                }
                std::system(CLEAR);
                std::cout << "Username or password incorrect, please try again!" << std::endl;
                i++;
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
                if (user.verifyLogin(login) == true)
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
            std::system(CLEAR);
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
                std::system(CLEAR);
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
            std::system(CLEAR);
            break;
        }
        default:
            std::cout << "Invalid option, please try again !" << std::endl;
            break;
        }
    }

    return 0;
}
