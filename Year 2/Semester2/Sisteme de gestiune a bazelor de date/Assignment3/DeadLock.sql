
begin transaction
update Courses set CourseName=' course transaction 1' where CourseID=11; --actualizeaza course 
waitfor delay '00:00:10';  -- tine courses blocat 10 sec
update Students set StudentName='student transaction 1' where StudentID=12;
commit transaction;


begin transaction
update Students set StudentName='student transaction 2' where StudentID=1; --actualizeaza student
waitfor delay '00:00:05'; -- tine blocat 5 min
update Courses set CourseName='course transaction 2' where CourseID=1; --actualizeaza courses
commit transaction;


begin transaction
update Courses set CourseName='course transaction 2' where CourseID=1;
waitfor delay '00:00:05';
update Students set StudentName='student transaction 2' where StudentID=1;
commit transaction;

select * from Courses
select * from Students
insert into Courses (CourseName) values ('')

SET IDENTITY_INSERT Courses ON;

-- Only run if these IDs are missing
IF NOT EXISTS (SELECT 1 FROM Courses WHERE CourseID = 1)
    INSERT INTO Courses (CourseID, CourseName) VALUES (1, 'Physics 101');

IF NOT EXISTS (SELECT 1 FROM Courses WHERE CourseID = 11)
    INSERT INTO Courses (CourseID, CourseName) VALUES (11, 'Mathematics 101');

SET IDENTITY_INSERT Courses OFF;

SET IDENTITY_INSERT Students ON;

-- Only run if these IDs are missing
IF NOT EXISTS (SELECT 1 FROM Students WHERE StudentID = 1)
    INSERT INTO Students (StudentID, StudentName) VALUES (1, 'Jane Smith');

IF NOT EXISTS (SELECT 1 FROM Students WHERE StudentID = 12)
    INSERT INTO Students (StudentID, StudentName) VALUES (12, 'John Doe');

SET IDENTITY_INSERT Students OFF;
