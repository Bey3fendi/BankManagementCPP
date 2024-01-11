#pragma once
#include <string>
class IDataBase {
	virtual bool WriteUserInformationToDataBaseFile(std::string data_1, std::string data_2, std::string data_3) = 0;
	virtual bool UserLoginCheck(std::string data_1, std::string data_2) = 0;
	virtual bool UserAccountDeletion(std::string data_1, std::string data_2) = 0;
	virtual bool UserAccountDeletion(std::string data_1, std::string data_2, std::string data_3) = 0;
};