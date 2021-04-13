create database writtenPractice
go

use writtenPractice
go

create table S(
	FK1 int,
	FK2 int,
	A varchar(50),
	B varchar(50),
	C varchar(50),
	D int,
	E INT
	constraint pk_S primary key(FK1, FK2)
)

--drop table S

insert into S values
(1,1, 'a1','b1','c1',7,2),
(1,2, 'a_','b3','c1',7,2),
(1,3, 'a2','b1','c2',NULL,2),
(2,1, 'a3','b3','c2',NULL,100),
(2,2, 'a3','b3','c3',NULL,100)

select * from S

select * from S s1 left join S s2 on s1.FK1 = s2.E

select distinct * from S s1 inner join S s2 on s1.FK1 = s2.E


select FK2, FK1, COUNT(DISTINCT B)
from S
group by FK2, FK1
having FK1 = 0

select FK2, FK1, COUNT(C)
from S
group by FK2, FK1
having MAX(E) < 0



create table R (
	RID int primary key,
	A int,
	B int,
	C int,
	D int,
	E int,
	F int
)

insert into R values
(1,100,200,5,200,20,11),
(2,101,50,11,200,5,12),
(3,100,100,7,200,5,13),
(4,200,200,6,200,20,14),
(5,200,100,2,200,5,9),
(6,300,50,11,200,5,10)

select r1.RID, r1.A + r2.A C2, r1.A * r2.A C3
from R r1 left join R r2 on r1.RID = r2.RID
where r1.A > ANY(select B from R where C < 10)


select S.RID, S.A from 
	(select * from R where F < 13) S
inner join R on S.D = R.D


select R.*
from 
 R right join
(select r1.RID, r2.A, r3.B
	from R r1 inner join R r2 on r1.A = r2.B
	inner join R r3 on r2.B > r3.D
	where r1.F > 10) t
 on t.RID = R.RID
