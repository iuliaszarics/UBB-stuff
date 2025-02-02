use Assignment5
go

create table TableA(
aid int primary key,
a int unique
);

drop table TableA
drop table TableB
drop table TableC

create table TableB(
bid int primary key,
b int
);

create table TableC(
cid int primary key,
c1 int foreign key references TableA(aid),
c2 int foreign key references TableB(bid)
);

create procedure populate_tableA(@rows int) as
begin
	while @rows>0
	begin
		insert into TableA(aid,a) values (@rows,@rows*4+87)
		set @rows=@rows-1
	end
end
go

create procedure populate_tableB(@rows int) as
begin
	while @rows>0
	begin
		insert into TableB(bid,b) values (@rows,@rows*3+24)
		set @rows=@rows-1
	end
end
go

create procedure populate_tableC(@rows int) as
begin
	while @rows>0
	begin
		insert into TableC(cid,c1,c2) values (@rows,@rows,@rows)
		set @rows=@rows-1
	end
end
go

exec populate_tableA 3000
exec populate_tableB 3000
exec populate_tableC 3000

--a. write queries on TableA such that their execution plans contain the following operators:
--clustered index scan

select * from TableA;

--clustered index seek
select * 
from TableA 
where aid>10 and aid<50;

--nonclustered index scan
select aid
from TableA;

--nonclustered index seek
select a
from TableA
where a between 100 and 500

--key lookup 
select a
from TableA
where a=100

--b. write a query on table TableB with a where clause of the form where b=value and analyze its execution plan . create a nonclustered index that can speed up the query. recheck the quey's execution plan (operators, select's estimated subtree cost)

select * 
from TableB
where b=237

create nonclustered index tableb_index on TableB(b)
drop index tableb_index on TableB

--create a view that joins at least 2 tables . check whether existing indexes are useful; if not, reasses existing indexes/examine the cardinality of the tables.

create view theView as
select TableA.aid,TableB.bid,TableC.cid
from TableC
inner join TableA on TableC.cid=TableA.aid 
inner join TableB on TableC.c2=TableB.bid
where TableA.a >227 and TableB.b<429
go

select * from theView
create nonclustered index tableA_index on TableA(a)
drop index tableA_index on TableB

create nonclustered index tableC_index on TableC(c1,c2)
drop index tableC_index on TableC