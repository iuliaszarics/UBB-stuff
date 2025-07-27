<?php
require_once '../includes/config.php';
require_once '../includes/database.php';
require_once '../includes/auth.php';
require_once '../includes/functions.php';

header('Content-Type: application/json');

try {
    $auth = new Auth($db);
    if (!$auth->isLoggedIn()) {
        throw new Exception('No access');
    }
    $groupId = $_GET['group_id'] ?? null;
    if (!$groupId) {
        throw new Exception('group id is required');
    }
    $students = $db->fetchAll("
        select s.user_id, u.full_name
        from students s
        join users u ON s.user_id = u.id
        where s.group_id = ?
    ", [$groupId]);

    echo json_encode($students);
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode(['error' => $e->getMessage()]);
}
?>