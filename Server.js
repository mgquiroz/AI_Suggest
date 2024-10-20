const express = require('express');
const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');

const app = express();
const PORT = 3000;

app.use(express.urlencoded({ extended: true }));

app.use(express.static(__dirname)); // Changed to serve from the current directory

// Handling index.html
app.post('/submit', (req, res) => {
    const questions = {
        "q1": "1. Do you enjoy socializing with large groups of people?",
        "q2": "2. Do you often start conversations with strangers?",
        "q3": "3. You prefer concrete facts over abstract theories.",
        "q4": "4. You are more focused on the present than future possibilities.",
        "q5": "5. You prioritize logic over emotions when making decisions.",
        "q6": "6. You believe justice is more important than mercy.",
        "q7": "7. You prefer to have a detailed plan rather than being spontaneous.",
        "q8": "8. You like to finish tasks well ahead of a deadline.",
        "q9": "9. You prefer working in a team rather than alone.",
        "q10": "10. You are a perfectionist when it comes to your work."
    };

    // Make results into string
    let results = '';
    for (let key in req.body) {
        if (questions[key]) {
            results += `${questions[key]}: ${req.body[key]}, `;
        }
    }
    results = results.slice(0, -2); // Remove commas

    const filePath = path.join(__dirname, 'quiz-results.txt');

    // Saving to quiz-results.txt
    fs.writeFile(filePath, results, (err) => {


        console.log('Quiz results saved successfully.');

        // Run the C++ program
        const cppFile = path.join(__dirname, './SongListFromPy'); // The compiled C++ program
        exec(cppFile, (error, stdout, stderr) => {

            console.log(`C++ stdout: ${stdout}`);

            // After C++ program execution, run result.html
            res.redirect('/result.html');
        });
    });
});

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});