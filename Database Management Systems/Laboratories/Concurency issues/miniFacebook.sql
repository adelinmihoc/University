create database MiniFacebook
go
use MiniFacebook
go


create table Users(
Uid int primary key identity(1,1),
UName varchar(50),
UCity varchar(50),
UDob Date
)

create table Categories(
Cid int primary key identity(1,1),
CName varchar(50),
CDescription varchar(50)
)

create table Pages(
Pid int primary key identity(1,1),
PName varchar(50),
Cid int Foreign key references Categories(Cid)
)


create table Likes(
	Uid int references Users(Uid),
	Pid int references Pages(Pid),
	LikeDate date,
	Constraint pk_Like primary key(Uid, Pid)
)

create table Posts(
Poid int primary key identity(1,1),
PoDate date,
PoText varchar(50),
NoOfShares int,
Uid int foreign key references Users(Uid)
)

select * from Posts where Uid=1;

create table Comments(
	Coid int primary key identity(1,1),
	CoDate date,
	CoText varchar(50),
	CoFlagTop bit,
	Poid int Foreign key references Posts(Poid)
)

insert Users values('User1', 'city1', '10/10/2000'),
('User2', 'city2', '10/10/2000'),
('User3', 'city3', '10/10/2000')

insert Categories values('Category1', 'very interesting'),
('Category2', 'interesting')

insert Pages values('page1', 1),('page2',1)

insert Likes values(1,1,'2/21/2018'),(1,2,'6/7/2018'),(2,1,'2/3/2017')

insert Posts values('1/1/2018','post1', 3, 1), ('3/23/2018', 'post2', 5, 2)

insert Comments values('6/8/2019', 'comment1', 1,1),('6/9/2017', 'commmmmm', 0, 2)
go

select * from Users
select * from Categories
select * from Pages
select * from Likes
select * from Posts
select * from Comments



