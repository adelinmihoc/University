use MiniFacebook
go

begin tran
waitfor delay '00:00:05'
Update Categories set CDescription='desctription nonrepeatable reads'
where Cid = 2
Commit tran
