<?php

function sanitizeInput($data){
    return htmlspecialchars(stripslashes(trim($data)));
}

function redirect($location){
    header("Location: $location");
    exit();
}

function isProfessor(){
    global $auth;
    return $auth->getUserRole()==='professor';
}

function isStudent(){
    global $auth;
    return $auth->getUserRole()==='student';
}


function requireLogin(){
    global $auth;
    if(!$auth->isLoggedIn()){
        redirect('login.php');
    }
}

function requireProfessor(){
    requireLogin();
    if(!isProfessor()){
        redirect('dashboard.php');
    }
}

function requireStudent(){
    requireLogin();
    if(!isStudent()){
        redirect('dashboard.php');
    }
}
?>