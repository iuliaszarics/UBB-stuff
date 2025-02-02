CREATE DATABASE SneakersStore
GO

CREATE TABLE StoreAddress
(
	adressID INT PRIMARY KEY IDENTITY,
	county VARCHAR(30) NOT NULL,
	city VARCHAR(30) NOT NULL,
	street VARCHAR(50) NOT NULL,
	numberOfStreet INT NOT NULL,
	postalCode INT NOT NULL,
)

CREATE TABLE Producer
(
	producerID INT PRIMARY KEY IDENTITY,
	producerName VARCHAR(30),
)

CREATE TABLE Brand
(
	brandID INT PRIMARY KEY IDENTITY,
	brandName VARCHAR(50) NOT NULL,
	producerID INT FOREIGN KEY REFERENCES Producer(producerID),
)

CREATE TABLE Model
(
	modelID INT PRIMARY KEY IDENTITY,
	modelName VARCHAR(100) NOT NULL,
	releaseYear INT,
	brandID INT FOREIGN KEY REFERENCES Brand(brandID),
)

CREATE TABLE Sneaker
(
	sneakerID INT PRIMARY KEY IDENTITY,
	productName VARCHAR(100),
	price INT,
	modelID INT FOREIGN KEY REFERENCES Model(modelID),
)

CREATE TABLE StoreInventory
(
	inventoryID INT PRIMARY KEY IDENTITY,
	sneakerID INT FOREIGN KEY REFERENCES Sneaker(sneakerID),
	quantity INT,
)



CREATE TABLE Client
(
	clientID INT PRIMARY KEY IDENTITY,
	username VARCHAR(50) UNIQUE,
)

CREATE TABLE PaymentMethod
(
    paymentMethodID INT PRIMARY KEY IDENTITY,
    methodName VARCHAR(50) NOT NULL 
)

CREATE TABLE SalesRep
(
    salesRepID INT PRIMARY KEY IDENTITY,
    firstName VARCHAR(50) NOT NULL,
    lastName VARCHAR(50) NOT NULL,
    email VARCHAR(100),
    phoneNumber VARCHAR(15)
)

CREATE TABLE Orders
(
	orderID INT PRIMARY KEY IDENTITY,
    clientID INT FOREIGN KEY REFERENCES Client(clientID),
    checkout INT,
    addressID INT FOREIGN KEY REFERENCES StoreAddress(adressID),
    producerID INT FOREIGN KEY REFERENCES Producer(producerID),
    brandID INT FOREIGN KEY REFERENCES Brand(brandID),
    modelID INT FOREIGN KEY REFERENCES Model(modelID),
    paymentMethodID INT FOREIGN KEY REFERENCES PaymentMethod(paymentMethodID),
    salesRepID INT FOREIGN KEY REFERENCES SalesRep(salesRepID),
    payment VARCHAR(20)
)

