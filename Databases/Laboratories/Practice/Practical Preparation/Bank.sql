create database Bank
go

use Bank
go

create table Customers(
	CustomerId int primary key identity(1, 1),
	CName varchar(50),
	DOB varchar(50)
)

create table BankAccounts(
	BankAccountId int primary key identity(1, 1),
	IBAN varchar(50),
	CurrentBalance float,
	CustomerId int foreign key references Customers(CustomerId)
)

create table Cards(
	CardId int primary key identity(1, 1),
	CardNumber varchar(50),
	CVV varchar(5),
	BankAccountId int foreign key references BankAccounts(BankAccountId)
)

create table ATMs(
	ATMId int primary key identity(1, 1),
	address varchar(50)
)

create table Transactions(
	CardId int foreign key references Cards(CardId),
	ATMId int foreign key references ATMs(ATMId),
	SumOfMoney float,
	TDate varchar(50),
	TTime varchar(50)
	constraint pk_Transactions primary key(CardId, ATMId)
)

alter table Transactions drop constraint pk_Transactions


insert into Customers values('Andrei', '12.05.1997'), ('Gigi', '13.05.2000'), ('Ana', '29.02.1996')
insert into BankAccounts values('12345', 1005.23, 1), ('123456', 9999.98, 2), ('1234567', 100, 3), ('12345678', 8007.9, 2)
insert into Cards values('123','123', 1), ('234','234', 1), ('345','345', 2), ('456','456', 4), ('567','567', 3)
insert into ATMs values('addr1'), ('addr2'), ('addr3'), ('addr4')
insert into Transactions values(1, 1, 100, '14.05.2020', '15:45:00'), (1, 2, 200, '15.05.2020','16:45:00'), (1, 3, 100, '16.05.2020', '18:00:00'), (3, 4, 100, '19.09.2020','23:00:00')
insert into Transactions values(2, 1, 100, '20.01.2021', '00:00:00')



--- 2) Implement a stored procedure that receives a card and deletes all the transactions related to that card.

go
create proc DeleteTransaction @CardId int
as
	delete from Transactions
	where Transactions.CardId = @CardId
go

select * from Transactions
exec DeleteTransaction 1
select * from Transactions
select * from ATMs
--- 3) Create a view that shows the card numbers which were used in transactions at all the ATMs.


go 
create or alter view vTransactionsATMs 
as
	select x.CardId from (
	select distinct t.CardId, t.ATMId from Transactions t
	group by t.CardId, t.ATMId) x
	group by x.CardId
	having COUNT(*) = (select count(*) from ATMs)
go

select * from vTransactionsATMs

---4) Implement a function that lists the cards (number and CVV code) that have the total
--- transactions sum greater than 2000 lei.

go
create or alter function uf_Cards(@r int)
returns table
as
return
	select c.CardId, c.CardNumber, c.CVV from Cards c inner join 
	(select t.CardId, sum(t.SumOfMoney)as Sum from Transactions t
	group by t.CardId
	having sum(t.SumOfMoney) > @r) x on c.CardId = x.CardId
go

select * from uf_Cards(500)