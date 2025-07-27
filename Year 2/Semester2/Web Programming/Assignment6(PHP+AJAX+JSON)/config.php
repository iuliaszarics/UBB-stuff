<?php
if (!defined('DB_HOST')) define('DB_HOST', 'localhost');
if (!defined('DB_NAME')) define('DB_NAME', 'school_app');
if (!defined('DB_USER')) define('DB_USER', 'root');
if (!defined('DB_PASS')) define('DB_PASS', '');

if (!defined('APP_NAME')) define('APP_NAME', 'Grade Management System');
if (!defined('STUDENTS_PER_PAGE')) define('STUDENTS_PER_PAGE', 4);

if (session_status() === PHP_SESSION_NONE) {
    session_start();
}
?>