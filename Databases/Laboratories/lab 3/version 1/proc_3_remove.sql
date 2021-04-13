use OceanLife
go

create procedure proc_2_remove
as
begin
print 'Remove column'
alter table LivingBeing
drop column behaviour
end

exec proc_2_remove

drop procedure proc_2_remove
 