<?php
require_once '../includes/config.php';
require_once '../includes/auth.php';
require_once '../includes/functions.php';

requireLogin();

$userRole = $auth->getUserRole();
$userName = $auth->getCurrentUserName();

$stats = [];
if (isProfessor()) {
    $stats['courses'] = $db->fetchOne(
        "select count(*) as count from professor_courses where professor_id = ?",
        [$auth->getCurrentUserId()]
    )['count'];
    
    $stats['grades_assigned'] = $db->fetchOne(
        "select count(*) as count from grades where professor_id = ?",
        [$auth->getCurrentUserId()]
    )['count'];
    
    $stats['groups'] = $db->fetchOne(
        "select count(distinct s.group_id) as count 
         from grades g 
         join students s on g.student_id = s.user_id 
         where g.professor_id = ?",
        [$auth->getCurrentUserId()]
    )['count'];
} else {
    $stats['grades'] = $db->fetchOne(
        "select count(*) as count from grades where student_id = ?",
        [$auth->getCurrentUserId()]
    )['count'];
    
    $stats['average'] = $db->fetchOne(
        "select avg(grade) as average from grades where student_id = ?",
        [$auth->getCurrentUserId()]
    )['average'];
    
    $groupInfo = $db->fetchOne(
        "SELECT sg.name FROM students s 
         JOIN student_groups sg ON s.group_id = sg.id 
         WHERE s.user_id = ?",
        [$auth->getCurrentUserId()]
    );
    $stats['group'] = $groupInfo ? $groupInfo['name'] : 'Not assigned';
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>Welcome, <?php echo htmlspecialchars($userName); ?></h1>
            <nav>
                <ul>
                    <li><a href="dashboard.php">Dashboard</a></li>
                    <?php if (isProfessor()): ?>
                        <li><a href="manage_grades.php">Manage Grades</a></li>
                        <li><a href="students.php">View Students</a></li>
                    <?php else: ?>
                        <li><a href="grades.php">My Grades</a></li>
                    <?php endif; ?>
                    <li><a href="../includes/logout.php">Logout</a></li>
                </ul>
            </nav>
        </header>
        
        <main>
            <section class="dashboard-section">
                <h2>Your Statistics</h2>
                
                <div class="stats-grid">
                    <?php if (isProfessor()): ?>
                        <div class="stat-card">
                            <h3>Courses</h3>
                            <p><?php echo $stats['courses']; ?></p>
                        </div>
                        <div class="stat-card">
                            <h3>Grades Assigned</h3>
                            <p><?php echo $stats['grades_assigned']; ?></p>
                        </div>
                        <div class="stat-card">
                            <h3>Groups</h3>
                            <p><?php echo $stats['groups']; ?></p>
                        </div>
                    <?php else: ?>
                        <div class="stat-card">
                            <h3>Your Group</h3>
                            <p><?php echo htmlspecialchars($stats['group']); ?></p>
                        </div>
                        <div class="stat-card">
                            <h3>Grades Received</h3>
                            <p><?php echo $stats['grades']; ?></p>
                        </div>
                        <div class="stat-card">
                            <h3>Average Grade</h3>
                            <p><?php echo number_format($stats['average'], 2); ?></p>
                        </div>
                    <?php endif; ?>
                </div>
                
                <div class="recent-activity">
                    <h3>Recent Activity</h3>
                    <?php if (isProfessor()): ?>
                        <?php
                        $recentGrades = $db->fetchAll("
                            select g.grade, g.date_created, u.full_name as student_name, c.name as course_name
                            from grades g
                            join users u ON g.student_id = u.id
                            join courses c ON g.course_id = c.id
                            where g.professor_id = ?
                            order by g.date_created DESC
                            limit 5
                        ", [$auth->getCurrentUserId()]);
                        ?>
                        
                        <?php if ($recentGrades): ?>
                            <ul class="activity-list">
                                <?php foreach ($recentGrades as $grade): ?>
                                    <li>
                                        <span class="activity-date"><?php echo date('M j, Y', strtotime($grade['date_created'])); ?></span>
                                        <span class="activity-desc">Assigned <?php echo $grade['grade']; ?> to <?php echo htmlspecialchars($grade['student_name']); ?> in <?php echo htmlspecialchars($grade['course_name']); ?></span>
                                    </li>
                                <?php endforeach; ?>
                            </ul>
                        <?php else: ?>
                            <p>No recent grade assignments</p>
                        <?php endif; ?>
                    <?php else: ?>
                        <?php
                        $recentGrades = $db->fetchAll("
                            select g.grade, g.date_created, u.full_name as professor_name, c.name as course_name
                            from grades g
                            join users u ON g.professor_id = u.id
                            join courses c ON g.course_id = c.id
                            where g.student_id = ?
                            order by g.date_created DESC
                            limit 5
                        ", [$auth->getCurrentUserId()]);
                        ?>
                        
                        <?php if ($recentGrades): ?>
                            <ul class="activity-list">
                                <?php foreach ($recentGrades as $grade): ?>
                                    <li>
                                        <span class="activity-date"><?php echo date('M j, Y', strtotime($grade['date_created'])); ?></span>
                                        <span class="activity-desc">Received <?php echo $grade['grade']; ?> in <?php echo htmlspecialchars($grade['course_name']); ?> from <?php echo htmlspecialchars($grade['professor_name']); ?></span>
                                    </li>
                                <?php endforeach; ?>
                            </ul>
                        <?php else: ?>
                            <p>No recent grades received</p>
                        <?php endif; ?>
                    <?php endif; ?>
                </div>
            </section>
        </main>
    </div>
</body>
</html>