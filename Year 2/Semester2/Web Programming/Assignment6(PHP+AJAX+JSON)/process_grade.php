<?php
require_once '../includes/config.php';
require_once '../includes/database.php';
require_once '../includes/auth.php';
require_once '../includes/functions.php';

header('Content-Type: application/json');

try {
    $auth = new Auth($db);

    if (!$auth->isLoggedIn() || $auth->getUserRole() !== 'professor') {
        throw new Exception('Unauthorized access');
    }

    $input = json_decode(file_get_contents('php://input'), true);
    if (!$input) {
        throw new Exception('Invalid input data');
    }

    $action = $input['action'] ?? '';
    $professorId = $auth->getCurrentUserId();

    switch ($action) {
        case 'add':
        case 'update':
            $studentId = $input['student_id'] ?? null;
            $courseId = $input['course_id'] ?? null;
            $grade = $input['grade'] ?? null;

            if (!$studentId || !$courseId || $grade === null) {
                throw new Exception('Missing required fields');
            }
            if ($grade < 1 || $grade > 10) {
                throw new Exception('Grade must be between 1 and 10');
            }

            $existingGrade = $db->fetchOne(
                "SELECT id FROM grades WHERE student_id = ? AND course_id = ? AND professor_id = ?",
                [$studentId, $courseId, $professorId]
            );

            if ($existingGrade) {
                $db->query(
                    "UPDATE grades SET grade = ? WHERE id = ?",
                    [$grade, $existingGrade['id']]
                );
                $message = "Grade updated successfully.";
            } else {
                $db->query(
                    "INSERT INTO grades (student_id, course_id, professor_id, grade) VALUES (?, ?, ?, ?)",
                    [$studentId, $courseId, $professorId, $grade]
                );
                $message = "Grade added successfully.";
            }
            break;

        case 'delete':
            $gradeId = $input['grade_id'] ?? null;
            if (!$gradeId) {
                throw new Exception('Grade ID is required.');
            }
            $grade = $db->fetchOne(
                "SELECT id FROM grades WHERE id = ? AND professor_id = ?",
                [$gradeId, $professorId]
            );

            if (!$grade) {
                throw new Exception('Grade not found or unauthorized.');
            }

            $db->query("DELETE FROM grades WHERE id = ?", [$gradeId]);
            $message = "Grade deleted successfully.";
            break;

        default:
            throw new Exception('Invalid action.');
    }

    echo json_encode(['success' => true, 'message' => $message]);
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode(['success' => false, 'error' => $e->getMessage()]);
}
?>
