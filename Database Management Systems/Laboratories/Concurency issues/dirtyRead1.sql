use MiniFacebook
go

Begin transaction
update Categories set CDescription='My Desctription'
where Cid = 2
waitfor delay '00:00:10'
rollback transaction


