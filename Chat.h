#pragma once

#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>
#include <iostream>
#include <string>

#include "Message.h"

/*Структуры-исключения*/

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is bisy"; }
};
struct UserPasswordExp : public std::exception
{
	const char* what() const noexcept override { return "error: the password length must be from 4 to 8 digits or letters"; }
};

class Chat
{
public:
	void start() { _isChatWork = true; }; // начало работы чата, установка _isChatWork в true
	bool isChatWork() const { return _isChatWork; } // возвращает текущее состояние чата работает/не работает
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; } // если текущий пользователь выходит из пользовательского меню - возвращает nullptr
	void showLoginMenu();
	void showUserMenu();

private:
	bool _isChatWork = false; // переменная, отвечающая за прекращение работы чата (в начале работы чата переходит в true)
	std::unordered_map<int,User> _users; // контейнер содержащий всех зарегистрированных пользователей
	std::vector<Message> _messages; // вектор - массив, содержащий все отправленные в чат сообщения
	std::shared_ptr<User> _currentUser = nullptr; // указатель на текущего пользователя
	int _data_count = 0;
	int _mem_size = 8;

	void logIn(); // меню авторизации пользователя
	void signUp(); // меню регистрации нового пользователя
	void addUser(std::string login, uint* password);
	int hash_func(const std::string& login, int offset);
	int hf_multiply(int val);
	void showAllUsersLogin(); // показать всех пользователей, зарегистрованных в чате
	void showChat(); // показать все сообщения в чате
	void addMessage(); // написать сообщение всем / конкретному пользователю
	void changePassword(); // изменение пароля текущего пользователя

	std::shared_ptr<User> getUserByLogin(const std::string& login) const; // найти пользователя по логину
};
