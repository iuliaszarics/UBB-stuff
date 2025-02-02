-- a. modify the type of a column;
-- b. add / remove a column;
-- c. add / remove a DEFAULT constraint;
-- d. add / remove a primary key;
-- e. add / remove a candidate key;
-- f. add / remove a foreign key;
-- g. create / drop a table.

--a. modify/undo modification

use SneakerStore
go

create procedure modify_type_column1 as
begin
	alter table StoreAddress alter column postalCode TINYINT
	print 'am schimbat din int in tinyint'
end
go

exec modify_type_column1

create procedure modify_back_type_column2 as
begin
	alter table StoreAddress alter column postalCode INT
	print 'am schimbat inapoi din tinyint in int'
end
go

exec modify_back_type_column2

--b. add/remove column

create procedure add_column3 as
begin
	alter table StoreAddress add ColoanaNoua int
	print 'am adaugat o coloana noua in storeAddress'
end
go

exec add_column3

create procedure remove_column4 as
begin
	alter table StoreAddress drop column ColoanaNoua
	print 'pa pa coloana'
end
go

exec remove_column4


--c. add/remove default constraint

create procedure add_default_constraint5 as
begin
	alter table StoreAddress add constraint df_postalCode default 545100 for postalCode
	print 'adaugat default constaint la codu postal'
end
go

exec add_default_constraint5

exec add_default_constraint5

create procedure remove_def_constraint6 as
begin
	alter table StoreAddress drop constraint df_postalCode
	print 'pa pa default constraint'
end
go

exec remove_def_constraint6

-- g. create / drop a table
--fac asta inaite ca sa am pe ce lucra


create procedure create_table13 as
begin 
	create table Material(
	materialID int not null,
	materialName varchar(50) not null,
	materialType varchar(50),
	price int not null
	constraint material_primary primary key(materialID)
	);
	print 'am facut tabelul material'
end
go

exec create_table13

create procedure remove_table14 as 
begin
	drop table Material
	print 'pa pa tabel material'
end
go

exec remove_table14


--d. add/remove priary key

create procedure add_primary_key7 as
begin
	alter table Material
	add constraint pk_Material primary key(materialID)
	print 'am facut primary key'
end
go

exec add_primary_key7

create procedure remove_primary_key8 as
begin
	alter table Material drop constraint pk_Material
	print 'pa pa primary key'
end
go

exec remove_primary_key8

--e. add/remove candidate key

create procedure add_candidate_key9 as
begin
	alter table Material
	add constraint material_candidate UNIQUE(materialID)
	print 'am facut unique constraint'
end
go

exec add_candidate_key9

create procedure remove_candidate_key10 as
begin
	alter table Material
	drop constraint material_candidate
	print 'pa pa candidate key'
end
go

exec remove_candidate_key10

--f. add/remove foreign key

create procedure add_foreign_key11 as
begin
	alter table Material
	add constraint material_foreign foreign key (materialID) REFERENCES Sneaker(sneakerID)
	print 'am facut foreign key '
end
go

exec add_foreign_key11

create procedure remove_foreign_key12 as
begin
	alter table Material
	drop constraint material_foreign
	print 'pa pa foreign key'
end
go



exec remove_foreign_key12

create table versionTable(
current_procedure varchar(199),
previous_procedure varchar(199),
destination int unique);
go

select * from versionTable


insert into versionTable(current_procedure,previous_procedure,destination)
values
('create_table13','remove_table14',1),
('modify_type_column1','modify_back_type_column2',2),
('add_column3','remove_column4',3),
('add_default_constraint5','remove_def_constraint6',4),
('add_primary_key7','remove_primary_key8',5),
('add_candidate_key9','remove_candidate_key10',6),
('add_foreign_key11','remove_foreign_key12',7)


create table currentVersion(
curent int default 0);


insert into currentVersion values (0)

drop procedure main

create procedure main(@version int) as
begin
    declare @current_version int;
    set @current_version = (select curent from currentVersion);

    if @version < 0 or @version > 7
    begin
        raiserror('numa 7 versiuni avem', 17, 1);
        return;
    end

    if @version = @current_version
    begin
        print 'deja suntem aici';
        return;
    end

    declare @current_procedure nvarchar(50);

    if @current_version < @version
    begin
        while @current_version < @version
        begin
            set @current_procedure = (select current_procedure from versionTable where destination = @current_version + 1);
            exec(@current_procedure);
            set @current_version = @current_version + 1;
        end
    end
    else
    begin
        while @current_version > @version
        begin
            set @current_procedure = (select previous_procedure from versionTable where destination = @current_version);
            exec(@current_procedure);
            set @current_version = @current_version - 1;
        end
    end

    update currentVersion set curent = @current_version;
    print N'am ajuns la versiunea mult dorita:  ' + cast(@current_version as NVARCHAR(10));
end;



exec modify_type_column1
exec modify_back_type_column2

exec add_column3
exec remove_column4

exec add_default_constraint5
exec remove_def_constraint6

exec add_primary_key7
exec remove_primary_key8

exec add_candidate_key9
exec remove_candidate_key10


exec add_foreign_key11
exec remove_foreign_key12

exec create_table13
exec remove_table14



exec main 1
exec main 2
exec main 3
exec main 4
exec main 5
exec main 6
exec main 7
exec main 0

alter table Material drop constraint pk_Material

select * from currentVersion