#include <iostream>
#include <string>
#include <vector>

class User
{
private:
    std::string login;
    std::string psswrd;
    static std::vector<User> storage;


public:
    void registration(std::string login, std::string psswrd)
    {
        this->login = login;
        this->psswrd = psswrd;
        storage.push_back(*this);
    }

    static bool verify(std::string login, std::string psswrd)
    {
        for (int i = 0; i < storage.size(); i++)
        {
            if (storage[i].login == login && storage[i].psswrd == psswrd)
                return true;
        }
        return false;
    }
};

std::vector<User> User::storage; // Definition of static storage

int main()
{
    int option;
    while (true)
    {
        std::cout << "(1) Login" << '\n'
                  << "(2) Register" << '\n'
                  << "(3) Exit" << std::endl;
        std::cin >> option;
        std::cin.ignore();
        std::system("clear");
        if (option == 2)
        {
            std::string login, psswrd;
            std::cout << "Enter username: ";
            std::getline(std::cin, login);
            std::cout << "Enter password: ";
            std::getline(std::cin, psswrd);
            User user;
            user.registration(login, psswrd);
            std::system("clear");
        }
        else if (option == 1)
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
                std::cout << "Enter password: ";
                std::getline(std::cin, psswrd);
                if (User::verify(login, psswrd))
                {
                    std::system("clear");
                    std::cout << "You are now logged" << std::endl;
                    int option2;
                    std::cout << "(1)Logout" << std::endl;
                    std::cin >> option2;
                    if (option2 == 1)
                    {
                        std::system("clear");
                        break;
                    }
                    std::cout << "Invalid option, please try again!" << std::endl;
                }
                std::system("clear");
                std::cout << "Username or password incorrect, please try again!" << std::endl;
                i++;
            }
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            std::cout << "Invalid option, please try again !" << std::endl;
        }
    }

    return 0;
}
