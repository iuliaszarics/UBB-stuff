<?php
require_once '../includes/config.php';
require_once '../includes/auth.php';

if($auth->isLoggedIn()){
    redirect('dashboard.php');
}

if($_SERVER['REQUEST_METHOD']==='POST'){
    $username=sanitizeInput($_POST['username']);
    $password=sanitizeInput($_POST['password']);
    if($auth->login($username, $password)){
        header("Location: dashboard.php");
        exit;
    } else {
        $error='Invalid username or password';
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Login - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <div class="login-container">
        <h1>Login</h1>
        <?php if (isset($error)): ?>
            <div class="error"><?php echo $error; ?></div>
        <?php endif; ?>
        <form method="POST" action="">
            <div class="form-group">
                <label for="username">Username:</label>
                <input type="text" id="username" name="username" required>
            </div>
            <div class="form-group">
                <label for="password">Password:</label>
                <input type="password" id="password" name="password" required>
            </div>
            <button type="submit" class="btn">Login</button>
        </form>
    </div>
</body>
</html>