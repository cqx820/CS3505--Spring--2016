#include "typetypeprotocol.h"

#ifndef TYPETYPEDB_H
#define TYPETYPEDB_H

#include <mysql/mysql.h>

#include <vector>
#include <string>

#define SQL_SERVER "foo.mx"
#define SQL_USER "utah_3505"
#define SQL_DATABASE "typetyperevolution"
#define SQL_PASSWORD "funforta"

class TypeTypeDB {
	std::vector<std::string> tables;
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *connection, mysql;

	int state;

public:
	TypeTypeDB();
	~TypeTypeDB();

	bool db_register(client_register);
	int db_login(client_login);
	server_stories db_stories();
	std::vector<std::string> db_story(server_story);
	bool db_report(client_report);
	std::string db_stat();
	
private:
	void connect(const char*, const char*, const char*, const char*);
	void query(const char*);
};

#endif
