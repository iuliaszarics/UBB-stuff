alter database school_management set allow_snapshot_isolation on

set transaction isolation level snapshot -- vede databaseul cum e cand a inceput
begin transaction
select * from Courses where CourseID = 1 -- citim primu curs 
waitfor delay '00:00:05' 
update Courses set CourseName='course transaction 1' where CourseID=1 --actualizam primu curs
commit transaction

set transaction isolation level snapshot
begin transaction
select * from Courses where CourseID=1
waitfor delay '00:00:05' 
update Courses set CourseName='am actualizat' where CourseID=1 -- nu o sa mearga pt ca tranzactia 1 a schimbat val
commit transaction

select * from Courses where CourseID=1