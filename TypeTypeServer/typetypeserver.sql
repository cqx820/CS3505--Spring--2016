create database typetyperevolution;
use typetyperevolution;

create table user(
	id int(20) not null auto_increment,
	nick varchar(50) not null,
	email varchar(255) not null,
	name varchar(50) not null,
	pass varchar(255) not null,
	PRIMARY KEY (id)
) Engine = InnoDB;

create table userinfo(
	id int(20) not null auto_increment,
	played int(10),
	wins int(10),
	avg int(3),
	PRIMARY KEY (id),
	FOREIGN KEY (id) REFERENCES user(id)
) Engine = InnoDB;

create table story(
	id int(20) not null auto_increment,
	name varchar(255) not null,
	parts int(20) not null,
	PRIMARY KEY (id)
) Engine = InnoDB;

create table user_story(
	user int(20) not null,
	story int(20) not null,
	completed int(20),
	PRIMARY KEY (user, story),
	FOREIGN KEY (user) REFERENCES user(id),
	FOREIGN KEY (story) REFERENCES story(id)
) Engine = InnoDB;
	
create table game(
	id int(50) not null auto_increment,
	material varchar(255) not null,
	user varchar(255) not null,
	/*elapsed int(32) not null,
	started int(32) not null,
	completed int(5),
	correct int(5),
	speed int(3),*/
	score int(10),
	PRIMARY KEY (id)
) Engine = InnoDB;

/*insert into user (nick, email, name, pass)
	values ("Ross", "ross@spam.im", "Ross DiMassimo", "foo");
insert into userinfo (played, wins, avg)
	values (0,0,100);*/

insert into story(name, parts)
	values ("Alice In Wonderland", 139);
