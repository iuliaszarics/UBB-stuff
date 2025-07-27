ALTER DATABASE school_management SET ALLOW_SNAPSHOT_ISOLATION ON 

BEGIN TRAN
UPDATE Courses SET CourseName='curs transaction 1' WHERE CourseID=1
waitfor delay '00:00:05' 
COMMIT TRAN

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRAN
Select * from Courses where CourseID=1
waitfor delay '00:00:05' 
select * from Courses where CourseID=1
update Courses set CourseName='am actualizat' where CourseID=1
COMMIT TRAN