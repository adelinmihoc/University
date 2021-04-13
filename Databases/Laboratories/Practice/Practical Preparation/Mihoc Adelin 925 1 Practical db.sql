create database Practical
go
use Practical
go


--- 1)

create table Resources(
	RID int primary key identity(1, 1),
	Rurl varchar(50)
)

create table Topics(
	TID int primary key identity(1, 1),
	TName varchar(50)
)

create table Courses(
	CID int primary key identity(1, 1),
	CTitle varchar(50),
	CLanguage varchar(50),
	CPrice float,
	CDiscount int,
	NoOfLectures int,
	TID int foreign key references Topics(TID)
)

create table Companies(
	CID int primary key identity(1, 1),
	CName varchar(50),
	CTurnover varchar(50),
	CDescription varchar(50)
)

create table CourseCompany(
	CourseID int foreign key references Courses(CID),
	CompID int foreign key references Companies(CID)
	constraint pk_CourComp primary key(CourseID, CompID)
)

create table Lectures(
	LID int primary key identity(1, 1),
	LTitle varchar(50),
	CID int foreign key references Courses(CID)
)

create table LectResources(
	LID int foreign key references Lectures(LID),
	RID int foreign key references Resources(RID)
	constraint pk_LectRes primary key(LID, RID)
)


--- populate tables

insert into Resources values('r1'), ('r2'), ('r3')

insert into Companies values('c1', 't1', 'd1'), ('c2', 't2', 'd2'), ('c3', 't3', 'd3')

insert into Topics values('t1'), ('t2'), ('t3'), ('t4')

insert into Courses values('c1', 'l1', 100, 0, 10, 1),
('c2', 'l2', 200, 0, 10, 2), ('c3', 'l3', 150, 0, 10, 1), ('c4', 'l4', 350, 0, 10, 4)

insert into CourseCompany values(1, 1),(2, 1), (1, 3)

insert into Lectures values('l1', 1), ('l2', 1), ('l3', 2), ('l4', 1)

insert into LectResources values(1, 1),(1, 2)


---b. Implement a stored procedure that receives a company and a course as parameters, 
--and adds the course to the company. 
--If the company is already associated with the course, 
--a warning message is displayed to the user.

go
create or alter proc Add_course @CompId int, @CoursId int
as
	declare @nr int;
	set @nr = 0;

	select @nr = count(*) from CourseCompany where @CompId = CompID and @CoursId = CourseID
	
	if @nr <> 0 begin
		print 'Company already associated with the course'
	end
	else begin
		insert into CourseCompany values(@CoursId, @CompId)
	end

go

exec Add_course 1, 1
select * from CourseCompany
exec Add_course 1, 3
select * from CourseCompany


---c. Create a view that shows the names of the companies that offer at least 20 courses
---with a price that's lower than the average price for all courses 
---(consider the original price for each course, not the discounted price).

go
create or alter view cComp
as
	select c2.CName from 
	(
	select * from
	(select x.CompID, x.CourseID from 
	(select distinct cc.CompID, cc.CourseID from CourseCompany cc)x
	group by x.CompID, x.CourseID
	having COUNT(x.CompID) >= 20 ) t inner join Courses c on c.CID = t.CourseID
	where c.CPrice < (select avg(c1.CPrice) from Courses c1) 
	) t1 inner join Companies c2 on c2.CID = t1.CompID
go

select * from cComp


---d. Implement a function that returns the names of the companies that offer less than C 
---courses, where C is a function parameter.

go
create or alter function uf_Comp(@C int)
returns table
as
return 
	select c.CName from
	(select x.CompID from
	(select distinct cc.CompID, cc.CourseID from CourseCompany cc)x
	group by x.CompID
	having COUNT(*) < @C ) t 
	inner join Companies c on c.CID = t.CompID
go


select * from uf_Comp(10)


