#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <map>

//using namespace std;

class BankAccount{
    std::string accountNumber;
    float balance;
public:
    BankAccount(){

    }
    BankAccount(std::string accountNumber, float balance = 0)
    :accountNumber(accountNumber),balance(balance)
    {
    }

    std::string getAccountNumber()
    {
	    return this->accountNumber;
    }
};

class IAccountStorage {
public:    
    virtual void addAccount(BankAccount account) = 0;
	virtual BankAccount *findAccount(std::string accountNumber) = 0;        
};



class Bank
{
private:
	IAccountStorage * accountStorage;
public:
	Bank(IAccountStorage *storage):accountStorage(storage){

    }
	bool addAccount(std::string accountNumber){
        //validate
        //if something (accountNumber) return false
        accountStorage->addAccount(accountNumber);
        return true;
    }
	BankAccount *getAccount(std::string accountNumber){
        return accountStorage->findAccount(accountNumber);
    }
};

class VectorAccountStorage: public IAccountStorage{
        std::vector<BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts.push_back(account);
    }

    BankAccount *findAccount(std::string accountNumber){
        //for(BankAccount &account : accounts){
        for(int i = 0; i < accounts.size();i++){
            BankAccount &account = accounts[i];
            if(account.getAccountNumber() == accountNumber ){
                return &account;                                        
            }
        }
        return nullptr;
    }
    

};



class MapAccountStorage: public IAccountStorage{
        std::map<std::string,BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts[account.getAccountNumber()] = account;
    }

    BankAccount *findAccount(std::string accountNumber){
        return &accounts[accountNumber];
    }
    

};





int main(int, char**){

    //std::map<std::string,BankAccount> personerna;
    //personerna["2008-05-28"] = new BankAccount();

    // int arrayen[10];

    // arrayen[0] = 12; // 0 * sizeof(int) + 1000
    // arrayen[120] = 13; // IDIOT 120 * sizeof(int) + 1000 
    // arrayen[-10] = 11; // IDIOT

    //VectorAccountStorage storage;
    MapAccountStorage storage;
    Bank bank(&storage);

    const int AntalAccounts =  1000000;


    std::string sFirst = ""; 
    std::string sLast = ""; 
    std::string sNotFound = "notfound"; 
    std::cout << "INITIALIZE: " << std::endl;
    
    // auto - är BEST PRACTICE
    //int i = 12;
//    auto i = 12;
//    auto player = new std::chrono::high_resolution_clock::HpckeyPlayer();
    auto startTime = std::chrono::high_resolution_clock::now();
//    std::chrono::_V2::system_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    for(int i = 0;i < AntalAccounts; i++){
        std::string accountNumber =  std::to_string(i);
        if(i == 0){
            sFirst = accountNumber;
        }
        if(i == AntalAccounts-1){
            sLast = accountNumber;
        }
        bank.addAccount(std::to_string(i));
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "INIT Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    BankAccount *p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;
}