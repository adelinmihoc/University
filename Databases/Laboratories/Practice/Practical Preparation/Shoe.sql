create database Shoes
go 
use Shoes
go

create table Model(
	ModelId int primary key identity(1, 1),
	MName varchar(50),
	MSeason varchar(50)
)

create table Shoe(
	ShoeId int primary key identity(1, 1),
	SPrice float,
	SModel int foreign key references Model(ModelId)
)

create table Shop(
	ShopId int primary key identity(1, 1),
	SName varchar(50),
	SCity varchar(50)
)

create table Woman(
	WomanId int primary key identity(1, 1),
	WName varchar(50),
	AmountOfMoney float
)

create table ShoeShop(
	ShoeId int foreign key references Shoe(ShoeId),
	ShopId int foreign key references Shop(ShopId),
	AvailableShoes int
	constraint pk_ShoeShop primary key(ShoeId, ShopId)
)

create table ShoeWoman (
	ShoeId int foreign key references Shoe(ShoeId),
	WomanId int foreign key references Woman(WomanId),
	NoOfShoesBought int,
	SpentAmount float
	constraint pk_ShoeWoman primary key(ShoeId, WomanId)
)


insert into Model values('m1', 'vara'), ('m2', 'vara'), ('m3', 'iarna'), ('m4', 'iarna'), ('m5', 'toamna')

insert into Shoe values(150, 1), (250, 2), (350, 3), (450, 4), (550, 5)

insert into Shop values('n1', 'c1'), ('n2', 'c2'), ('n3', 'c3'), ('n4', 'c4')

insert into Woman values('w1', 1200), ('w2', 1400), ('w3', 5000), ('w4', 500), ('w5', 650)

insert into ShoeShop values(1, 1, 100), (1, 2, 50), (1, 3, 10), (3, 4, 100)

insert into ShoeWoman values(1, 1, 10, 1500), (1, 2, 2, 500), (2, 3, 1, 350)

select * from Model
select * from Shoe
select * from Shop
select * from Woman
select * from ShoeShop
select * from ShoeWoman

---- 2) Create a stored procedure that receives a shoe, a presentation shop and the number of shoes and
---- adds the shoe to the presentation shop

go
create or alter proc AddShoe @ShoeId int, @ShopId int, @noOfShoes int
as

	declare @nr int;
	set @nr = 0;
	select @nr = count(*) from ShoeShop ss where ss.ShoeId = @ShoeId and ss.ShopId = @ShopId
	
	if @nr <> 0 begin
		update ShoeShop
		set AvailableShoes = AvailableShoes + @noOfShoes
	end
	else begin
		insert into ShoeShop values(@ShoeId, @ShopId, @noOfShoes)
	end
go

select * from ShoeShop
exec AddShoe 2, 1, 100
select * from ShoeShop
exec AddShoe 2, 1, 50
select * from ShoeShop

--- 3) Create a view that shows the women that bought at least 2 shoes from a given shoe model.

go
create or alter view vWoman --- consider the model 2
as
	select w.WName, sw.NoOfShoesBought from ShoeWoman sw 
	inner join Woman w on sw.WomanId = w.WomanId 
	where sw.NoOfShoesBought >= 2
go

select * from vWoman

--- 4) Create afunction that lists the shoes that can be found in at least
--- T presentation shops, where T >= 1 is a function parameter

go
create or alter function uf_Shoes (@T int)
returns table
as
return
	select s.ShoeId, s.SModel, s.SPrice from
	(select distinct ss.ShoeId, ss.ShopId  from ShoeShop ss) x
	inner join Shoe s on x.ShoeId = s.ShoeId
	group by s.ShoeId, s.SModel, s.SPrice
	having count(x.ShoeId) >= @T
	
go

select * from uf_Shoes(2)