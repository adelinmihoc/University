use OceanLife
go

create table database_version (        
id int not null primary key,
operation nvarchar(500) not null,
revert_operation nvarchar(500) not null
)

insert into database_version values (0, '', '') 
select * from database_version
go


create procedure modify_column_type 
@table_name nvarchar(500),
@col_name nvarchar(500),
@col_type nvarchar(500)
as
begin
print 'Modifying a column type!'
declare @operation nvarchar(500) = 'alter table ' + @table_name + ' alter column ' + @col_name + ' ' + @col_type
print @operation
declare @revert_operation nvarchar(500) = 'alter table ' + @table_name + ' alter column ' + @col_name + ' ' + (select data_type from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME = @table_name and COLUMN_NAME = @col_name)
print @revert_operation
insert into database_version values(1, @operation, @revert_operation)
end
go


create procedure add_column
@table_name nvarchar(500),
@col_name nvarchar(500),
@col_type nvarchar(500)
as
begin
print 'Adding a column'
declare @operation nvarchar(500) = 'alter table ' + @table_name + ' add ' + @col_name + ' ' + @col_type
print @operation
declare @revert_operation nvarchar(500) = 'alter table ' + @table_name + ' drop column ' + @col_name
print @revert_operation
insert into database_version values(2, @operation, @revert_operation)
end
go


create procedure add_default_constraint
@table_name nvarchar(500),
@col_name nvarchar(500),
@constr_name nvarchar(500),
@constr_value nvarchar(500)
as
begin
print 'Adding a default constraint'
declare @operation nvarchar(500) = 'alter table ' + @table_name + ' add constraint ' + @constr_name + ' default ' + @constr_value + ' for ' + @col_name
print @operation
declare @revert_operation nvarchar(500) = 'alter table ' + @table_name + ' drop constraint ' + @constr_name
print @revert_operation
insert into database_version values(3, @operation, @revert_operation)
end
go


create procedure add_primary_key
@table_name nvarchar(500),
@col_name nvarchar(500),
@constr_name nvarchar(500)
as
begin
print 'Adding a primary key'
declare @operation nvarchar(500) = 'alter table ' + @table_name + ' add constraint ' + @constr_name + ' primary key(' + @col_name + ')'
print @operation
declare @revert_operation nvarchar(500) = 'alter table ' + @table_name + ' drop constraint ' + @constr_name
print @revert_operation
insert into database_version values(4, @operation, @revert_operation)
end
go


create procedure add_candidate_key
@table_name nvarchar(500),
@col_name nvarchar(500),
@constr_name nvarchar(500)
as
begin
print 'Adding a candidate key'
declare @operation nvarchar(500) = 'alter table ' + @table_name + ' add constraint ' + @constr_name + ' unique(' + @col_name + ')'
print @operation 
declare @revert_operation nvarchar(500) = 'alter table ' + @table_name + ' drop constraint ' + @constr_name
print @revert_operation
insert into database_version values(5, @operation, @revert_operation)
end
go


create procedure add_foreign_key
@table_name nvarchar(500),
@constr_name nvarchar(500),
@col_name nvarchar(500),
@ref_table_name nvarchar(500),
@ref_col_name nvarchar(500)
as
begin
print 'Adding a foreign key'
declare @operation nvarchar(500) = 'alter table ' + @table_name + ' add constraint ' + @constr_name + ' foreign key(' + @col_name + ') references ' + @ref_table_name + '(' + @ref_col_name + ')'
print @operation
declare @revert_operation nvarchar(500) = 'alter table ' + @table_name + ' drop constraint ' + @constr_name
print @revert_operation
insert into database_version values(6, @operation, @revert_operation)
end
go


create procedure create_table
@table_name nvarchar(500),
@primary_key_name nvarchar(500),
@primary_key_type nvarchar(500)
as begin
print 'Creating a new table'
declare @operation nvarchar(500) = 'create table ' + @table_name + ' ( ' + @primary_key_name + ' ' + @primary_key_type + ' primary key )'
print @operation
declare @revert_operation nvarchar(500) = 'drop table ' + @table_name
print @revert_operation 
insert into database_version values(7, @operation, @revert_operation)
end
go


create table Fish (
sname varchar(50) not null
)

drop table Fish


--version 1
exec modify_column_type 'Oceans', 'area', 'int'
--version 2
exec add_column 'Oceans', 'new_col', 'int'
--version 3
exec add_default_constraint 'Ecosystems', 'eArea', 'def_eAr', '0'
--version 4
exec add_primary_key 'Fish', 'sname', 'pr_ke'
--version 5
exec add_candidate_key 'Oceans', 'oLocation', 'cand_ke'
--version 6
exec add_foreign_key 'Fish', 'for_ke_F_S', 'sname', 'Species', 'name'
--version 7
exec create_table 'New_table', 'id', 'int'


select * from database_version
go


create procedure main
@version int,
@@current_version int output
as
begin
print 'Changing version'

declare @max_v int = (select max(id) from database_version)
if @version > @max_v or @version < 0
	begin
		print 'Invalid version'
		return
	end

if @@current_version <= @version
	begin
		while @@current_version < @version
			begin
				declare @operation nvarchar(500) = (select operation from database_version where id = @@current_version + 1)
				exec sp_executesql @operation
				print @operation
				set @@current_version = @@current_version + 1
			end
	end
else
	begin
		while @@current_version > @version
			begin
				declare @revert_operation nvarchar(500) = (select revert_operation from database_version where id = @@current_version)
				exec sp_executesql @revert_operation
				print @revert_operation
				set @@current_version = @@current_version - 1
			end
	end
end
go

--------------------------------------------------------------------
--------------------------------------------------------------------
declare @@current_v int
set @@current_v = 0
print @@current_v

exec main 4, @@current_v output
print @@current_v

exec main 1, @@current_v output
print @@current_v

exec main 0, @@current_v output
print @@current_v

exec main 7, @@current_v output
print @@current_v

exec main 0, @@current_v output
print @@current_v

exec main 0,1

--------------------------------------------------------------------
--------------------------------------------------------------------




drop procedure main

--procedures drops
drop procedure modify_column_type
drop procedure add_column
drop procedure add_default_constraint
drop procedure add_candidate_key
drop procedure add_primary_key
drop procedure add_foreign_key
drop procedure create_table


