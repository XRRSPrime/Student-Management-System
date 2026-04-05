const students = [];

const fields = {
    number: document.getElementById('stuNumber'),
    name: document.getElementById('stuName'),
    score1: document.getElementById('stuScore1'),
    score2: document.getElementById('stuScore2'),
    score3: document.getElementById('stuScore3')
};

const tableByNumber = document.getElementById('tableByNumber');
const tableByScore = document.getElementById('tableByScore');
const scoreChart = document.getElementById('scoreChart');

function formatStudent(student) {
    return {
        number: student.number.trim(),
        name: student.name.trim(),
        score1: Number(student.score1),
        score2: Number(student.score2),
        score3: Number(student.score3),
        sum: Number(student.score1) + Number(student.score2) + Number(student.score3)
    };
}

function refreshStudentView() {
    const byNumber = [...students].sort((a, b) => a.number.localeCompare(b.number));
    const byScore = [...students].sort((a, b) => b.sum - a.sum || a.number.localeCompare(b.number));

    const headers = ['学号', '姓名', '成绩1', '成绩2', '成绩3', '总分'];

    tableByNumber.innerHTML = '<thead><tr>' + headers.map(h => `<th>${h}</th>`).join('') + '</tr></thead>' +
        '<tbody>' + byNumber.map(student =>
            `<tr><td>${student.number}</td><td>${student.name}</td><td>${student.score1}</td><td>${student.score2}</td><td>${student.score3}</td><td>${student.sum}</td></tr>`
        ).join('') + '</tbody>';

    tableByScore.innerHTML = '<thead><tr>' + headers.map(h => `<th>${h}</th>`).join('') + '</tr></thead>' +
        '<tbody>' + byScore.map(student =>
            `<tr><td>${student.number}</td><td>${student.name}</td><td>${student.score1}</td><td>${student.score2}</td><td>${student.score3}</td><td>${student.sum}</td></tr>`
        ).join('') + '</tbody>';

    scoreChart.innerHTML = '';
    const topStudents = byScore.slice(0, 5);
    const maxSum = topStudents.length ? Math.max(...topStudents.map(s => s.sum)) : 100;

    topStudents.forEach(student => {
        const chartItem = document.createElement('div');
        chartItem.className = 'chart-item';
        const label = document.createElement('div');
        label.textContent = `${student.name} (${student.number})`;
        const bar = document.createElement('div');
        bar.className = 'bar';
        const fill = document.createElement('div');
        fill.className = 'bar-fill';
        fill.style.width = `${(student.sum / maxSum) * 100}%`;
        bar.appendChild(fill);
        const value = document.createElement('div');
        value.textContent = student.sum;
        chartItem.appendChild(label);
        chartItem.appendChild(bar);
        chartItem.appendChild(value);
        scoreChart.appendChild(chartItem);
    });
}

function addOrUpdateStudent() {
    const student = formatStudent({
        number: fields.number.value,
        name: fields.name.value,
        score1: fields.score1.value,
        score2: fields.score2.value,
        score3: fields.score3.value
    });

    if (!student.number || !student.name) {
        alert('请填写完整的学号和姓名。');
        return;
    }

    const index = students.findIndex(item => item.number === student.number);
    if (index >= 0) {
        students[index] = student;
        alert('学生信息已更新。');
    } else {
        students.push(student);
        alert('学生已添加。');
    }
    refreshStudentView();
}

function deleteStudent() {
    const number = fields.number.value.trim();
    if (!number) {
        alert('请输入要删除的学号。');
        return;
    }
    const index = students.findIndex(item => item.number === number);
    if (index >= 0) {
        students.splice(index, 1);
        alert('删除成功。');
        refreshStudentView();
    } else {
        alert('未找到该学号的学生。');
    }
}

function searchByNumber() {
    const number = document.getElementById('searchByNumber').value.trim();
    if (!number) {
        alert('请输入学号进行查询。');
        return;
    }
    const student = students.find(item => item.number === number);
    if (!student) {
        alert('未找到学号：' + number);
        return;
    }
    alert(`学号：${student.number}\n姓名：${student.name}\n成绩：${student.score1}, ${student.score2}, ${student.score3}\n总分：${student.sum}`);
}

function searchByName() {
    const term = document.getElementById('searchByName').value.trim();
    const matches = students.filter(item => item.name.includes(term));
    if (!matches.length) {
        alert('未找到匹配姓名。');
        return;
    }
    alert(matches.map(student => `${student.number} ${student.name} 总分 ${student.sum}`).join('\n'));
}

document.getElementById('btnAddStudent').addEventListener('click', addOrUpdateStudent);
document.getElementById('btnDeleteStudent').addEventListener('click', deleteStudent);
document.getElementById('btnSearchNumber').addEventListener('click', searchByNumber);
document.getElementById('btnSearchName').addEventListener('click', searchByName);

refreshStudentView();