#pragma once

#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>
#include <iostream>
#include <string>

#include "Message.h"

/*���������-����������*/

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
	void start() { _isChatWork = true; }; // ������ ������ ����, ��������� _isChatWork � true
	bool isChatWork() const { return _isChatWork; } // ���������� ������� ��������� ���� ��������/�� ��������
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; } // ���� ������� ������������ ������� �� ����������������� ���� - ���������� nullptr
	void showLoginMenu();
	void showUserMenu();

private:
	bool _isChatWork = false; // ����������, ���������� �� ����������� ������ ���� (� ������ ������ ���� ��������� � true)
	std::unordered_map<int,User> _users; // ��������� ���������� ���� ������������������ �������������
	std::vector<Message> _messages; // ������ - ������, ���������� ��� ������������ � ��� ���������
	std::shared_ptr<User> _currentUser = nullptr; // ��������� �� �������� ������������
	int _data_count = 0;
	int _mem_size = 8;

	void logIn(); // ���� ����������� ������������
	void signUp(); // ���� ����������� ������ ������������
	void addUser(std::string login, uint* password);
	int hash_func(const std::string& login, int offset);
	int hf_multiply(int val);
	void showAllUsersLogin(); // �������� ���� �������������, ���������������� � ����
	void showChat(); // �������� ��� ��������� � ����
	void addMessage(); // �������� ��������� ���� / ����������� ������������
	void changePassword(); // ��������� ������ �������� ������������

	std::shared_ptr<User> getUserByLogin(const std::string& login) const; // ����� ������������ �� ������
};
