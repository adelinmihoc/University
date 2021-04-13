create database OceanLife
go
use OceanLife
go

create table Orders(
name varchar(50) primary key
)

create table Families(
name varchar(50) primary key,
Oname varchar(50) foreign key references Orders(name)
)

create table Genera(
name varchar(50) primary key,
Fname varchar(50) foreign key references Families(name),
speciesCount int
)

create table Species (
name varchar(50) primary key,
Gname varchar(50) foreign key references Genera(name),
)

create table LivinfBeing(
id int primary key,
name varchar(50),
Sname varchar(50) foreign key references Species(name),
fLength float,
fWeight float,
color char(10),
behaviour varchar(256), 
)

create table Oceans(
name varchar(50) primary key,
oLocation varchar(50),
averageDepth float,
area float,
volume float,
)

create table Territory(
Sname varchar(50) foreign key references Species(name),
Oname varchar(50) foreign key references Oceans(name),
primary key(Sname, Oname),
)

create table Predators(
PredatorSpecies varchar(50),
foreign key(PredatorSpecies) references Species(name),
PreySpecies varchar(50) foreign key references Species(name),
primary key(PredatorSpecies, PreySpecies)
)

create table AquaticRespiration(
respiratorySystem varchar(50) primary key,
controlType varchar(50)
)

alter table Species
add respiratorySystem varchar(50) foreign key references AquaticRespiration(respiratorySystem)

create table Ecosystems(
name varchar(50) primary key,
eLocation varchar(50),
eArea float,
)

create table MarineComunities(
Sname varchar(50) foreign key references Species(name),
Ename varchar(50) foreign key references Ecosystems(name),
primary key(Sname, Ename)
)

