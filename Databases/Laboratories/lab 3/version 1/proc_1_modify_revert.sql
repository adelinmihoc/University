use OceanLife
go

create procedure proc_1_modify_revert
as
begin
print 'Modify the type of a column (Revert)'
alter table Oceans
alter column volume float
end

exec proc_1_modify_revert

drop procedure proc_1_modify_revert
