import * as express from 'express';
import * as cors from 'cors';
import * as bodyParser from 'body-parser';
import { SetColorCommand } from './models/set-color';
import * as SerialPort from 'serialport';
import { SetLedColorCommand } from './models/set-led-color';
import { SetBrightnessCommand } from './models/set-brightness';

const app = express();

console.log(app.configure);

app.use(cors());
app.use(bodyParser.json())

app.listen(3000, () => {
    console.log("Server is running at http://localhost:3000");
});

const serial = new SerialPort('COM7', { baudRate: 9600, }, (err) => {
    console.error('error:', err);
});

serial.on('data', (data) => {
    console.log('Data:', data.toString());
})

app.post('/api/set-color', (req, res) => {
    const cmd = new SetColorCommand(req.body);
    try {
        serial.write(cmd.build());
        res.send();
    } catch (ex) {
        res.status(402);
        res.json(ex);
    }

});

app.post('/api/set-led-color', (req, res) => {
    const cmd = new SetLedColorCommand(req.body);
    try {
        serial.write(cmd.build());
        res.send();
    } catch (ex) {
        res.status(402);
        res.json(ex);
    }
});

app.post('/api/set-brightness', (req, res) => {
    const cmd = new SetBrightnessCommand(req.body);
    try {
        serial.write(cmd.build());
        res.send();
    } catch (ex) {
        res.status(402);
        res.json(ex);
    }
});

