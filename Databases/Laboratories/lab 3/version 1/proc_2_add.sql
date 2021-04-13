use OceanLife
go

create procedure proc_2_add
as
begin
print 'Add a column'
alter table LivingBeing
add Age int
end

exec proc_2_add

drop procedure proc_2_add
