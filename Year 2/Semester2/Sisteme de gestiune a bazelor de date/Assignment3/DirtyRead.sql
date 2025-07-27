set identity_insert Courses on;
begin transaction
insert into Courses (CourseID, CourseName) VALUES (999, 'dirty read') -- adauga o valoare
waitfor delay '00:00:05' --asteapta 5 min
rollback transaction -- da rollback deci se sterge valoarea
set identity_insert Courses off;

set transaction isolation level read uncommitted --read uncommitted
begin tran
select * from Courses where CourseID=999 --poate returna randul adaugat
waitfor delay '00:00:07' 
select * from Courses  where CourseID=999 --randul nu mai exista
commit tran

set transaction isolation level read committed 
begin tran
select * from Courses where CourseID=999 -- nu vede randu pt ca e blocat de read committed
waitfor delay '00:00:07' 
select * from Courses where CourseID=999
commit tran