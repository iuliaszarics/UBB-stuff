<?php
require_once '../includes/config.php';
require_once '../includes/auth.php';
require_once '../includes/functions.php';

requireProfessor();

$professorId=$auth->getCurrentUserId();

$courses=$db->fetchAll(
"select c.id, c.name 
from courses c 
join professor_courses pc 
on c.id = pc.course_id 
where pc.professor_id = ?",[$professorId]);

$groups = $db->fetchAll("select id, name from student_groups order by name");

if($_SERVER['REQUEST_METHOD']==='POST'){
    $studentId = $_POST['student_id'] ?? null;
    $courseId = $_POST['course_id'] ?? null;
    $grade = $_POST['grade'] ?? null;
    $action = $_POST['action'] ?? '';

    if($action==="add" && $studentId && $courseId && $grade){
        $existingGrade = $db->FetchOne("select id 
        from grades 
        where student_id = ? 
        and course_id = ?
        and professor_id = ?", [$studentId, $courseId, $professorId]);

        if($existingGrade){
            $db->query("update grades set grade = ? where id = ?", [$grade, $existingGrade['id']]);
            $message = "Grade updated successfully.";
        } else {
            $db->query("insert into grades (student_id, course_id, professor_id, grade) values ( ?, ?, ?, ?)", [$studentId, $courseId, $professorId, $grade]);
            $message = "Grade added successfully.";
        }
    }elseif($action==="delete" &&isset($_POST['grade_id'])){
        $db->query("delete from grades where id = ? and professor_id = ?", [$_POST['grade_id'],$professorId]);
        $message = "Grade deleted successfully.";
    }
}

$assignedGrades=$db->fetchAll("select g.id, g.grade, g.date_created, s.user_id as student_id, u.full_name as student_name, c.name as course_name, gr.name as group_name
from grades g 
join students s on g.student_id = s.user_id
join users u on s.user_id = u.id
join courses c on g.course_id = c.id
join student_groups gr on s.group_id = gr.id
where g.professor_id = ?
order by g.date_created desc", [$professorId]);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Manage Grades - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../css/style.css">
    <script src="../scripts/scripts.js"></script>
</head>
<body>
    <div class="container">
        <header>
            <h1>Manage Grades</h1>
            <nav>
                <ul>
                    <li><a href="dashboard.php">Dashboard</a></li>
                    <li><a href="manage_grades.php">Manage Grades</a></li>
                    <li><a href="students.php">View Students</a></li>
                    <li><a href="logout.php">Logout</a></li>
                </ul>
            </nav>
        </header>
<main>
    <section class="manage-grades-section">
        <h2>Assign new grade</h2>
        <?php if(isset($message)): ?>
            <div class="message"><?php echo $message; ?></div>
        <?php endif; ?>
        <form id="gradeForm" method="POST">
            <div class="form-group">
                <label for="course_id">Course:</label>
                <select id="course_id" name="course_id" required>
                    <option value="">Select a course</option>
                    <?php foreach($courses as $course): ?>
                        <option value="<?php echo $course['id']; ?>"><?php echo $course['name']; ?></option>
                    <?php endforeach; ?>
                </select>
            </div>
            <div class="form-group">
                <label for="group_id">Group:</label>
                <select id ="group_id" name="group_id" required>
                    <option value="">Select a group</option>
                    <?php foreach($groups as $group): ?>
                        <option value="<?php echo $group['id']; ?>"><?php echo $group['name']; ?></option>
                    <?php endforeach; ?>
                </select>
            </div>
            <div class="form-group">
                <label for="student_id">Student:</label>
                <select id="student_id" name="student_id" required>
                    <option value="">Select a student</option>
                </select>
            </div>
            <div class="form-group">
                <label for="grade">Grade:</label>
                <input type="number" id="grade" name="grade" min="1" max="10" step="0.1" required>
            </div>
            <input type="hidden" name="action" value="add">
            <button type="submit" class="btn">Assign</button>
        </form>
        <h2>Assigned Grades</h2>
        <table class="grades-table">
            <thead>
                <tr>
                    <th>Student</th>
                    <th>Group</th>
                    <th>Course</th>
                    <th>Grade</th>
                    <th>Date</th>
                    <th>Actions</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach($assignedGrades as $grade): ?>
                    <tr>
                        <td><?php echo $grade['student_name']; ?></td>
                        <td><?php echo $grade['group_name']; ?></td>
                        <td><?php echo $grade['course_name'];?></td>
                        <td><?php echo $grade['grade']; ?></td>
                        <td><?php echo date('Y-m-d', strtotime($grade['date_created'])); ?></td>
                        <td>
                            <form method="POST" style="display:inline;">
                                <input type="hidden" name="grade_id" value="<?php echo $grade['id']; ?>">
                                <input type="hidden" name="action" value="delete">
                                <button type="submit" class="btn-delete" onlick="return confirm('Are you sure you want to delete this grade?')">Delete</button>
                            </form>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    </section>
</main>
</div>
</body>
</html>  