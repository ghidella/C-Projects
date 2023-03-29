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
    while (true)
    {
        int option;
        std::cout << "(2) Login" << '\n'
                  << "(1) Register" << std::endl;
        std::cin >> option;
        std::cin.ignore();
        std::system("clear");
        if (option == 1)
        {
            User user;
            std::string login, psswrd;
            std::cout << "Enter username: ";
            std::getline(std::cin, login);
            std::cout << "Enter password: ";
            std::getline(std::cin, psswrd);
            registration(&user, login, psswrd);
            storage.push_back(user);
        }
        else if (option == 2)
        {
            while (true)
            {
                std::string login, psswrd;
                std::cout << "Enter username: ";
                std::getline(std::cin, login);
                std::cout << "Enter password: ";
                std::getline(std::cin, psswrd);
                if(verify(storage, login, psswrd) == true) break;
                std::system("clear");    
                std::cout<<"Username or password incorrect, please try again !"<<std::endl;           
            }
        }
    }

    return 0;
}
