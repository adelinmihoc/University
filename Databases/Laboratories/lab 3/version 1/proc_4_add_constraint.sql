use OceanLife
go

create procedure proc_4
as
begin
print 'Add constraint'
alter table LivingBeing
add behaviour varchar(50)
end

exec proc_2_remove_revert

drop procedure proc_2_remove_revert
 