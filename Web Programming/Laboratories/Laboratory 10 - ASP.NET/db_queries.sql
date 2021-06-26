create database pw_lab10;
use pw_lab10;

create table Users(
	Id int identity(1,1) primary key,
	Name varchar(250),
	Username varchar(250),
	Password varchar(250),
	Age int,
	Role varchar(250),
	Profile varchar(250),
	Email varchar(250),
	Webpage varchar(250),
);

insert into Users(Name, Username, Password, Age, Role, Profile, Email, Webpage) 
values ('name1', 'username1', 'pass1', 20, 'role1', 'profile1', 'email1', 'webpage1');
insert into Users(Name, Username,Password, Age, Role, Profile, Email, Webpage) 
values ('name2', 'username2','pass1', 20, 'role2', 'profile2', 'email2', 'webpage2');
insert into Users(Name, Username,Password, Age, Role, Profile, Email, Webpage) 
values ('name3', 'username3','pass1', 20, 'role1', 'profile3', 'email3', 'webpage3');
insert into Users(Name, Username,Password, Age, Role, Profile, Email, Webpage) 
values ('name4', 'username4','pass1', 20, 'role2', 'profile4', 'email4', 'webpage4');
insert into Users(Name, Username,Password, Age, Role, Profile, Email, Webpage) 
values ('name5', 'username5','pass1', 20, 'role3', 'profile5', 'email5', 'webpage5');



select * from Users;








