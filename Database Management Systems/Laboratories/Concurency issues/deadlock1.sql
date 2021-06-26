use MiniFacebook
go

set deadlock_priority high
begin tran
update Users set UCity='City tran 1' where Uid = 1
waitfor delay '00:00:10'
update Categories set CName='Category tran 1' where Cid=1
commit tran
