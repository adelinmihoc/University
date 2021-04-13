use OceanLife
go

create procedure proc_1_modify
as
begin
print 'Modify the type of a column'
alter table Oceans
alter column volume int
end

exec proc_1_modify

drop procedure proc_1_modify
