use MiniFacebook
go

set transaction isolation level read committed
begin tran
select * from Categories
waitfor delay '00:00:15'
select * from Categories
Commit tran