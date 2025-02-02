use SneakerStore
go

create or alter procedure add to tables (@tableName varchar(50)) as
if @tableName in (select Name from Tables) begin 
print 'Table already exists' 
return
end
if @tableName not in (select TABLE_NAME from INFORMATION_SCHEMA.TABLES) begin
print 'Table does not exist in database'
return 
end
insert into Tables(Name) values (@tableName)