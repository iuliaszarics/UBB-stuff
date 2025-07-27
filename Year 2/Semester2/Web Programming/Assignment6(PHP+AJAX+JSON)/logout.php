<?php
session_start();
require_once 'config.php';
require_once 'database.php';
require_once 'auth.php';

$auth->logout();
header('Location: ../index.php');
exit;
?>
