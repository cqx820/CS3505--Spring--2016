#include "typetypedb.h"
#include "typetypeprotocol.h"

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
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

bool TypeTypeDB::db_report(client_report proto) {
	std::string query = "insert into game (material, user, started, elapsed, completed, speed) values ('" + proto.story + "','" + proto.user + "','" + std::to_string((int)proto.started) + "','" + std::to_string((int)proto.elapsed) + "','" + std::to_string((int)proto.completed) + "','" + std::to_string((int)proto.difficulty) + "');";
	std::cout << "query: " << query << std::endl;
	if (!mysql_query(&mysql, query.c_str()))
		return false;

	return true;
}

std::string TypeTypeDB::db_stat() {
	std::string m;
	std::string query = "select material, user, started, elapsed, completed, speed from game order by completed DESC;";
	mysql_query(&mysql, query.c_str());

	result = mysql_store_result(&mysql);
	while ((row = mysql_fetch_row(result))) {
			m += "<tr><td>" + std::string(row[0]) + "</td>";
			m += "<td>" + std::string(row[1]) + "</td>";
			m += "<td>" + std::string(row[2]) + "</td>";
			m += "<td>" + std::string(row[3]) + "</td>";
			m += "<td>" + std::string(row[4]) + "</td>";
			m += "<td>" + std::string(row[5]) + "</td></tr>";
	}

	mysql_free_result(result);

	return m;
}
