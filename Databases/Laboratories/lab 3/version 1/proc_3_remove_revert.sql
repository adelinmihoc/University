use OceanLife
go

create procedure proc_3
as
begin
print 'Remove column revert'
alter table LivingBeing
add behaviour varchar(50)
end

exec proc_2_remove_revert

drop procedure proc_2_remove_revert
 