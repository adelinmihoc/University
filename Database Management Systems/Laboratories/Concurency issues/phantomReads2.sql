use MiniFacebook
go

set transaction isolation level serializable
begin tran
select * from Categories
waitfor delay '00:00:05'
select* from Categories
commit tran

/*
set transaction isolation level repeatable read
begin tran
select * from Categories
waitfor delay '00:00:05'
select * from Categories
commit tran
*/
