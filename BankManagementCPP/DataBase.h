#pragma once
/*This class contains user login data and user account management like
account delete, account creation etc.*/
#include <iostream>
#include <fstream>
#include "IDatabase.h"
#include <string>
class DataBase : public IDataBase {
public:
	DataBase() : RetryCountforOpenFileAgain_{ 5 } {
		data_base_file.open("database.txt", std::ios::app);
	}

	// a method for add user data to the .txt file
	bool WriteUserInformationToDataBaseFile(std::string data_1, std::string data_2, std::string data_3) override {
		bool return_value;
		if (!data_base_file.is_open()) {
			while (RetryCountforOpenFileAgain_ > 0) {
				if (!data_base_file.is_open()) {
					RetryCountforOpenFileAgain_--;
				}
				else {
					RetryCountforOpenFileAgain_ = 5;
					break;
				}

			}
			if (RetryCountforOpenFileAgain_ <= 0) {
				return false;
			}

		}
		data_base_file << data_1 << "\n"; //ID
		data_base_file << data_2 << "\n"; //Password
		data_base_file << data_3 << "\n"; //Email
		data_base_file.close();

		return_value = CheckFileInputs(data_1, data_2, data_3);

		data_base_file.open("database.txt", std::ios::app);
		return return_value;
	}


	//Func which check user ID and Password for warn the user if he/she give wrong input.
	bool UserLoginCheck(std::string data_1, std::string data_2) override {
		data_base_file.close();
		std::ifstream InputFileForCheck("database.txt");
		bool FileSituation = false;
		bool UserInputCheckFlag = false;
		if (!InputFileForCheck.is_open()) {
			while (RetryCountforOpenFileAgain_ > 0) {
				if (!InputFileForCheck.is_open()) {
					RetryCountforOpenFileAgain_--;
				}
				else {
					RetryCountforOpenFileAgain_ = 5;
					break;
				}
			}
			if (RetryCountforOpenFileAgain_ <= 0) {
			}
		}
		else {
			FileSituation = true;
		}

		if (FileSituation) {
			std::string WordForSearch_1 = data_1;
			std::string WordForSearch_2 = data_2;
			std::string line;

			while (std::getline(InputFileForCheck, line)) {
				if (line.find(WordForSearch_1) != std::string::npos) {
				}
				else if (line.find(WordForSearch_2) != std::string::npos) {
					UserInputCheckFlag = true;
					break;
				}
			}
		}

		return UserInputCheckFlag;
	}

	bool UserAccountDeletion(std::string data_1, std::string data_2) override {
		data_base_file.close();
		bool return_value;
		return_value = DeletionDataFromDataBaseFile(data_1, data_2);
		return return_value;
	}

	bool UserAccountDeletion(std::string data_1, std::string data_2, std::string data_3) override {
		data_base_file.close();
		bool return_value;
		return_value = DeletionDataFromDataBaseFile(data_1, data_2, data_3);
		return return_value;
	}



private:
	bool CheckFileInputs(std::string data_1, std::string data_2, std::string data_3) {
		std::ifstream InputFileForCheck("database.txt");
		bool FileSituation = false;
		bool return_value = false;
		if (!InputFileForCheck.is_open()) {
			while (RetryCountforOpenFileAgain_ > 0) {
				if (!data_base_file.is_open()) {
					RetryCountforOpenFileAgain_--;
				}
				else {
					RetryCountforOpenFileAgain_ = 5;
					break;
				}

			}
			if (RetryCountforOpenFileAgain_ <= 0) {
				return false;
			}
		}
		else {
			FileSituation = true;
		}
		if (FileSituation) {
			return_value = ReverseDataBaseFile(InputFileForCheck, data_1, data_2, data_3);
		}
		InputFileForCheck.close();
		return return_value;
	}

	bool CheckFileInputs(std::string data_1, std::string data_2) {
		std::ifstream InputFileForCheck("database.txt");
		bool FileSituation = false;
		bool return_value = false;
		if (!InputFileForCheck.is_open()) {
			while (RetryCountforOpenFileAgain_ > 0) {
				if (!InputFileForCheck.is_open()) {
					RetryCountforOpenFileAgain_--;
				}
				else {
					RetryCountforOpenFileAgain_ = 5;
					break;
				}
			}
			if (RetryCountforOpenFileAgain_ <= 0) {
			}
		}
		else {
			FileSituation = true;
		}
		if (FileSituation) {
			return_value = ReverseDataBaseFile(InputFileForCheck, data_1, data_2);
		}
		InputFileForCheck.close();
		return return_value;
	}

	bool ReverseDataBaseFile(std::ifstream& file, std::string data_1, std::string data_2, std::string data_3) {
		std::string WordForSearch_1 = data_1;
		std::string WordForSearch_2 = data_2;
		std::string WordForSearch_3 = data_3;
		std::string line;
		bool return_value = false;
		while (std::getline(file, line)) {
			if (line.find(WordForSearch_1) != std::string::npos) {
			}
			else if (line.find(WordForSearch_2) != std::string::npos) {
			}
			else if (line.find(WordForSearch_3) != std::string::npos) {
				return_value = true;
			}
		}
		return return_value;
	}

	bool ReverseDataBaseFile(std::ifstream& file, std::string data_1, std::string data_2) {
		std::string WordForSearch_1 = data_1;
		std::string WordForSearch_2 = data_2;
		std::string line;
		bool return_value = false;
		while (std::getline(file, line)) {
			if (line.find(WordForSearch_1) != std::string::npos) {
			}
			else if (line.find(WordForSearch_2) != std::string::npos) {
				return_value = true;
			}
		}
		return return_value;
	}

	bool DeletionDataFromDataBaseFile(std::string data_1, std::string data_2, std::string data_3) { //V1 include email
		std::ifstream InputFileForCheck("database.txt");
		std::ofstream InputDeletionFile;
		InputDeletionFile.open("InputDeletionFile.txt");
		std::string WordForSearch_1 = data_1;
		std::string WordForSearch_2 = data_2;
		std::string WordForSearch_3 = data_3;
		std::string line;
		bool return_value;
		bool check_flag = true;

		while (std::getline(InputFileForCheck, line)) {
			if (line.find(WordForSearch_1) != std::string::npos || line.find(WordForSearch_2) != std::string::npos || line.find(WordForSearch_3) != std::string::npos) {
				check_flag = false;
			}
			else {
				check_flag = true;
			}

			if (check_flag) {
				InputDeletionFile << line << "\n"; //ID
				//InputDeletionFile << data_2 << "\n"; //Password
			}
		}
		InputFileForCheck.close();
		if (!InputFileForCheck.is_open()) {
		}
		InputDeletionFile.close();
		if (!InputDeletionFile.is_open()) {
		}
		if (std::remove("database.txt") != 0) {
			return_value = false;
		}
		if (std::rename("InputDeletionFile.txt", "database.txt") != 0) {
			return_value = false;
		}
		return_value = CheckFileInputs(data_1, data_2, data_3);
		return return_value == false;

	}
	bool DeletionDataFromDataBaseFile(std::string data_1, std::string data_2) { //V2 NOT INCLUDE EMAIL
		std::ifstream InputFileForCheck("database.txt");
		std::ofstream InputDeletionFile;
		InputDeletionFile.open("InputDeletionFile.txt");
		std::string WordForSearch_1 = data_1;
		std::string WordForSearch_2 = data_2;
		std::string line;
		bool return_value;
		bool check_flag = true;

		while (std::getline(InputFileForCheck, line)) {
			if (line.find(WordForSearch_1) != std::string::npos || line.find(WordForSearch_2) != std::string::npos) {
				check_flag = false;
			}
			else {
				check_flag = true;
			}

			if (check_flag) {
				InputDeletionFile << line << "\n"; //ID
				//InputDeletionFile << data_2 << "\n"; //Password
			}
		}
		InputFileForCheck.close();
		if (!InputFileForCheck.is_open()) {
		}
		InputDeletionFile.close();
		if (!InputDeletionFile.is_open()) {
		}
		if (std::remove("database.txt") != 0) {
			return_value = false;
		}
		if (std::rename("InputDeletionFile.txt", "database.txt") != 0) {
			return_value = false;
		}
		return_value = CheckFileInputs(data_1, data_2);
		return return_value == false;
	}

	std::ofstream data_base_file;
	uint8_t RetryCountforOpenFileAgain_;
};




