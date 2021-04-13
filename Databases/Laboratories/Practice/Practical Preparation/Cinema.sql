create database Cinema
go

use Cinema
go

---- 1) Write an SQL script that creates the corresponding relational data model.

create table Company (
	CompanyId int primary key identity(1, 1),
	CName varchar(50)
)

create table Director(
	DirectorId int primary key identity(1, 1),
	DName varchar(50),
	NoOfAwards int 
)

create table Movie(
	MovieId int primary key identity(1, 1),
	MName varchar(50),
	ReleaseDate varchar(50),
	CompanyId int foreign key references Company(CompanyId),
	DirectorId int foreign key references Director(DirectorId)
)

create table Actor(
	ActorId int primary key identity(1, 1),
	AName varchar(50),
	Ranking int
)

create table Production(
	ProductionId int identity(1, 1),
	MovieId int foreign key references Movie(MovieId),
	ActorId int foreign key references Actor(ActorId),
	Title varchar(50),
	EntryMoment varchar(50)
	constraint pk_Production primary key(ProductionId, MovieId, ActorId)
)


--- populate tables:

insert into Actor values('a1', 10), ('a2', 10), ('a3', 9), ('a4', 8), ('a5', 10)

insert into Director values('d1', 3), ('d2', 4), ('d3', 2), ('d4', 3), ('d5', 10)

insert into Company values('c1'), ('c2'), ('c3'), ('c4')

insert into Movie values('m1', 'rd1', 1, 1), ('m2', 'rd2', 1, 2), ('m3', 'rd3', 2, 3), ('m4', 'rd4', 4, 5), ('m5', 'rd5', 3, 3)

insert into Production values(1, 1, 't1', 2), (1, 2, 't1', 1), (1, 3, 't1', 3), (2, 1, 't2', 1), (2, 3, 't2', 2), (3, 1, 't3', 1), (3, 5, 't3', 3)

select * from Actor
select * from Movie
select * from Company
select * from Production
select * from Director


--- 1) Create a stored procedure that receives an actor, an entry moment and a cinema production
--- and adds the new actor to the cinema production
go
create or alter proc Add_Production @ActorId int, @EntryMoment varchar(50), @ProductionId int
as
	declare @MovieId int;
	select @MovieId = p.MovieId from Production p where p.ProductionId = @ProductionId
	declare @Title varchar(50);
	select @Title = p.Title from Production p where p.ProductionId = @ProductionId

	insert into Production values(@MovieId, @ActorId, @Title, @EntryMoment)
go

select * from Production
exec Add_Production 1, 2, 1
select * from Production

--- 3) Create a view that shows the name of the actors that appear in all cinema productions

go
create or alter view vActors 
as
	select distinct x.ActorId from 
	(select distinct  p.MovieId, p.ActorId from Production p) x
	group by x.ActorId
	having count(x.MovieId) = (select count(x.MovieId) from (select distinct  p.MovieId from Production p) x)

go

select * from vActors


--- 4) Create a function that returns all movies that have the release date after '2018-01-01' and
--- have at least p productions, where p is a function parameter




