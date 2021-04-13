create database CakeStore
go
use CakeStore
go


--- 1) Write an SQL script that creates the corresponding relational data model.

create table Chefs(
	ChefId int primary key identity(1, 1),
	CName varchar(50),
	Gender varchar(50),
	DateOfBirth varchar(50)
)

create table Orders(
	OrderId int primary key identity(1, 1),
	ODate varchar(50)
)

create table CakeTypes(
	CakeTypeId int primary key identity(1, 1),
	CTName varchar(50),
	CTDescription varchar(50)
)

create table Cakes(
	CakeId int primary key identity(1, 1),
	CName varchar(50),
	CShape varchar(50),
	CWeight float,
	CPrice float,
	CTypeId int foreign key references CakeTypes(CakeTypeId)
)


create table ChefsCakes(
	ChefId int foreign key references Chefs(ChefId),
	CakeId int foreign key references Cakes(CakeId)
	constraint pk_ChefsCakes primary key(ChefId, CakeId)
)

create table CakesOrders(
	OrderId int foreign key references Orders(OrderId),
	CakeId int foreign key references Cakes(CakeId),
	Pieces int
	constraint pk_CakesOrders primary key(OrderId, CakeId)
)


--- populate tables

insert into CakeTypes values('t1', 'd1'), ('t2', 'd2'), ('t3', 'd3'), ('t4', 'd4')

insert into Cakes values('n1', 's1', 100, 100, 1), ('n2', 's2', 50, 50, 2), 
('n3', 's3', 150, 150, 3), ('n4', 's4', 250, 250, 4), ('n5', 's5', 350, 350, 1)

insert into Chefs values('c1', 'm', ''), ('c2', 'f', ''), ('c3', 'm', ''), ('c4', 'm', '')

insert into Orders values('d1'), ('d2'), ('d3'), ('d4'), ('d5')

insert into ChefsCakes values(1, 1), (1, 2), (1, 3), (1, 4), (2, 1), (2, 3), (3, 4), (4, 3)

insert into CakesOrders values(1, 1, 3), (1, 2, 2), (2, 1, 3), (3, 4, 10)


--- 2) Implement a stored prodcedure that receives an order ID, a cake anme, and a positive
--- number P representing the number of ordered pieces, and adds the cake to the order.
--- If the cake is already on the order, the number of ordered pieces is set to P

go
create or alter proc Add_Order @OId int, @CName varchar(50), @P int
as
	declare @nr int;
	set @nr = 0;

	declare @CakeId int;
	set @CakeId = 0;
	select @CakeId = c.CakeId from Cakes c where c.CName = @CName

	select @nr = count(*) from CakesOrders co where co.OrderId = @OId and co.CakeId = @CakeId

	if @nr <> 0 begin
		update CakesOrders 
		set Pieces = Pieces + @P
		where OrderId = @OId and CakeId = @CakeId
	end
	else begin 
		insert into CakesOrders values(@OId, @CakeId, @P)
	end
go

select * from CakesOrders
exec Add_Order 1, 'n1', 1
select * from CakesOrders
exec Add_Order 2, 'n2', 1
select * from CakesOrders

---3) Implement a function that lists the names of the chefs who are specialized in the
--- preparation of all the cakes

go
create or alter function uf_Chefs()
returns table
as
return
	select x.ChefId from
	(select * from ChefsCakes) x
	group by x.ChefId
	having count(x.ChefId) = (select count(*) from Cakes)
go

select* from uf_Chefs()