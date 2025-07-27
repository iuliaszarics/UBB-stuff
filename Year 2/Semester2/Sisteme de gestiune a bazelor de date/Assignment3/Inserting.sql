create or alter procedure AddStudent
    @StudentName nvarchar(100)
as
begin
    if (@StudentName is null)
    begin
        raiserror('student name must not be null', 16, 1);
        return;
    end
    insert into Students (StudentName)
    values (@StudentName);
    declare @StudentID int;
    set @StudentID = SCOPE_IDENTITY();
    exec sp_log_changes null, @StudentName, 'added row to students'
end;
go

create or alter procedure AddCourse
    @CourseName nvarchar(200)
as
begin
    if (@CourseName is null)
    begin
        raiserror('course name must not be null', 16, 1);
        return;
    end
    insert into Courses (CourseName)
    values (@CourseName);
    declare @CourseID int;
    set @CourseID = SCOPE_IDENTITY();
    exec sp_log_changes null, @CourseName, 'added row to courses'
end;
go

create or alter procedure AddStudentCourse
    @StudentName nvarchar(100),
    @CourseName nvarchar(200)
as
begin
    declare @StudentID int;
    declare @CourseID int;

    if (@StudentName is null)
    begin
        raiserror('student name must not be null', 16, 1);
        return;
    end

    if (@CourseName is null)
    begin
        raiserror('course name must not be null', 16, 1);
        return;
    end

    set @StudentID = (select StudentID from Students where StudentName = @StudentName);
    set @CourseID = (select CourseID from Courses where CourseName = @CourseName);

    if (@StudentID is null)
    begin
        raiserror('student does not exist', 16, 1);
        return;
    end

    if (@CourseID is null)
    begin
        raiserror('course does not exist', 16, 1);
        return;
    end

    insert into StudentCourses (StudentID, CourseID) values (@StudentID, @CourseID);

    declare @newData nvarchar(100);
    set @newData = @StudentName + '  ' + @CourseName;
    exec sp_log_changes null, @newData, 'linked student with course';
end;
go

create or alter procedure RollbackScenarioNoFail
as
begin
    begin transaction;
    begin try
        exec AddStudent 'Student5';
        exec AddCourse 'Software Engineering';
        exec AddStudentCourse 'Student5', 'Software Engineering';
        commit transaction;
    end try
    begin catch
        rollback transaction;
        throw;
    end catch;
end;
go

create or alter procedure RollbackScenarioFail
as
begin
    begin transaction;
    begin try
        exec AddStudent 'Student5';
        exec AddCourse 'Software Engineering';
        exec AddStudentCourse 'Student5', 'Analysis'; -- fail course does not exist
        commit transaction;
    end try
    begin catch
        rollback transaction;
        throw;
    end catch;
end;
go

create or alter procedure NoRollbackScenarioManyToManyNoFail
as
begin
    declare @ERRORS int;
    set @ERRORS = 0;

    begin try
        exec AddStudent 'Student6';
    end try
    begin catch
        set @ERRORS = @ERRORS + 1;
    end catch;

    begin try
        exec AddCourse 'Algebra';
    end try
    begin catch
        set @ERRORS = @ERRORS + 1;
    end catch;

    if (@ERRORS = 0)
    begin
        begin try
            exec AddStudentCourse 'Student6', 'Algebra';
        end try
        begin catch
        end catch;
    end
end;
go

create or alter procedure NoRollbackScenarioManyToManyFail
as
begin
    declare @ERRORS int;
    set @ERRORS = 0;

    begin try
        exec AddStudent 'Student7';
    end try
    begin catch
        set @ERRORS = @ERRORS + 1;
    end catch;

    begin try
        exec AddCourse 'Dynamical Systems';
    end try
    begin catch
        set @ERRORS = @ERRORS + 1;
    end catch;

    if (@ERRORS = 0)
    begin
        begin try
            exec AddStudentCourse 'Student7', 'Nonexistent Course'; -- fail: course does not exist
        end try
        begin catch
        end catch;
    end
end;
go

use school_management
go

exec RollbackScenarioFail;
exec RollbackScenarioNoFail;
exec NoRollbackScenarioManyToManyFail;
exec NoRollbackScenarioManyToManyNoFail;

select * from Students;
select * from Courses;
select * from StudentCourses;
select * from ActionLogs;

delete from StudentCourses;
delete from Students;
delete from Courses;
delete from ActionLogs;