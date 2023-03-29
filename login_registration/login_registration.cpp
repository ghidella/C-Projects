#include <iostream>
#include <string>
#include <vector>

class User
{
public:
    std::string login;
    std::string psswrd;
};

void registration(User *user, std::string login, std::string psswrd)
{
    user->login = login;
    user->psswrd = psswrd;
}

bool verify(std::vector<User> storage, std::string login, std::string psswrd)
{
    for (int i = 0; i < storage.size(); i++)
    {
        if (storage[i].login == login && storage[i].psswrd == psswrd)
            return true;
    }
    return false;
}

int main()
{
    std::vector<User> storage;
    int option;
    while (true)
    {
        int option;
        std::cout << "(1) Login" << '\n'
                  << "(2) Register" << '\n'
                  << "(3) Exit" << std::endl;
        std::cin >> option;
        std::cin.ignore();
        std::system("clear");
        if (option == 2)
        {
            User user;
            std::string login, psswrd;
            std::cout << "Enter username: ";
            std::getline(std::cin, login);
            std::cout << "Enter password: ";
            std::getline(std::cin, psswrd);
            registration(&user, login, psswrd);
            storage.push_back(user);
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
                if (verify(storage, login, psswrd) == true)
                {
                    std::system("clear");
                    std::cout << "You are now logged" << std::endl;
                    int option2;
                    std::cout << "(1)Logout" << std::endl;
                    std::cin >> option2;
                    if (option2 == 1){
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
