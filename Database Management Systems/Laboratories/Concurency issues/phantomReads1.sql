use MiniFacebook
go

begin tran
waitfor delay '00:00:05'
insert into Categories(CName, CDescription)
values ('Phantom', 'Phantom description')
commit tran