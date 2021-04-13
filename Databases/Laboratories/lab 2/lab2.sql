use OceanLife

--1.1
-- inserting into Orders
insert into Orders
values ('Perciformes'), ('Myxini'), ('Beloniformes'), ('Lamniformes'), ('Pleuronectiformes'), ('Gasterosteiformes'), ('Zeiformes')

-- select all
Select * from Orders

-- insert into families
Insert into Families
values ('Apogonidae', 'Perciformes'), ('Belontiidae','Perciformes'), ('Serrantidae', 'Perciformes'),
	('Pomacanthidae','Perciformes'), ('Pomacentridae','Perciformes'), ('Blenniidae','Perciformes'),
	('Chaetodontidae','Perciformes'), ('Cyprinidae','Cypriniformes'), ('Exocoetidae','Beloniformes'),
	('Cetorhinidae','Lamniformes'), ('Pleuronectidae','Pleuronectiformes'), ('Syngnathidae','Gasterosteiformes'), 
	('Zeidae', 'Zeiformes')

-- select all
Select * from Families

update Families
set name='Serranidae'
where name='Serrantidae'

-- insert into Genera
Insert into Genera
values ('Betta', 'Belontiidae', 73), ('Anthias', 'Serranidae', 8), ('Exocoetus', 'Exocoetidae', 5), ('Fodiator', 'Exocoetidae', 2), 
	('Cetorhinus', 'Cetorhinidae', 1), --the basking shark not only the single species from that Genus but from the entire Family
	('Platichthys', 'Pleuronectidae', 3), ('Pomacanthus', 'Pomacanthidae', 13), ('Hippocampus', 'Syngnathidae', 46), 
	('Amphiprion', 'Pomacentridae', 29),
	('Zeus', 'Zeidae', 2), ('Chaetodon', 'Chaetodontidae', 87), ('Forcipiger', 'Chaetodontidae', 3), ('Apogon', 'Apogonidae', 200)

select * from Genera

-- insert into Aquatic Respiration
insert into AquaticRespiration
values ('Gills', 'Ram ventilation, operculum, countercurrent flow')

select * from AquaticRespiration

--insert into Species
insert into Species
values ('A. americanus','Apogon','Gills'), ('A. atricaudus','Apogon','Gills'), ('A. ruber','Apogon','Gills'),
('B. trifasciata','Betta','Gills'), ('B. antoni','Betta','Gills'), ('B. splendens','Betta','Gills'),
('A. anthias','Anthias','Gills'), ('A. noeli','Anthias','Gills'),
('E. peruvianus','Exocoetus','Gills'),
('F. acutus','Fodiator','Gills'),
('C. maximus','Cetorhinus','Gills'),
('P. flesus','Platichthys','Gills'), ('P. stellatus','Platichthys','Gills'),
('P. annularis','Pomacanthus','Gills'), ('P. maculosus','Pomacanthus','Gills'), ('P. asfur','Pomacanthus','Gills'),
('H. abdominalis','Hippocampus','Gills'), ('H. coronatus','Hippocampus','Gills'), ('H. zebra','Hippocampus','Gills'),
('A. ocellaris','Amphiprion','Gills'), --Nemo clownfish
('A. clarkii','Amphiprion','Gills'), ('A. pacificus','Amphiprion','Gills'),
('Z. capensis','Zeus','Gills'),
('C. punctatofasciatus','Chaetodon','Gills'), ('C. quadrimaculatus','Chaetodon','Gills'), ('C. interruptus','Chaetodon','Gills'),
('F. flavissimus','Forcipiger','Gills'), ('F. longirostris','Forcipiger','Gills')


select * from Species

-- insert into Oceans
insert into Oceans
-- name, location, average depth, area, volume
values ('Pacific Ocean', 'Separates Asia and Australasia from Americas', 3970, 168723000, 669880000),
('Atlantic Ocean', 'Separates Americas from Europe and Africas', 3646, 85133000, 310410900),
('Indian Ocean', 'Southern Asia,separates Africa and Australia', 3741, 70560000,264000000),
('Arctic Ocean', 'Borders North America and Eurasia, covers Arctic', 1205, 15558000,18750000)

select * from Oceans

--insert into Territories
insert into Territories
values ('A. americanus', 'Pacific Ocean'), ('A. americanus', 'Atlantic Ocean'),
('A. atricaudus', 'Pacific Ocean'), ('A. atricaudus', 'Atlantic Ocean'), ('A. atricaudus', 'Indian Ocean'),
('B. splendens', 'Indian Ocean'),
('A. noeli', 'Atlantic Ocean'), ('A. noeli', 'Pacific Ocean'), ('A. noeli', 'Indian Ocean'),
('C. maximus', 'Pacific Ocean'), ('C. maximus', 'Atlantic Ocean'), ('C. maximus', 'Indian Ocean'), ('C. maximus', 'Arctic Ocean')

select * from Territories

--alter table LivingBeing
--alter column fLength DROP DEFAULT;
--add default -1 for fWeight
--add default 'unknown' for color
--add default 'swims' for behaviour

-- insert into LivingBeing
insert into LivingBeing (id, name, Sname)
values (101, 'Plain cardinalfish', 'A. atricaudus'),
(100, 'Brazilian flamefish', 'A. americanus'),
(102, 'Basking shark', 'C. maximus'),
(103, 'Starry flounder', 'P. stellatus'),
(104, 'Bluering angelfish', 'P. annularis'),
(105, 'Yellowbar angelfish', 'P. maculosus'),
(106, 'Arabian angelfish', 'P. asfur'),
(107, 'Big-belly seahorse', 'H. abdominalis'),
(108, 'Crowned seahorse', 'H. coronatus'),
(109, 'Zebra seahorse', 'H. zebra'),
(110, 'Nemo', 'A. ocellaris'),
(111, 'Yellowtail clownfish', 'A. clarkii'),
(112, 'Pacific anemonefish', 'A. pacificus'),
(113, 'Cape dory', 'Z. capensis'),
(114, 'Spotband butterflyfish', 'C. punctatofasciatus'),
(115, 'Fourspot butterflyfish', 'C. quadrimaculatus'),
(116, 'Yellow longnose butterflyfish', 'F. flavissimus'),
(117, 'Longnose butterflyfish', 'F. longirostris')

insert into LivingBeing (id, name, Sname)
values (201, 'Plain cardinalfish', 'A. atricaudus'),
(200, 'Brazilian flamefish', 'A. americanus'),
(202, 'Basking shark', 'C. maximus'),
(203, 'Starry flounder', 'P. stellatus'),
(204, 'Bluering angelfish', 'P. annularis'),
(205, 'Yellowbar angelfish', 'P. maculosus'),
(206, 'Arabian angelfish', 'P. asfur'),
(207, 'Big-belly seahorse', 'H. abdominalis'),
(208, 'Crowned seahorse', 'H. coronatus'),
(209, 'Zebra seahorse', 'H. zebra'),
(210, 'Nemo', 'A. ocellaris'),
(211, 'Yellowtail clownfish', 'A. clarkii'),
(212, 'Pacific anemonefish', 'A. pacificus'),
(213, 'Cape dory', 'Z. capensis'),
(214, 'Spotband butterflyfish', 'C. punctatofasciatus'),
(215, 'Fourspot butterflyfish', 'C. quadrimaculatus'),
(216, 'Yellow longnose butterflyfish', 'F. flavissimus'),
(217, 'Longnose butterflyfish', 'F. longirostris')


--insert into ecosystems
insert into Ecosystems
values('The Great Barrier Reef','Australia', 2600), 
('The Mesoamerican Barrier Reef System', 'Isla Contoy, Yucatan Peninsula, Islands of Honuras', 1000)


insert into Ecosystems
values ('Kelp forest - Lamimaria', 'Atlantic Ocean, China, Japan', 3000), ('Kelp forest - Ecklonia', 'Australia, New Zeeland, South Africa', 2500)

select * from Ecosystems

--insert into MarineComunities
insert into MarineComunities
values('A. ocellaris', 'The Great Barrier Reef'), ('A. pacificus','The Great Barrier Reef'),
('P. annularis','The Great Barrier Reef'), ('H. zebra', 'The Great Barrier Reef'), 
('A. clarkii', 'The Great Barrier Reef'),('C. punctatofasciatus','The Great Barrier Reef'),
('C. quadrimaculatus','The Great Barrier Reef'),('F. flavissimus','The Great Barrier Reef'),
('F. longirostris','The Great Barrier Reef')

select * from MarineComunities

insert into Territories
values ('A. ocellaris', 'Pacific Ocean'), ('A. ocellaris', 'Indian Ocean'), 
('P. annularis', 'Pacific Ocean'), ('P. annularis', 'Atlantic Ocean'),
('A. clarkii', 'Pacific Ocean'), ('F. longirostris', 'Pacific Ocean')





--1.2
-- insert statement that violates referential integrity constraints
insert into Species 
values ('D. leucas', 'Delphinapterus', 'Gills')

select * from Oceans

-- update data for 3 tables
Update LivingBeing -- update adds 15 to fLength if > 24 and id % 4 == 0
set fLength = fLength + 15
where fLength > 24 and id%4!=0
select * from LivingBeing

Update Oceans -- update the area of the oceans that have the avgdepth <= 1205 or volume < 18760000
set area = 15559000
where averageDepth <= 1205 or volume < 18760000

Update LivingBeing -- update the fWeight if it is null
set fWeight = 10
where fWeight is null

Update Ecosystems -- update eLocation if the area is in between 2 values
set eLocation = 'Atlantic Ocean, China, Japan'
where eArea between 2900 and 3100

-- delete data for 2 tables
delete from LivingBeing -- deletes from LivingBeing if id in set and name is not Nemo
where id in (201,202,210) and name not in ('Nemo') 

delete from LivingBeing -- deletes if fWeight not null
where fWeight is not null

delete from Oceans -- deletes all oceans that have oLocation start with Borders
where oLocation like 'Borders%'

delete from LivingBeing -- deletes LivingBeing if id >= 217 except 219
where id >= 217 and id != 219

-- used: =, and, >, or, <=, <, is null, between, in, is not null, like, not, >=, != 


--a 2 querries with union[ALL] and OR
Select * from LivingBeing   --select the living beings with id < 105 or id > 205
where id < 105 or id > 205

Select * from LivingBeing
where id < 105
Union
Select * from LivingBeing
where id >205

--b 2 querries with the intersection operation Intersect and In
Select S1.name from Species S1 -- select the species that have name start with A and genus end with us
where Gname like 'A_%' 
Intersect
Select S2.name from Species S2
where name like '%_us'

Select * from Species s1 
where Gname like 'A_%' and name in 
(Select s2.name from Species s2 where name like '%_us') 

--c 2 querries with the difference: except and Not In
Select g.name from Genera g --selects all Genera names that have more then the minimum no of species + 13 and name doesn't start with A
where g.speciesCount > (select min(g.speciesCount) from Genera g) + 13
Except
Select g1.name from Genera g1
where g1.name like 'A_%'

Select g.name from Genera g
where g.speciesCount > 13 and g.name not in (Select g1.name from Genera g1 where g1.name like 'A_%')

--d 4 querries with INNER JOIN, LEFT JOIN, RIGHT JOIN, FULL JOIN
-- one will join at least 3 tables
-- one will join at least two m:n relationships

Select s.name, s.Gname, o.name, e.name, e.eArea --joins species with the oceans and ecosystems, joins 2 m:n relationships
from Species s
inner join Territories t on s.name = t.Sname
inner join Oceans o on t.Oname = o.name
inner join MarineComunities m on s.name = m.Sname
inner join Ecosystems e on m.Ename = e.name and e.eLocation = t.Oname

-- left join --joins 3 tables
select l.name, l.fLength, l.fWeight, l.color, s.Gname, s.name, o.name, o.oLocation
from LivingBeing l
left outer join Species s on l.Sname = s.name 
left outer join Territories t on s.name = t.Sname
left outer join Oceans o on o.name = t.Oname

-- right join
select  l.id, l.name, l.Sname, l.fLength, l.fWeight, l.color, s.Gname, s.name, g.Fname, g.speciesCount
from LivingBeing l
right outer join Species s on s.name = l.Sname
right outer join Genera g on g.name = s.Gname

-- full join
select s.Gname, s.name, l.id, l.name, l.fLength, l.fWeight, l.color, l.behaviour  
from Species s 
full outer join LivingBeing l on s.name = l.Sname


--e 2 querries using the in operator to introduce a subquery in the where clause; 
--in at least one querry, the subquerry should include a subquerry in its own where clause

select * --select all ecosystems from MarineComunities that contains species
from Ecosystems e 
where e.name in (select m.Ename from MarineComunities m where m.Sname in (select s.name from Species s))

select * --select all from oceans that are location for an ecosystem
from Oceans o
where o.name in (select e.eLocation from Ecosystems e)


--f 2 queries using exist to introduce a subquery in the where clause

select * --selects all species where exists living beings that have weight > 1000
from Species s
where exists (select * from LivingBeing l where l.fWeight > 1000 and l.Sname = s.name)

select * --select all species that live in oceans that have averageDepth > 3700
from Species s
where exists (select * from Territories t where t.Sname = s.name and t.Oname in (select o.name from Oceans o where o.averageDepth > 3700 ))


--g 2 querries with a subquery in the from clause

select A.name, A.controlType --select species name and control type of the respiration
from (select s.name, r.respiratorySystem, r.controlType from AquaticRespiration r inner join Species s on s.respiratorySystem = r.respiratorySystem) A

select top 3 A.name -- selects top 3 Genus names that have over 50 species
from (select * from Genera g where g.speciesCount > 50) A

--h 4 querries with the GROUP BY clause
--3 of which also contain the HAVING clause
--2 of the latter will also have a subquerry in the HAVING clause
--use aggregation operators: COUNT, SUM, AVG, MIN, MAX

select distinct l.Sname, avg(l.fLength) as averageLength --calculate the average length of a species based on the lengths of living beings
from LivingBeing l inner join LivingBeing l1 on l.Sname = l1.Sname
group by l.Sname
having AVG(l.fLength) > 5 * 8 / 2
order by avg(l.fLength)

		-- select the name of the LivingBeings that have grey color calculate their number and totalWeight 
		-- display only the livingBeings that have totalWeight > average weight
select top 4 l.name, COUNT(l.name) as NoOfBeings, SUM(l.fWeight) as TotalWeight
from LivingBeing l
where l.color = 'Grey'
group by l.name
having sum(l.fWeight) > (select AVG(l.fWeight))
order by sum(l.fWeight) desc


select l.Sname, l.fLength, count(*) as Number --select the species name from LivingBeing that have minimum lenght and their number
from LivingBeing l
group by l.Sname, l.fLength
having l.fLength = (select min(l1.fLength) from LivingBeing l1)


select g.name, Max(g.speciesCount) as maxSpecies --select the genus name and the maximum species
from Genera g
group by g.name
Order by max(g.speciesCount) desc


--i 4 querries using ANY and ALL to introduce a subquerry in the WHERE clause; 
--rewrite 2 of them with aggregation operators,
--and the other 2 with [NOT] IN

select o.name --select all oceans that are the locations of any ecosystem
from Oceans o
where o.name =any (select e.eLocation from Ecosystems e)

	select o.name --rewrite with in
	from Oceans o
	where o.name in (select e.eLocation from Ecosystems e)

select s.name -- select all species that are not part of a marine comunity
from Species s
where s.name <>all (select distinct m.Ename from MarineComunities m)

	select s.name --rewrite with not in
	from Species s
	where s.name not in (select m.Ename from MarineComunities m)

select distinct l.name -- select all distinc livingbeings that have maximum length
from LivingBeing l
where l.fLength >=ALL (select l1.fLength from LivingBeing l1)
	
	select l.name --rewrite using max
	from LivingBeing l
	where l.fLength =(select MAX(l1.fLength) from LivingBeing l1)

select e.name --select the name of the ecosystems that have minimum area
from Ecosystems e
where e.eArea <=ALL (select e1.eArea from Ecosystems e1)

	select e.name
	from Ecosystems e
	where e.eArea <= (select min(e1.eArea) from Ecosystems e1)

select * from Ecosystems

