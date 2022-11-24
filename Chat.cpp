#include "Chat.h"

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;
	std::cout << "\n*** Welcome to Console Chat! ***" << std::endl;

	do
	{
		std::cout << " \n1 - Autorization \n2 - Registration \n0 - Exit" << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			logIn();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			_isChatWork = false;
			break;
		default:
			std::cout << "Wrong choice! Choose 0, 1 or 2" << std::endl;
			break;
		}
	} while (!_currentUser && _isChatWork);
}

void Chat::showUserMenu()
{
	std::cout << "\n*** You have entered the User menu ***" << std::endl;
	char operation;

	do
	{
		std::cout << "\n1 - Show all users \n2 - Show all messages"
			<< "\n3 - Add message to chat \n4 - Change password \n5 - Sign Out" << std::endl;
		std::cin >> operation;
		switch (operation)
		{
		case '1':
			showAllUsersLogin();
			break;
		case '2':
			//showChat();
			break;
		case '3':
			//addMessage();
			break;
		case '4':
			//changePassword();
			break;
		case '5':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "Wrong choice! Choose 1 - 5" << std::endl;
			break;
		}
	} while (_currentUser);

}

void Chat::logIn()
{
	std::string login, password;
	std::string operation;

	do {
		std::cout << "Enter your login: " << std::endl;
		std::cin >> login;
		_currentUser = getUserByLogin(login);
		if (_currentUser == nullptr)
		{
			std::cout << "The login entered is incorrect. To exit press 0, to continue press any key:" << std::endl;
			std::cin >> operation;
			if (operation == "0")
				return;
		}
		else
		{
			std::cout << "Enter your password: " << std::endl;
			std::cin >> password;
			for (size_t i = 0; i < _mem_size; i++)
			{
				int index = hash_func(login, i);
				std::unordered_map<int, User>::iterator it = _users.find(index);
				uint* PasHash = sha1(password.c_str(), password.length());
				if (!memcmp(it->second.getUserPassword(), PasHash, SHA1HASHLENGTHBYTES))
				{
					std::cout << "Hello " << it->second.getUserLogin() << "!" << std::endl;
					delete[] PasHash;
				}
				else
				{
					std::cout << "The password entered is incorrect. To exit press 0, to continue press any key:" << std::endl;
					std::cin >> operation;
					if (operation == "0")
					{
						_currentUser = nullptr;
						return;
					}
				}
			}
		}
	} while (!_currentUser);
}

void Chat::signUp()
{
	std::string login, password;
	bool passwordOk = false;

	std::cout << "Enter your login: " << std::endl;
	std::cin >> login;
	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}
	while (!(passwordOk))
	{
		std::cout << "Enter your password: " << std::endl;
		std::cin >> password;
		if (password.length() < 4 || password.length() > 8)
			throw UserPasswordExp();
		else
		{
			passwordOk = true;
			uint* _pass_sha1_hash = sha1(password.c_str(), password.length());
			addUser(login, _pass_sha1_hash);
		}
	}
}

void Chat::addUser(std::string login, uint* password)
{
	if (_data_count >= _mem_size)
		_mem_size *= 2;

	int index = -1;
	int i = 0;
	// берем пробы по всем i от 0 до размера массива
	for (; i < _mem_size; i++) {
		index = hash_func(login, i);
		std::unordered_map<int, User>::iterator it = _users.find(index);
		if (!_users.size() || it->second.getUserStatus() == 0)
			break;
	}
	if (i >= _mem_size)
	{
		_mem_size *= 2;
		addUser(login, password);
	}
	else
	{
		User user = User(login, password);
		_currentUser = std::make_shared<User>(user);
		_users.emplace(index,user);
		_data_count++;
	}
}

int Chat::hash_func(const std::string& login, int offset) {
	long sum = 0;
	for (int i = 0; i < login.length(); i++)
	{
		sum += login[i];
	}
	return (hf_multiply(sum) + offset * offset) % _mem_size;
}

int Chat::hf_multiply(int val) {
	const double A = 0.7;
	return int(_mem_size * (A * val - int(A * val)));
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : _users)
	{
		if (login == user.second.getUserLogin())
		{
			return std::make_shared<User>(user);
		}
	}
	return nullptr;
}

void Chat::showAllUsersLogin()
{
}
