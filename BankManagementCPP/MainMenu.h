#include "DataBase.h"
#include "IMainMenu.h"
#include <iostream>
#include <string>

class MainMenu : public IMainMenu {
public:
	DataBase d;
	MainMenu() : CheckLoginFlag{ false }, LocalLoginFlag{ true }, amount_of_money{ 0 } {}

	void MainMenuStructure() override {
		int user_input;
		int try_login_counter = 0;
		if (LocalLoginFlag) {
			std::cout << "Please Select the action to be performed if you write 0 sign up screen will be open or write 1 login menu will be open: " << std::endl;
			std::cin >> user_input;

			switch (user_input) {
			case 0:
				CreateAccount();
				break;
			case 1:
				CheckLoginFlag = true;
				LocalLoginFlag = false;
				while (!LoginAccount()) {
					std::cout << "You entered the ID or Password incorrectly" << std::endl;
					try_login_counter++;
					if (try_login_counter == 3) {
						std::cout << "You entered ID or Password incorrect 3 times. Please try again later\n";
						CheckLoginFlag = false;
						LocalLoginFlag = true;
						try_login_counter = 0;
						break;
					}
				}
				break;
			default:
				break;
			}
		}

	}

	void AfterLoginMenu() override {
		if (CheckLoginFlag) {
			int user_input_ = 0;
			/*
			 Add account deletion screen (4)(added but if there is a same email info old one should be deleted)
			*/
			std::cout << "Press 1 for account information screen." << std::endl;
			std::cout << "Press 2 for see amount of money you have." << std::endl;
			std::cout << "Press 3 for reach the transfer screen." << std::endl;
			std::cout << "Press 4 for account deletion." << std::endl;
			std::cout << "Press 5 for log out." << std::endl;
			std::cin >> user_input_;
			switch (user_input_) {
			case 1:
				AccountInformation();
				break;
			case 2:
				AmountOfMoney();
				break;
			case 3:
				TransferMoney();
				break;
			case 4:
				if (DeleteAccount()) {
					CheckLoginFlag = false;
					LocalLoginFlag = true;
					MainMenuStructure();
				}
				else {
					std::cout << "Account deletion failed please try again.\n";
				}
			case 5:
				LogOut();
			default:
				break;
			}
		}
		else {
			return;
		}

	}

private:
	bool CreateAccount() {
		std::cout << "Please define a ID: " << std::endl;
		std::cin >> user_input_1;
		std::cout << "Please define a Password: " << std::endl;
		std::cin >> user_input_2;
		CheckPasswordAppoprity(user_input_2, user_input_1);
		std::cout << "Please specify your Email: " << std::endl;
		std::cin >> user_input_3;
		std::ofstream user_input_1_(user_input_1);
		user_input_1_ << 0;
		user_input_1_.close();
		return d.WriteUserInformationToDataBaseFile(user_input_1, user_input_2, user_input_3);
	}

	bool LoginAccount() {
		std::cout << "Please specify your ID for login : " << std::endl;
		std::cin >> user_input_1;
		std::cout << "Please specify your Password for login : " << std::endl;
		std::cin >> user_input_2;

		bool return_value = d.UserLoginCheck(user_input_1, user_input_2);
		if (return_value == true) {
			ChangeAmountOfMoneyFromFile();
		}
		return return_value;
	}

	void AccountInformation() {
		std::string line;
		std::ifstream InputFileForCheck("database.txt");
		while (std::getline(InputFileForCheck, line)) {
			if (line.find(user_input_1) != std::string::npos) {
				std::cout << "Account ID: " << user_input_1 << std::endl;
			}
			else if (line.find(user_input_2) != std::string::npos) {
				std::cout << "Account Password: " << user_input_2 << std::endl;
			}
			else if (line.find(user_input_3) != std::string::npos) {
				std::cout << "Account Email: " << user_input_3 << std::endl;
			}
		}
		InputFileForCheck.close();
	}

	void AmountOfMoney() {
		std::cout << "Amount of money in your account is: " << amount_of_money << std::endl;
	}

	void TransferMoney() {
		std::ifstream CheckFile(user_input_1);
		std::ofstream AdditionToFile("InputDeletionFile.txt");
		uint32_t transfer_amount;
		std::cin >> transfer_amount;
		amount_of_money += transfer_amount;
		std::cout << "money transfer successfull" << std::endl;

		std::string line;
		std::string id;
		bool check_flag;
		while (std::getline(CheckFile, line)) {
			if (line.find(amount_of_money - transfer_amount) != std::string::npos) {
				check_flag = false;
			}
			else {
				id = line;
				check_flag = true;
			}

			if (check_flag) {
				if (id == user_input_1) {
					AdditionToFile << line << std::endl;
				}
			}
			CheckFile.close();
			AdditionToFile << amount_of_money;
			AdditionToFile.close();
			std::remove(user_input_1.c_str());
			std::rename("InputDeletionFile.txt", user_input_1.c_str());
		}

	}

	void ChangeAmountOfMoneyFromFile() {
		std::cout << user_input_1 << std::endl;
		std::ifstream CheckFile(user_input_1);
		if (!CheckFile.is_open()) {
			std::cout << "" << std::endl;
		}
		std::string line;
		std::string money;
		while (std::getline(CheckFile, line)) {
			money = line;
		}
		amount_of_money = std::stoi(money);
		CheckFile.close();
	}

	bool DeleteAccount() {
		return d.UserAccountDeletion(user_input_1, user_input_2);
	}

	void LogOut() {
		CheckLoginFlag = false;
		LocalLoginFlag = true;
		MainMenuStructure();
	}

	bool CheckPasswordAppoprity(std::string password, std::string ID) {
		int size = password.size();
		char first_index = password[0];
		bool return_value{};
		while (flag) {
			if (size < 10) {
				std::cout << "Password size must be bigger then 10 charachter\n";
				std::cout << "Please define a new password: \n";
				std::cin >> user_input_2;
				size = user_input_2.size();
				first_index = user_input_2[0];
				return_value = false;
				continue;
			}
			else if (first_index == '0') {
				std::cout << "Password can not begin with 0\n";
				std::cout << "Please define a new password: \n";
				std::cin >> user_input_2;
				first_index = user_input_2[0];
				continue;
				return_value = false;
			}
			else if (!comparison_result) {
				comparison_result = IdPasswordComparison(user_input_2, ID);
				std::cout << "Password and ID cannot have same beginning\n";
				std::cout << "Please define a new password: \n";
				if (!comparison_result) {
					std::cin >> user_input_2;
				}
				continue;
				return_value = false;
			}
			else {
				comparison_result = false;
				return_value = true;
				flag = false;
			}
		}
		flag = true;
		return return_value;
	}

	bool IdPasswordComparison(std::string password_, std::string ID_) {
		int Psize = password_.size();
		int IDsize = ID_.size();
		bool return_value = false;
		if (Psize > IDsize) {
			for (int i = 0; i < IDsize; i++) {
				if (password_[i] == ID_[i]) {
					return_value = false;
				}
				else {
					return_value = true;
					break;
				}
			}
		}
		else if (IDsize > Psize) {
			for (int i = 0; i < Psize; i++) {
				if (password_[i] == ID_[i]) {
					return_value = false;
				}
				else {
					return_value = true;
					break;
				}
			}

		}
		return return_value;
	}

	bool CheckLoginFlag;
	bool LocalLoginFlag;
	bool flag{ true };
	bool comparison_result{ false };
	uint32_t amount_of_money;
	std::string user_input_1;
	std::string user_input_2;
	std::string user_input_3;
};