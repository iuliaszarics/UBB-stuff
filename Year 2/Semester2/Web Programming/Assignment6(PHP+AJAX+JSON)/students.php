<?php
require_once '../includes/config.php';
require_once '../includes/auth.php';
require_once '../includes/functions.php';

requireProfessor();

$groups = $db->fetchAll("SELECT id, name FROM student_groups ORDER BY name");
$groupId = $_GET['group_id'] ?? null;
$currentPage = max(1, $_GET['page'] ?? 1);
$offset = ($currentPage - 1) * STUDENTS_PER_PAGE;

$students = [];
$totalStudents = 0;

if ($groupId) {
    $totalStudents = $db->fetchOne("SELECT COUNT(*) as count FROM students WHERE group_id = ?", [$groupId])['count'];

    $limit = intval(STUDENTS_PER_PAGE);
    $offsetInt = intval($offset); // make sure it's safe to inject

    $students = $db->fetchAll("
        SELECT u.id, u.full_name, u.username, sg.name AS group_name
        FROM students s
        JOIN users u ON s.user_id = u.id
        JOIN student_groups sg ON s.group_id = sg.id
        WHERE s.group_id = ?
        ORDER BY u.full_name
        LIMIT $limit OFFSET $offsetInt
    ", [$groupId]);
}

$totalPages = ceil($totalStudents / STUDENTS_PER_PAGE);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Students - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
<div class="container">
    <header>
        <h1>Students</h1>
        <nav>
            <ul>
                <li><a href="dashboard.php">Dashboard</a></li>
                <li><a href="manage_grades.php">Manage Grades</a></li>
                <li><a href="students.php">View Students</a></li>
                <li><a href="../includes/logout.php">Logout</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section class="students-section">
            <h2>Students by group</h2>
            <form method="GET" action="students.php">
                <div class="form-group">
                    <label for="group_id">Select Group:</label>
                    <select id="group_id" name="group_id" required>
                        <option value="">Select a group</option>
                        <?php foreach ($groups as $group): ?>
                            <option value="<?php echo $group['id']; ?>"
                                <?php echo $groupId == $group['id'] ? 'selected' : ''; ?>>
                                <?php echo $group['name']; ?>
                            </option>
                        <?php endforeach; ?>
                    </select>
                </div>
                <button type="submit" class="btn">View Students</button>
            </form>

            <?php if ($groupId): ?>
                <h3>Students in <?php echo $students[0]['group_name'] ?? 'Selected group'; ?></h3>
                <table class="students-table">
                    <thead>
                    <tr>
                        <th>Name</th>
                        <th>Username</th>
                    </tr>
                    </thead>
                    <tbody>
                    <?php foreach ($students as $student): ?>
                        <tr>
                            <td><?php echo $student['full_name']; ?></td>
                            <td><?php echo $student['username']; ?></td>
                        </tr>
                    <?php endforeach; ?>
                    </tbody>
                </table>

                <div class="pagination">
                    <?php if ($currentPage > 1): ?>
                        <a href="students.php?group_id=<?php echo $groupId; ?>&page=<?php echo $currentPage - 1; ?>" class="btn">Previous</a>
                    <?php endif; ?>

                    <span>Page <?php echo $currentPage; ?> of <?php echo $totalPages; ?></span>

                    <?php if ($currentPage < $totalPages): ?>
                        <a href="students.php?group_id=<?php echo $groupId; ?>&page=<?php echo $currentPage + 1; ?>" class="btn">Next</a>
                    <?php endif; ?>
                </div>
            <?php endif; ?>
        </section>
    </main>
</div>
</body>
</html>
