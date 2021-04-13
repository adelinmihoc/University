use OceanLife
go

---- Create 3 tables Ta(*aid,a2-unique) Tb(*bid, b2) Tc(*cid, aid, bid)

create table Researcher ( --Ta
Rid int primary key identity, --aid
Rname nvarchar(50), 
studies nvarchar(50),
certificateId int unique --a2
)

create table Project ( --Tb
Pid int primary key identity, --bid
Pname nvarchar(50),
description nvarchar(50),
toatalCost int --bd
)
 
create table ResearchProject ( --Tc
RPid int primary key identity, --cid
Rid int foreign key references Researcher(Rid), --aid
Pid int foreign key references Project(Pid) --bid
)

/*
drop Table ResearchProject
drop Table Researcher
drop Table Project
*/
---- tables insertion
insert into Researcher values
('George', 'UBB', 1098),
('Mary','UBB',2057),
('Andrew','UAIC',1145),
('Anna', 'MIT', 9987),
('Noah', 'UOO', 5478),
('Liam', 'SU', 7349),
('Emma', 'UOO', 3498),
('Olivia', 'MIT', 1923),
('William', 'HU', 2873),
('Mason', 'SU', 1234)

insert into Project values
('Marine Species Database', '', 100000),
('Marine Conservation Information', '', 250000),
('Marine Life Sciences', '', 57000),
('Ocean Online Communitites', '', 5000000),
('Planet Ocean Content', '', 90000)

insert into ResearchProject values
(1, 1),
(2, 1),
(3, 1),
(4, 2),
(5, 2),
(6, 3),
(7, 4),
(8, 4),
(9, 5),
(10, 5)

---- insert more in tables
declare @n int
set @n = 10000
declare @m int
set @m = 10799

while @n < 10800
begin
	if @n % 2 = 0
		begin
		declare @name nvarchar(50) = 'Name' + cast(@n as nvarchar)
		declare @studies nvarchar(50) = 'Studies' + cast(@n as nvarchar)
		insert into Researcher values (@name, @studies, @n)
	end
	if @n % 2 = 1
	begin
		declare @name1 nvarchar(50) = 'Name' + cast(@m as nvarchar)
		declare @studies1 nvarchar(50) = 'Studies' + cast(@m as nvarchar)
		insert into Researcher values (@name1, @studies1, @m)
		set @m = @m - 2
	end
	set @n = @n + 1
end

/*
delete from Researcher where Rid > 10
*/

---- select * from tables

select * from Researcher
select * from Project
select * from ResearchProject

------------------------------------
----------*Indexes delete*----------
if exists (select name from sys.indexes where name = N'N_idx_Studies')
	drop index N_idx_Studies on Researcher
go
if exists (select name from sys.indexes where name = N'N_idx_Name')
	drop index N_idx_Name on Researcher
go
if exists (select name from sys.indexes where name = N'N_idx_TotalCost')
	drop index N_idx_TotalCost on Project
go
------------------------------------

----===============================================================================================================----


----a. Write 5 querries on Ta such that their corresponding execution plans the following operators:
----	-clustered index scan
----	-clustered index seek
----	-nonclustered index scan 
----	-nonclustered index seek
----	-key lookup

----------*Clustered index scan*----------
select * from Researcher order by Rid ----On Rid there is a clustered index

select * from Researcher order by studies 

select * from Researcher order by certificateId ----On certificateId there is a unique index

----------*Clustered index seek*----------
select Rid, Rname from Researcher where Rid between 10 and 30

----------*Nonclustered index scan*----------
if exists (select name from sys.indexes where name = N'N_idx_Studies')
	drop index N_idx_Studies on Researcher
go
create nonclustered index N_idx_Studies on Researcher(studies)
go
select studies from Researcher order by studies

----------*Nonclustered index seek and key lookup*----------
if exists (select name from sys.indexes where name = N'N_idx_Name')
	drop index N_idx_Name on Researcher
go
create nonclustered index N_idx_Name on Researcher(Rname)
go

select Rid, RName from Researcher where Rname = 'Name10700' or Rname = 'Name10799' order by studies


---- testing awith different fields in select
if exists (select name from sys.indexes where name = N'N_idx_Studies')
	drop index N_idx_Studies on Researcher
go
if exists (select name from sys.indexes where name = N'N_idx_Name')
	drop index N_idx_Name on Researcher
go
----1 Primary key
select Rid from Researcher ----index scan nonclustered
select Rid from Researcher order by studies ----index scan clustered

----2 Primary key + field with nonclustered index
if exists (select name from sys.indexes where name = N'N_idx_Name')
	drop index N_idx_Name on Researcher
go
create nonclustered index N_idx_Name on Researcher(Rname)
go
select Rid, Rname from Researcher ----index scan nonclustered
select Rid, Rname from Researcher order by Rname ----index scan nonclustered
select Rid, Rname from Researcher order by studies ----index scan clustered

----3 Primary key + field that has no nonclustered index on it
select Rid, studies from Researcher ----index scan clustered
select Rid, studies from Researcher order by studies ----index scan clustered
select Rid, studies from Researcher order by  Rname ----index scan clustered

----4 The field with nonclustered index
if exists (select name from sys.indexes where name = N'N_idx_Name')
	drop index N_idx_Name on Researcher
go
create nonclustered index N_idx_Name on Researcher(Rname)
go
select Rname from Researcher ----index scan nonclustered
select Rname from Researcher order by Rname ----index scan nonclustered
select Rname from Researcher order by studies ----index scan clustered
select Rname from Researcher order by Rid ----index scan clustered

----5 The field with noncluserd index + the primary key + a field with nonclustered index created on it
if exists (select name from sys.indexes where name = N'N_idx_Name')
	drop index N_idx_Name on Researcher
go
create nonclustered index N_idx_Name on Researcher(Rname)
go
if exists (select name from sys.indexes where name = N'N_idx_Studies')
	drop index N_idx_Studies on Researcher
go
create nonclustered index N_idx_Studies on Researcher(studies)
go
select Rname, Rid, studies from Researcher



-- check the indexes (nonclustered) for the database used
SELECT TableName = t.name, IndexName = ind.name, IndexId = ind.index_id, ColumnId = ic.index_column_id, ColumnName = col.name, ind.*, ic.*, col.* 
FROM sys.indexes ind INNER JOIN sys.index_columns ic ON ind.object_id = ic.object_id and ind.index_id = ic.index_id
INNER JOIN sys.columns col ON ic.object_id = col.object_id and ic.column_id = col.column_id 
INNER JOIN sys.tables t ON ind.object_id = t.object_id
WHERE ind.is_primary_key = 0 AND ind.is_unique = 0 AND ind.is_unique_constraint = 0 
	AND t.is_ms_shipped = 0 
ORDER BY t.name, ind.name, ind.index_id, ic.index_column_id;

-- all the indexes from table Researcher
select i2.name, i1.user_scans, i1.user_seeks, i1.user_updates,i1.last_user_scan,i1.last_user_seek, i1.last_user_update 
from sys.dm_db_index_usage_stats i1 
inner join sys.indexes i2 on i1.index_id = i2.index_id
where i1.object_id = OBJECT_ID('Researcher') and i1.object_id = i2.object_id
 
-- all the indexes from the current database
SELECT OBJECT_NAME(A.[OBJECT_ID]) AS [OBJECT NAME], I.[NAME] 
	AS [INDEX NAME], A.LEAF_INSERT_COUNT, A.LEAF_UPDATE_COUNT, A.LEAF_DELETE_COUNT 
FROM SYS.DM_DB_INDEX_OPERATIONAL_STATS (NULL,NULL,NULL,NULL ) A
	INNER JOIN SYS.INDEXES AS I ON I.[OBJECT_ID] = A.[OBJECT_ID] AND I.INDEX_ID = A.INDEX_ID 
	WHERE OBJECTPROPERTY(A.[OBJECT_ID],'IsUserTable') = 1

----===============================================================================================================----

----b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan.
---- Create a nonclustered index that can speed up the query.
---- Recheck the query's exectuion plan (operators, SELECTs estimated subtree cost).

----insert into Project----

declare @n int
set @n = 10

while @n < 850
begin
	declare @name nvarchar(50) = 'Name' + cast(@n as nvarchar)
	declare @descr nvarchar(50) = 'Descr' + cast(@n as nvarchar)
	insert into Project values (@name, @descr, @n)
	set @n = @n + 1
end

select * from Project

----write a query with WHERE b2 = value
select * from Project where toatalCost = 70 
----analyze: operator cost = 0.0087637 (100%)
----		 subtree cost = 0.0087637

----create nonclustered index to speed up query
if exists (select name from sys.indexes where name = N'N_idx_TotalCost')
	drop index N_idx_TotalCost on Project
go
create nonclustered index N_idx_TotalCost on Project(toatalCost)
go

select * from Project where toatalCost = 70 ----index seek nonclustered
----analyze: operator cost = 0.0032842 (40%)
----		 subtree cost = 0.0032842

----===============================================================================================================----

----c. Create a view that joins at least 2 tables. 
---- Check wheather existing indexes are helpful.
---- If not reassess existing indexes / examin the cardinality if the tables

declare @n int --- for ProjectId
set @n = 6 --- < 943
declare @m int --- for ResearchId
set @m = 1265 --- < 2164

while @m < 1400
begin
	while @n < 106
	begin
		insert into ResearchProject values (@m, @n)
		set @n = @n + 1
	end
	set @m = @m + 1
end

select * from Researcher
select * from Project
select * from ResearchProject

go
create or alter view v1 as
	select r.Rid, r.Rname, r.studies, r.certificateId, rp.RPid, rp.Pid from Researcher as r inner join ResearchProject as rp on rp.Rid = r.Rid
	where r.Rid between 1 and 3000
go

select v1.Rid, v1.Pid, v1.Rname, v1.studies, v1.certificateId from v1 where v1.Rname = 'Name10000' and v1.Pid between 0 and 100
--- operator cost for already created nonclustered indexes = 0.0032831

if exists (select name from sys.indexes where name = N'N_idx_Rid')
	drop index N_idx_Rid on ResearchProject
go
create nonclustered index N_idx_Rid on ResearchProject(Rid)
go

if exists (select name from sys.indexes where name = N'N_idx_Pid')
	drop index N_idx_Pid on ResearchProject
go
create nonclustered index N_idx_Pid on ResearchProject(Pid)
go

select v1.Rid, v1.Pid, v1.Rname, v1.studies, v1.certificateId from v1 where v1.Rname = 'Name10000' and v1.Pid between 0 and 100

select v1.Rid, v1.Pid, v1.Rname, v1.studies, v1.certificateId from v1 where v1.Rname = 'Name10000' order by v1.Pid
--- for the new nonclustered indexes operator cost = 0.003343  (new ones)
-------------------------------------------------- = 0.0032831 (the old ones)
--- so tyhe old ones are better
