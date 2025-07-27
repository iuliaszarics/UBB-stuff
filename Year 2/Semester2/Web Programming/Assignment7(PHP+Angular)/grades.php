<?php
require_once 'config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $studentId = isset($_GET['student_id']) ? (int)$_GET['student_id'] : null;
    
    if (!$studentId) {
        echo json_encode(['success' => false, 'message' => 'Student ID is required']);
        exit();
    }
    
    try {
        $stmt = $pdo->prepare("SELECT * FROM grades WHERE student_id = ? ORDER BY subject");
        $stmt->execute([$studentId]);
        $grades = $stmt->fetchAll(PDO::FETCH_ASSOC);
        
        echo json_encode(['success' => true, 'grades' => $grades]);
    } catch(PDOException $e) {
        echo json_encode(['success' => false, 'message' => 'Database error: ' . $e->getMessage()]);
    }
} elseif ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = json_decode(file_get_contents('php://input'), true);
    
    $studentId = $data['student_id'] ?? null;
    $subject = $data['subject'] ?? '';
    $grade = $data['grade'] ?? null;
    
    if (!$studentId || empty($subject) || $grade === null) {
        echo json_encode(['success' => false, 'message' => 'Student ID, subject, and grade are required']);
        exit();
    }
    
    if ($grade < 1 || $grade > 10) {
        echo json_encode(['success' => false, 'message' => 'Grade must be between 1 and 10']);
        exit();
    }
    
    try {
        // Check if grade already exists for this subject
        $stmt = $pdo->prepare("SELECT id FROM grades WHERE student_id = ? AND subject = ?");
        $stmt->execute([$studentId, $subject]);
        $existingGrade = $stmt->fetch();
        
        if ($existingGrade) {
            // Update existing grade
            $stmt = $pdo->prepare("UPDATE grades SET grade = ? WHERE id = ?");
            $stmt->execute([$grade, $existingGrade['id']]);
        } else {
            // Insert new grade
            $stmt = $pdo->prepare("INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?)");
            $stmt->execute([$studentId, $subject, $grade]);
        }
        
        echo json_encode(['success' => true, 'message' => 'Grade saved successfully']);
    } catch(PDOException $e) {
        echo json_encode(['success' => false, 'message' => 'Database error: ' . $e->getMessage()]);
    }
} else {
    echo json_encode(['success' => false, 'message' => 'Invalid request method']);
}
?> 