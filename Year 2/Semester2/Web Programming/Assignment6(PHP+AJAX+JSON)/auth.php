<?php
require_once 'database.php';
require_once 'functions.php';
require_once 'config.php';

if (session_status() === PHP_SESSION_NONE) {
    session_start();
}


class Auth{
    private $db;
    public function __construct(Database $db){
        $this->db=$db;
    }
    public function login($username, $password){
        $user = $this->db->fetchOne("SELECT * FROM users WHERE username = ?", [$username]);
    
        if (!$user) {
            echo "No user found with username: $username";
            return false;
        }
    

        if ($password !== $user['password']) {
            echo "Password doesn't match. Entered: $password | Expected: {$user['password']}";
            return false;
        }
    
        $_SESSION['user_id'] = $user['id'];
        $_SESSION['username'] = $user['username'];
        $_SESSION['role'] = $user['role'];
        $_SESSION['full_name'] = $user['full_name'];
    
        echo "✅ Logged in as {$user['username']}";
        return true;
    }

    public function isLoggedIn(){
        return isset($_SESSION['user_id']);
    }

    public function getUserRole(){
        return $_SESSION['role'] ?? null;
    }

    public function getCurrentUserId(){
        return $_SESSION['user_id'] ?? null;
    }

    public function getCurrentUserName(){
        return $_SESSION['full_name'] ?? 'Guest';
    }

    public function logout() {
        session_unset(); 
        session_destroy();   
    }
}

$auth=new Auth($db);
?>