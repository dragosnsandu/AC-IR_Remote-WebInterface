const express = require('express');
const app = express();
const bodyParser= require('body-parser');
let port = process.env.PORT || 3000;

let command = -1;

app.use(bodyParser.urlencoded({extended:true}));

app.set('view engine', 'pug');

app.get('/', (req, res) => {
        res.render('index');
        //res.sendStatus(command);
        // res.send(command);
});

app.post('/poweron',(req,res)=>{

command = req.body.powerOn; // here you can get the value of from the textbox
    res.render('index');
});

app.post('/arrowup',(req,res)=>{

    command = req.body.arrowUp; // here you can get the value of from the textbox
    res.render('index');
});

app.get('/command',(req,res)=>{
    res.send(command.toString());
});

app.listen(port, () => console.log('Server is running on port ' + port));