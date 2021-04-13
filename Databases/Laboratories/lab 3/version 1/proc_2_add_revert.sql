use OceanLife
go

create procedure proc_2_add_revert
as
begin
print 'Add revert'
alter table LivingBeing
drop column age
end

exec proc_2_add_revert

drop procedure proc_2_add_revert
 