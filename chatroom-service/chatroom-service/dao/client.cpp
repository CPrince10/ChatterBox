#include"client.h"
#include"api.h"
#include<string>
status Client::loginIn(TransPara transPara)
{
    std::string pw;
    transPara.tranJson.at("password").get_to(pw);
    std::string sql;
    int ID= transPara.tranJson["ID"];
    sql = "select PasswordHash from chatroom_sys.user where ID = " + std::to_string(ID) ;
    MYSQL_QUERY(sql)
    if (!res->next())
    {
        delete res;
        std::cout << "Query failed!";
        return 0;
    }
    else if (pw == res->getString("PasswordHash"))
    {
        delete res;
        std::cout << "Query succeeded!";
        return 1;
    }
    delete res;
    return 0;

}

int Client::signUp(TransPara transPara)
{
    std::string pw;
    std::string name;

    transPara.tranJson.at("password").get_to(pw);
    transPara.tranJson.at("name").get_to(name);
    std::string sql;
    sql = "select * from chatroom_sys.user where Username = '" + name + "'";
    std::cout << sql << std::endl;
    MYSQL_QUERY(sql);
    if (!res->next()) {
        delete res;
        std::cout << "User name query does not exist!";
        sql = "insert into chatroom_sys.user (Username,PasswordHash) values('" + name +"','"+ pw + "'); ";
        std::cout << sql << std::endl;
        sql::Statement* stmt; stmt = con->createStatement(); bool returnValue = stmt->execute(sql);
        int rowAffect = stmt->getUpdateCount();
        delete stmt;
        if (rowAffect==1)
        {
            std::cout << "User registered successfully !";
            sql = "select ID from chatroom_sys.user where Username = '" + name + "'";
    std::cout << sql << std::endl;
            MYSQL_QUERY(sql);
            if (!res->next()) {
                std::cout << "Failed to return user's ID";
                delete res;
                return 0;
            }
            return res->getInt("ID");
            delete res;
        }
    }
    return 0;
}

