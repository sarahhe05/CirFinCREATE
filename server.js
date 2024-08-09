const express = require('express');
const path = require('path');

const app = express();

app.use(express.static(path.join(__dirname, 'static'))); //ensures that Express server is correctly set up to serve static files, such as CSS files

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'templates/index.html'));
}
);

const port = process.env.PORT || 8080  //use "export PORT=1234" to change port
app.listen(port, () => {
    console.log(`Server is listerning on port ${port}`);
});

