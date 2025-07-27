begin tran
waitfor delay '00:00:10' -- delay
insert into Students (StudentName) values ('phantom')  --dupa delay adagam
commit tran

set transaction isolation level repeatable read
begin tran
select * from Students where StudentName like 'p%' -- nu exista inca phantom
waitfor delay '00:00:10' 
select * from Students where StudentName like 'p%'  -- exista phantom
commit tran

set transaction isolation level serializable -- serializable care nu permite inserari
begin tran
select * from Students where StudentName like 'p%'
waitfor delay '00:00:10' 
select * from Students where StudentName like 'p%'
commit tran