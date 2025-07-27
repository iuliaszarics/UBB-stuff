<?php
require_once '../includes/config.php';
require_once '../includes/auth.php';
require_once '../includes/functions.php';

requireLogin();

$userId = $auth->getCurrentUserId();
$userRole = $auth->getUserRole();
$userName = $auth->getCurrentUserName();

if (isProfessor()) {
    $grades = $db->fetchAll("
        select g.id, g.grade, g.date_created, 
               u.full_name as student_name, 
               c.name as course_name,
               sg.name as group_name
        from grades g
        join users u ON g.student_id = u.id
        join students s ON g.student_id = s.user_id
        join student_groups sg ON s.group_id = sg.id
        join courses c ON g.course_id = c.id
        where g.professor_id = ?
        order by g.date_created DESC
    ", [$userId]);
} else {
    $grades = $db->fetchAll("
        select g.id, g.grade, g.date_created, 
               u.full_name as professor_name, 
               c.name as course_name
        from grades g
        join users u ON g.professor_id = u.id
        join courses c ON g.course_id = c.id
        where g.student_id = ?
        order by g.date_created DESC
    ", [$userId]);
    
    $stats = $db->fetchOne("
        select count(*) as count, avg(grade) as average 
        from grades 
        where student_id = ?
    ", [$userId]);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Grades - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1><?php echo isProfessor() ? 'Grades Assigned' : 'Your Grades'; ?></h1>
            <nav>
                <ul>
                    <li><a href="dashboard.php">Dashboard</a></li>
                    <?php if (isProfessor()): ?>
                        <li><a href="manage_grades.php">Manage Grades</a></li>
                    <?php endif; ?>
                    <li><a href="grades.php">My Grades</a></li>
                    <li><a href="../includes/logout.php">Logout</a></li>
                </ul>
            </nav>
        </header>
        
        <main>
            <section class="grades-section">
                <?php if (isStudent()): ?>
                    <div class="grade-stats">
                        <h3>Your Statistics</h3>
                        <div class="stats-grid">
                            <div class="stat-card">
                                <h4>Total Grades</h4>
                                <p><?php echo $stats['count']; ?></p>
                            </div>
                            <div class="stat-card">
                                <h4>Average Grade</h4>
                                <p><?php echo number_format($stats['average'], 2); ?></p>
                            </div>
                        </div>
                    </div>
                <?php endif; ?>
                
                <h2><?php echo isProfessor() ? 'Grades You Have Assigned' : 'Your Grade History'; ?></h2>
                
                <?php if (empty($grades)): ?>
                    <p>No grades found.</p>
                <?php else: ?>
                    <table class="grades-table">
                        <thead>
                            <tr>
                                <?php if (isProfessor()): ?>
                                    <th>Student</th>
                                    <th>Group</th>
                                <?php else: ?>
                                    <th>Professor</th>
                                <?php endif; ?>
                                <th>Course</th>
                                <th>Grade</th>
                                <th>Date</th>
                                <?php if (isProfessor()): ?>
                                    <th>Actions</th>
                                <?php endif; ?>
                            </tr>
                        </thead>
                        <tbody>
                            <?php foreach ($grades as $grade): ?>
                                <tr id="grade-row-<?php echo $grade['id']; ?>">
                                    <?php if (isProfessor()): ?>
                                        <td><?php echo htmlspecialchars($grade['student_name']); ?></td>
                                        <td><?php echo htmlspecialchars($grade['group_name']); ?></td>
                                        <?php else: ?>
                                            <td><?php echo htmlspecialchars($grade['professor_name']); ?></td>
                                        <?php endif; ?>
                                        <td><?php echo htmlspecialchars($grade['course_name']); ?></td>
                                        <td id="grade-value-<?php echo $grade['id']; ?>"><?php echo $grade['grade']; ?></td>
                                        <td><?php echo date('Y-m-d', strtotime($grade['date_created'])); ?></td>

                            <?php if (isProfessor()): ?>
                                <td>
                            <form method="POST" action="../api/process_grade.php" class="ajax-form" style="display:inline-block;">
                                <input type="hidden" name="grade_id" value="<?php echo $grade['id']; ?>">
                                <input type="hidden" name="action" value="delete">
                                <button type="submit" class="btn-delete" onclick="return confirm('Are you sure you want to delete this grade?')">Delete</button>
                            </form>
                                            <button class="btn-update" onclick="showUpdateForm(<?php echo $grade['id']; ?>)">Update</button>
                                            <div id="update-form-<?php echo $grade['id']; ?>" class="update-form" style="display:none; margin-top:10px;">
                                                <form method="POST" action="../api/process_grade.php" class="ajax-form">
                                                    <input type="hidden" name="grade_id" value="<?php echo $grade['id']; ?>">
                                                    <input type="hidden" name="action" value="update">
                                                    <input type="number" name="grade" min="1" max="10" step="0.01" placeholder="New Grade" required value="<?php echo $grade['grade']; ?>">
                                                    <button type="submit" class="btn-save">Save</button>
                                                    <button type="button" class="btn-cancel" onclick="hideUpdateForm(<?php echo $grade['id']; ?>)">Cancel</button>
                                                </form>
                                            </div>
                                        </td>
                                    <?php endif; ?>
                                </tr>
                            <?php endforeach; ?>
                        </tbody>
                    </table>
                <?php endif; ?>
            </section>
        </main>
    </div>
    <script src="../js/scripts.js"></script>
</body>
</html>