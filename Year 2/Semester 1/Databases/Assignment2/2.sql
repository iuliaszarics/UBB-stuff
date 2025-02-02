ALTER TABLE SneakerStore
ADD CONSTRAINT FK_StoreInventory
FOREIGN KEY (inventoryID) 
REFERENCES StoreInventory(inventoryID) 
ON DELETE CASCADE;