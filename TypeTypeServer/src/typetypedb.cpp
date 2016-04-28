#include "typetypedb.h"
#include "typetypeprotocol.h"

#include <mysql/mysql.h>

#include <iostream>

TypeTypeDB::TypeTypeDB() {

	mysql_init(&mysql);

	connect(SQL_SERVER, SQL_USER, SQL_DATABASE, SQL_PASSWORD);
}

TypeTypeDB::~TypeTypeDB() {
	mysql_close(connection);
}

void TypeTypeDB::connect(const char *server, const char *user, const char *database, const char *password) {
	connection = mysql_real_connect(&mysql,server,user,password,database,0,0,0);
	
	if (connection == NULL)
		std::cout << mysql_error(&mysql) << std::endl;
}

void TypeTypeDB::query(const char *query) {
}

bool TypeTypeDB::db_register(client_register proto) {
	std::string query = "select count(*) from user where nick = '" + proto.nick + "';";
	mysql_query(&mysql, query.c_str());
	result = mysql_store_result(&mysql);

	row = mysql_fetch_row(result);
	if (atoi(row[0]) == 1)
		return false;

	mysql_free_result(result);

	query = "insert into user (nick, email, name, pass) values ('" + proto.nick + "','" + proto.name + "','" + proto.email + "','" + proto.pass + "');";
	mysql_query(&mysql, query.c_str());
	
	query = "insert into userinfo (played, wins, avg) values (0,0,0)";
	mysql_query(&mysql, query.c_str());

	return true;
}

int TypeTypeDB::db_login(client_login proto) {
	std::string query = "select id from user where nick = '" + proto.nick + "' AND pass = '" + proto.pass + "';";
	mysql_query(&mysql, query.c_str());

	result = mysql_store_result(&mysql);

	int id = 0;
	if (mysql_num_rows > 0) {
		row = mysql_fetch_row(result);
		id = atoi(row[0]);
	}
	
	mysql_free_result(result);

	return id;
}

server_stories TypeTypeDB::db_stories() {
	server_stories stories;
	std::string query = "select name, parts from story";
	mysql_query(&mysql, query.c_str());

	result = mysql_store_result(&mysql);
	while ((row = mysql_fetch_row(result))) {
		stories.stories.push_back(row[0]);
	}

	stories.count = mysql_num_rows(result);
	
	mysql_free_result(result);

	return stories;

}
