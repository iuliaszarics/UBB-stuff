<?php
require_once 'includes/config.php';
require_once 'includes/auth.php';

if($auth->isLoggedIn()){
    redirect('dashboard.php');
} else {
    redirect('../assignment6php/pages/login.php');
}

?>