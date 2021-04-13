create database TrainScheduler
go

use TrainScheduler
go

create table Stations (
	Sid int primary key identity(1, 1),
	SName varchar(50) unique
)

create table TrainTypes (
	Typeid int primary key identity(1, 1),
	Desctription varchar(50)
)

create table Trains (
	Tid int primary key identity(1,1),
	TName varchar(50),
	Typeid int foreign key references TrainTypes(Typeid)
)

create table Routes	(
	Rid int primary key identity(1, 1),
	RName varchar(50) unique,
	Tid int foreign key references Trains(Tid)
)

create table Stops ( ---RouteStations
	Rid int foreign key references Routes(Rid),
	Sid int foreign key references Stations(Sid),
	ArrivalTime time,
	DepartureTime time
	constraint pk_Stops primary key(Rid, Sid)
)

go


select * from TrainTypes
select * from Trains
select * from Stations
select * from Routes
select * from Stops


insert into TrainTypes values('description 1'), ('description 2')
insert into Trains values('InterRegio', 1), ('Intercity', 1), ('Regio', 2)
insert into Stations values('Cluj-Napoca'), ('Brasov'), ('Bucuresti')
insert into Routes values('Sighisoara', 1), ('Medias', 2)
insert into Stops values(1, 1, '12:00:00', '18:00:00'), (1, 2, '15:30:00', '22:42:00'), (2, 2, '08:05:00', '21:48:00')
go


---- Implement a stored procedure that receives a route, a station, arrival and departure times and adds the sation to the route.
---- If the station is already on the route, the arrival and departure times are updated

go 
create proc Add_stop @Rid int, @Sid int, @at time, @dt time
as
	declare @nr int;
	set @nr = 0;
	select @nr = COUNT(*) from Stops where Rid = @Rid and Sid = @Sid

	if (@nr <> 0) begin
		update Stops
		set ArrivalTime=@at, DepartureTime=@dt
		where Rid = @Rid and Sid=@Sid
	end
	else begin
		insert into Stops values(@Rid, @Sid, @at, @dt)
	end
go

---insert
select * from Stops
exec Add_stop 2, 1, '5:00:00', '9:00:00'
select * from Stops

---already inserted
select * from Stops
exec Add_stop 2, 1, '15:00:00', '19:00:00'
select * from Stops

---second version with names for Stations and Routes
go
create proc Add_RoutesStations_Names @RName varchar(50), @Sname varchar(50), @at time, @dt time
as
	declare @Rid int;
	declare @Sid int;

	select @Rid = Rid from Routes where Rname = @Rname
	select @Sid = Sid from Stations where SName = @Sname

	exec Add_stop @Rid, @Sid, @at, @dt
go

use TrainScheduler

--- 3) Create a view that shows the names of the routes that contain all the sations.
go
create view vRoutesStations
as
	select RName from Routes r inner join Stops ss on r.Rid = ss.Rid
	group by RName
	having count(*) = (select count(*) from Stations)
go

select * from Stations

select * from Stops

select * from Routes

select * from vRoutesStations

insert Stops values (1, 3, '12:00:00', '18:00:00')


--- 4) Create a function that lists the names of the stations with more than R routes, 
--- where R>=1 is a function parameter

go
create function uf_StationsRoutes(@r int)
returns table
as
return
	select distinct s.Sid, SName, count(SName) as NoOfRoutes
	from Stations s inner join Stops ss on ss.Sid = s.Sid
	group by s.Sid, SName
	having count(SName)>=@r
go

select * from uf_StationsRoutes(0)
select * from uf_StationsRoutes(2)
select * from uf_StationsRoutes(3)