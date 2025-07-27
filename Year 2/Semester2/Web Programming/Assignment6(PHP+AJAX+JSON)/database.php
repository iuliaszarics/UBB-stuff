<?php
require_once 'config.php';

class Database{
    private $connection;
    public function __construct(){
        try{
            $this->connection = new PDO(
                "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME,
                DB_USER,
                DB_PASS
            );
            $this->connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            $this->connection->exec("set names 'utf8'");
        }catch(PDOException $e){
            echo "Connection failed: " . $e->getMessage();
        }
    }

    public function getConnection(){
        return $this->connection;
    }

    public function query($sql,$params=[]){
        $statement = $this->connection->prepare($sql);
        $statement->execute($params);
        return $statement;
    }

    public function fetchAll($sql,$params=[]){
        $statement = $this->query($sql,$params);
        return $statement->fetchAll(PDO::FETCH_ASSOC);
    }

    public function fetchOne($sql, $params=[]){
        $statement=$this->query($sql,$params);
        return $statement->fetch(PDO::FETCH_ASSOC);
    }

    public function lastInsertId(){
        return $this->connection->lastInsertId();
    }
}

$db=new Database();
?>