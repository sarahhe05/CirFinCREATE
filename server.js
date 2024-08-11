/*
const express = require('express');
const path = require('path');
//const cors = require('cors');

const app = express();

//app.use(cors());


app.use(express.static(path.join(__dirname, 'static'))); //ensures that Express server is correctly set up to serve static files, such as CSS files


app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname,'jstemplate','index.html'));
}
);
*/
const express = require('express');
const bodyParser = require('body-parser');
const { execFile } = require('child_process');
const path = require('path');

const app = express();

app.use(express.static(path.join(__dirname, 'static')));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname,'jstemplate','index.html'));
});

app.post('/submit', (req, res) => {
    const selectedIngredients = req.body.selectedIngredients;
    console.log(selectedIngredients)

    // Pass the selected ingredients to the C++ program
    execFile('./filterDisplay', selectedIngredients, (error, stdout, stderr) => {
        if (error) {
            console.error(`exec error: ${error}`);
            res.status(500).json({ message: 'Internal Server Error' });
            return;
        }
        const result = stdout.trim().split('##').filter(line => line.length > 0);
        res.json({ message: result });
    });
});

const port = process.env.PORT || 8080  //use "export PORT=1234" to change port
app.listen(port, () => {
    console.log(`Server is listerning on port ${port}`);
});

