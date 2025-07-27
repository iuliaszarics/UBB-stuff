document.addEventListener('DOMContentLoaded', function () {
    const groupSelect = document.getElementById('group_id');
    const studentSelect = document.getElementById('student_id');

    if (groupSelect) {
        groupSelect.addEventListener('change', function () {
            const groupId = this.value;

            if (!groupId) {
                if (studentSelect) {
                    studentSelect.innerHTML = '<option value="">Select a student</option>';
                    studentSelect.disabled = true;
                }
                return;
            }

            if (studentSelect) {
                studentSelect.innerHTML = '<option value="">Loading students...</option>';
                studentSelect.disabled = true;
            }

            fetch(`../api/get_students.php?group_id=${groupId}`)
                .then(response => {
                    if (!response.ok) {
                        throw new Error("Failed to fetch students");
                    }
                    return response.json();
                })
                .then(data => {
                    if (data.error) {
                        if (studentSelect) {
                            studentSelect.innerHTML = `<option value="">${data.error}</option>`;
                            studentSelect.disabled = true;
                        }
                        return;
                    }

                    if (studentSelect) {
                        let options = '<option value="">Select a student</option>';
                        data.forEach(student => {
                            options += `<option value="${student.user_id}">${student.full_name}</option>`;
                        });
                        studentSelect.innerHTML = options;
                        studentSelect.disabled = false;
                    }
                })
                .catch(error => {
                    if (studentSelect) {
                        studentSelect.innerHTML = '<option value="">Error loading students</option>';
                        studentSelect.disabled = true;
                    }
                    console.error('Fetch error:', error);
                });
        });
    }
    
    window.showUpdateForm = function (id) {
        document.getElementById('update-form-' + id).style.display = 'block';
    };

    window.hideUpdateForm = function (id) {
        document.getElementById('update-form-' + id).style.display = 'none';
    };

    document.querySelectorAll('.update-form form').forEach(function (form) {
        form.addEventListener('submit', function (e) {
            e.preventDefault();

            const formData = new FormData(form);
            const gradeId = formData.get('grade_id');
            const newGrade = formData.get('grade');

            fetch('../api/process_grade.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    action: 'update_inline',
                    grade_id: gradeId,
                    grade: newGrade
                })
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    // Update the grade text instantly
                    document.getElementById('grade-value-' + gradeId).innerText = newGrade;
                    hideUpdateForm(gradeId);
                    alert('Grade updated successfully');
                } else {
                    alert('Error updating grade: ' + data.error);
                }
            })
            .catch(error => {
                console.error('Fetch error:', error);
                alert('An error occurred while updating the grade');
            });
        });
    });
});
