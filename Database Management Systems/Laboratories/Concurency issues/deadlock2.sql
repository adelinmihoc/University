use MiniFacebook
go

begin tran
update Categories set CName='Category tran 2' where Cid=1
waitfor delay '00:00:10'
update Users set UCity='City tran 2' where Uid = 1
commit tran