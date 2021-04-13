create database musical
go

use musical
go

create table Category(
	CID int primary key identity(1, 1),
	Cname varchar(50)
)


create table Subcategory(
	SID int primary key identity(1, 1),
	SName varchar(50),
	CategoryID int foreign key references Category(CID)
)

create table Instrument(
	IID int primary key identity(1,1),
	subcategoryID int foreign key references Subcategory(SID)
)

create table Customer(
	CID int primary key identity(1,1),
	CName varchar(50),
)

create table Orders(
	OID int primary key identity(1,1),
	CustomerID int foreign key references Customer(CID)
)

create table OrderSubcategory(
	OID int foreign key references Orders(OID),
	SID int foreign key references Subcategory(SID),
	no_of_instruments int,
	color varchar(50)
	constraint pk_OS primary key (OID,SID)
)



insert into Category values('c1'),('c2'),('c3')

insert into Subcategory values('s1',1),('s2',1),('s3',2),('s4', 3)

insert into Customer values ('o'),('o'),('a'),('b')

insert into Orders values(1),(1),(1),(2),(2),(3)

insert into OrderSubcategory values(1,1,10,'r')

select * from Category c1 full outer join Category c2 on c1.Cname = c2.CID 

create table S (
	ID1 int,
	ID2 int,
	c1 int,
	c2 int,
	c3 int,
	c4 int,
	c5 int
	constraint pk_S primary key (ID1, ID2)
)

insert into S values
(23,1,4,8,4,9,3),
(24,1,4,7,5,9,3),
(24,5,2,7,6,9,3),
(24,6,1,7,7,9,3),
(25,1,2,5,8,8,3),
(25,2,2,5,10,8,4),
(25,3,1,5,9,8,4),
(26,1,1,5,11,8,4),
(100,1,5,2,1,10,1),
(100,2,5,8,2,9,2),
(100,3,5,8,3,9,2)


select * from S

select s1.ID1, count(*) N
from S s1 inner join S s2 on s1.c1=s2.c2
group by s1.ID1
having count(*) > 1
intersect
select s1.ID1, count(*) N
from S s1 left join S s2 on s1.c1 = s2.c2
group by s1.ID1
having count(*) < 3


select * from S s1, S s2
where s1.C > ANY(select D from S)



