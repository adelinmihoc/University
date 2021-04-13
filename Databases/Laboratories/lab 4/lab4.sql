use OceanLife
go

--------------------------------------------------
--			   	     Tables                     --
--------------------------------------------------

insert into Tables 
values 
('Orders'),
('Families'),
('Species'),
('Predators')

select * from Tables
go



--------------------------------------------------
--			   	     VIEWS                      --
--------------------------------------------------
go

--------------------first view--------------------
create view Orders_view as
select * from Orders
go

select * from Orders_view
go

----------------second view------------------------
create view Orders_Families_view as
select o.name as orders, f.name as family from Orders o full outer join Families f on f.Oname = o.name
go

select * from Orders_Families_view
go

drop view Orders_Families_view
go

-----------------third view-------------------------
create view Species_view as
select * from Species
go

select * from Species_view

-----------------fourth view-------------------------

select o.name, f.name, p.PredatorSpecies, p.PreySpecies
from Predators p full outer join (Orders o inner join Families f on f.Oname = o.name) on p.PredatorSpecies = '%'
group by o.name, f.name, p.PredatorSpecies, p.PreySpecies
go

create view Orders_Families_Predators_view as
select o.name as orders, f.name as families, p.PredatorSpecies, p.PreySpecies
from Predators p full outer join (Orders o inner join Families f on f.Oname = o.name) on p.PredatorSpecies = '%'
group by o.name, f.name, p.PredatorSpecies, p.PreySpecies
go

select * from Orders_Families_Predators_view

------------inserting into table Views---------------------
insert into Views
values
('Orders_view'),
('Orders_Families_view'),
('Species_view'),
('Orders_Families_Predators_view')

select * from Views


--------------------------------------------------
--			   	     Tests                      --
--------------------------------------------------

insert into Tests
values
('delete_table'), 
('insert_table'), 
('select_view')

select * from Tests


---------------------------------------------------
--			   	    TestTables                   --
---------------------------------------------------

insert into dbo.TestTables --delete from Orders 100 rows
values (1, 1, 1000, 4)

insert into dbo.TestTables --delete from Families 100 rows
values (1, 2, 1000, 3)

insert into dbo.TestTables --delete from Species 100 rows
values (1, 3, 1000, 2)

insert into dbo.TestTables --delete from Predators 100 rows
values (1, 4, 1000, 1)

------------------------------------------------------------

insert into dbo.TestTables --insert into Orders 100 rows
values (2, 1, 1000, 1)

insert into dbo.TestTables --insert into Families 100 rows
values (2, 2, 1000, 2)

insert into dbo.TestTables --insert into Families 100 rows
values (2, 3, 1000, 3)

insert into dbo.TestTables --insert into Predators 100 rows
values (2, 4, 1000, 4)

select * from dbo.TestTables

---------------------------------------------------
--Inserting data into tables so it can be deleted--
---------------------------------------------------

-----------------insert into Orders----------------
go
create proc insertOrders as
begin
declare @NoOfRows int
declare @n int
declare @t nvarchar(50)

select top 1 @NoOfRows = NoOfRows from dbo.TestTables t
where t.TestID = 1 and t.TableID = 1

set @n = 1

declare @printString nvarchar(50) = 'Inserting '
set @printString = @printString + CONVERT(nvarchar(50), @NoOfRows) + ' rows into Orders'
print @printString

while @n <= @NoOfRows
begin
	set @t = 'Order' + CONVERT(nvarchar(50), @n)
	begin 
		if not exists (select * from Orders where name = @t)
		begin
		insert into Orders values (@t)
		end
	end
	set @n = @n + 1
end
end

select * from Orders where name like 'Order%'
go

delete from Orders where name like 'Order%'

exec insertOrders

--drop proc insertOrders

-----------------insert into Families--------------
go
create proc insertFamilies as
begin
declare @fk nvarchar(50)
select top 1 @fk = name from Orders where name like 'Order%'
--print @fk

declare @NoOfRows int
declare @n int
declare @t nvarchar(50)
set @n = 1
select top 1 @NoOfRows = NoOfRows from dbo.TestTables t
where t.TestID = 1 and t.TableID = 2
declare @printString nvarchar(50) = 'Inserting '
set @printString = @printString + CONVERT(nvarchar(50), @NoOfRows) + ' rows into Families'
print @printString

while @n <= @NoOfRows
begin
	set @t = 'Family' + CONVERT(nvarchar(50), @n)
	if not exists (select * from Families where name = @t)
	begin
		insert into Families values (@t, @fk)
	end
	set @n = @n + 1
end
end

select * from Families where name like 'Family%'
go

exec insertFamilies

--drop proc insertFamilies

----------------*insert into Genera*--------------- not used in actual tests

go
create proc insertGenera as
begin
declare @fk nvarchar(50)
select top 1 @fk = name from Families where name like 'Family%'
--print @fk

print 'Inserting into Genera'

if not exists (select * from Genera where name = 'Genera1')
begin
	insert into Genera values ('Genera1', @fk, 0)
end
end

select * from Genera where name like 'Genera%'
go

exec insertGenera

--drop proc insertGenera

------------*insert into AquaticRespiration-------- not used in actual tests

go
create proc insertRespiration as
begin
if not exists (select * from AquaticRespiration where respiratorySystem = 'Respiration1')
begin
	insert into AquaticRespiration values ('Respiration1', '')
end
end

select * from AquaticRespiration where respiratorySystem like 'Respiration%'
go

exec insertRespiration

--drop proc insertRespiration

-----------------insert into Species--------------- 

go
create proc insertSpecies as
begin
declare @fk nvarchar(50)
select top 1 @fk = name from Genera where name like 'Genera%'
--print @fk
declare @fk1 nvarchar(50)
select top 1 @fk1 = respiratorySystem from AquaticRespiration where respiratorySystem like 'Respiration%'
--print @fk1

declare @n int
set @n = 1

declare @NoOfRows int
select top 1 @NoOfRows = NoOfRows from dbo.TestTables t
where t.TestID = 1 and t.TableID = 3
--print @NoOfRows

declare @t nvarchar(50)

while @n <= @NoOfRows
begin 
	set @t = 'Species' + CONVERT(nvarchar(50), @n)
	if not exists (select * from Species where name = @t)
	begin
		insert into Species values (@t, @fk, @fk1)
	end
	set @n = @n + 1
end
print 'Inserting into Species'
if not exists (select * from Species where name = 'Species1')
begin
	insert into Species values ('Species1', @fk, @fk1)
end
end


select * from Species where name like 'Species%'
go

exec insertSpecies

--drop proc insertSpecies

-----------------insert into Predators-------------
go
create proc insertPredators as
begin
declare @m int
select top 1 @m = NoOfRows from dbo.TestTables t
where t.TestID = 1 and t.TableID = 3
--print @m

declare @n int
set @n = 1

declare @pk nvarchar(50)
declare @pk1 nvarchar(50)

select top 1 @pk1 = name from Species where name like 'Species%'
--print @pk1

print 'Inserting into Predators'

while @n < @m
begin
	select top (@n) @pk = name from Species where name like 'Species%'
	set @n = @n + 1
	--print @pk
	if not exists (select * from Predators where PredatorSpecies = @pk1 and PreySpecies = @pk)
	begin
		insert into Predators values (@pk1, @pk)
	end
end
end

select * from Predators where PredatorSpecies like 'Species%'

exec insertPredators

--drop proc insertPredators

---------------------------------------------------
--			   	      TestViews                  --
---------------------------------------------------

insert into TestViews
values (3, 1)

insert into TestViews
values (3, 2)

insert into TestViews
values (3, 3)

select * from TestViews


---------------------------------------------------
--			   	      TestRuns                   --
---------------------------------------------------

exec insertOrders
exec insertFamilies
exec insertGenera
exec insertRespiration
exec insertSpecies
exec insertPredators

---- * Deletes all from Table t (and from all the other tables which have position < t.position)
---- * Inserts all into Table t (and in all the other tables which have position < t.position)
---- * Selects the view v for Table t (v.viewId = t.TableID)
go
create proc TestAll as
begin
	set nocount on
	declare @max_tableID int ----last table id
	select @max_tableID = max(TableID) from TestTables
	--print @max_tableID

	declare @current_tableID int
	set @current_tableID = 1 ---- first table id
	--print @current_tableID

	---- Testing each table
	while @current_tableID <= @max_tableID 
	begin
		---- insertion part to fill the gaps between tests
		begin try
			exec insertOrders
			exec insertFamilies
			exec insertGenera
			exec insertRespiration
			exec insertSpecies
			exec insertPredators
		end try
		begin catch
			
		end catch

		declare @current_tableName nvarchar(50)
		select @current_tableName = t.Name from Tables t where TableID = @current_tableID
		print 'Testing table '  + @current_tableName
		declare @description nvarchar(50)
		set @description = 'Testing table ' + @current_tableName
		
		declare @ds datetime
		declare @di datetime
		declare @de datetime

		declare @current_operation int
		set @current_operation = 1 --delete operation

		---- Performing all operation (delete & insert & select)
		while @current_operation <= 3
		begin 
			declare @current_operationName nvarchar(50)
			select @current_operationName = t.Name from Tests t where TestID = @current_operation
			print '		Now performing the ' + @current_operationName + ' operation'


			-------------------------------------------------------
			if @current_operation < 3 ---- working with TestTables
			begin
				print '			Working with TestTables'
				set @ds = getdate()

				 
				declare @current_NoOfRows int
				select @current_NoOfRows = TestTables.NoOfRows from TestTables
				where TestTables.TableID = @current_tableID and TestTables.TestID = @current_operation
				--print @current_NoOFRows

				declare @position int
				select @position = TestTables.Position from TestTables
				where TestTables.TableID = @current_tableID and TestTables.TestID = @current_operation
				--print @current_position
				declare @current_position int
				set @current_position = 1
				
				while @current_position <= @position ----first we need to perform the operation on the other tables
				begin
					declare @table_id int
					select @table_id = TestTables.TableID from TestTables 
					where TestTables.Position = @current_position and TestTables.TestID = @current_operation
					declare @table_name nvarchar(50)
					select @table_name = Tables.Name from Tables
					where Tables.TableID = @table_id
					--print @table_name


					if @current_operation = 1 ----delete
					begin 
						print '				Deleting from ' + @table_name

						if @table_name = 'Predators'
						begin 
							delete from Predators where PredatorSpecies like '%[0-9]'
						end ---- end if

						if @table_name != 'Predators'
						begin
							declare @delete_from_table nvarchar(50)
							set @delete_from_table = 'delete from ' + @table_name + ' where name like ''' + '%[0-9]'''
							---print @delete_from_table

							if @table_name = 'Families'
							begin
								delete from Genera where name = 'Genera1'
							end 

							exec (@delete_from_table)
						end ---- end if
					end ---- end if

					if @current_operation = 2
					begin
						print '					Inserting into ' + @table_name
												
						if @table_name = 'Orders'
						begin
							exec insertOrders
						end
						if @table_name = 'Families'
						begin
							exec insertFamilies
						end
						if @table_name = 'Species'
						begin
							exec insertGenera
							exec insertSpecies
						end
						if @table_name = 'Predators'
						begin
							exec insertPredators
						end
					end

					set @current_position = @current_position + 1
				end ----end third while


			end ----end if
			-------------------------------------------------------
			set @di = GETDATE()

			-------------------------------------------------------
			if @current_operation = 3 ---- working with TestViews
			begin
				print '			Working with TestViews'
				declare @current_viewName nvarchar(50)
				select @current_viewName = Views.name from Views where Views.ViewID = @current_tableID
				print '				' + @current_viewName
				declare @select_view nvarchar(50)
				set @select_view = 'select * from ' + @current_viewName
				exec (@select_view) 
				set @de = GETDATE()
			end ----end if
			-------------------------------------------------------


			set @current_operation = @current_operation + 1 ----go to next operation
		end ----end second while

		insert into TestRuns values
		(@description, @ds, @de)

		declare @testRunID int
		select @testRunID = max(TestRunID) from TestRuns

		insert into TestRunTables values
		(@testRunID, @current_tableID, @ds, @di)

		insert into TestRunViews values
		(@testRunID, @current_tableID, @di, @de)

		 
		set @current_tableID = @current_tableID + 1 ----go to next table
	end ----end first while

end ---- end store procedure

exec TestAll
drop proc TestAll

select * from TestRuns
select  *from TestRunTables
select * from TestRunViews

delete from TestRunTables where TestRunID < 100
delete from TestRunViews where TestRunId < 100
delete from TestRuns where TestRunID < 100